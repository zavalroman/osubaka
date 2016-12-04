//
// Sound data classes for OpenAL
//

#include	<stdio.h>
#include	<string>
#include	<AL/al.h>
#include	<vorbis/vorbisfile.h>
#include	<mad.h>
#include	"SoundData.h"
#include	"Data.h"
#include	"OggSoundData.h"
#include	"WavSoundData.h"
#include	"Mp3SoundData.h"
#include	<string>
#include	<cstring>

SoundData :: SoundData ( Data * theData )
{
	data          = theData;
	fp            = 0;
	numChannels   = 0;
	frequency     = 0;
	bitsPerSample = 8;
	ok            = true;
}

SoundData :: SoundData ( const char * theFileName )
{
	data          = NULL;
	fp            = fopen ( theFileName, "rb" );
	numChannels   = 0;
	frequency     = 0;
	bitsPerSample = 8;
	ok            = true;
}

SoundData :: ~SoundData ()
{
	delete data;

	if ( fp != NULL )
		fclose ( fp );
}

bool	SoundData :: isOk () const
{
	return data != NULL || fp != NULL && ok;
}

bool	SoundData :: atEnd () const
{
	if ( data != NULL )
		return data -> getPos() >= data -> getLength ();

	return true;
}

int	SoundData :: getPos () const //added by rooman 08.03.2015
{	
	return data -> getPos();
}

////////////////////// Concrete classes for wav/ogg/mp3 formats ////////////////
////////////////////////////////////// ogg  ////////////////////////////////////

OggSoundData :: OggSoundData  ( Data * theData ) : SoundData ( theData )
{
	ov_callbacks	cb;

	cb.read_func  = readFunc;
	cb.seek_func  = seekFunc;
	cb.close_func = closeFunc;
	cb.tell_func  = tellFunc;

	if ( ov_open_callbacks ( this, &file, NULL, 0, cb ) < 0 )
	{
		ok = false;

		return;
	}

	info          = ov_info ( &file, -1 );
	numChannels   = info -> channels;
	frequency     = info -> rate;
	bitsPerSample = 16;
}

OggSoundData :: OggSoundData  ( const char * theFileName ) : SoundData ( theFileName )
{
	if ( ov_open ( fp, &file, NULL, 0 )	< 0 )
	{
		ok = false;

		return;
	}

	info          = ov_info ( &file, -1 );
	numChannels   = info -> channels;
	frequency     = info -> rate;
	bitsPerSample = 16;
}

OggSoundData :: ~OggSoundData ()
{
	ov_clear ( &file );
}

int	OggSoundData :: getSize () const
{
	double	totalTime = ov_time_total ( const_cast <OggVorbis_File *> ( &file ), -1 );

	return (int)( totalTime + 0.5) * numChannels * frequency * 2;
}
											// fill buffer with next audio data
int		OggSoundData :: read ( byte * buf, int size )
{
	if ( size < 0 )
		size = getSize ();

	int	curSection;
	int	bytesRead = 0;

	while ( bytesRead < size )
	{
		int	res = ov_read ( &file, (char *)(buf + bytesRead), size - bytesRead, 0, 2, 1, &curSection );

		if ( res <= 0 )
			break;

		bytesRead += res;
	}

	return bytesRead;
}

											// position in sound (in seconds)
bool	OggSoundData :: seek ( float time )
{
	ov_time_seek ( &file, time );

	return true;
}

////////////////////////////////////// wav  ////////////////////////////////////

#pragma pack (push, 1)

struct WavFmt
{
		unsigned short encoding;
		unsigned short channels;
		unsigned int   frequency;
		unsigned int   byterate;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
};

#pragma pack (pop)

WavSoundData :: WavSoundData ( Data * theData ) : SoundData ( theData )
{
	long	magic  = data -> getLong ();
	long	length = data -> getLong ();
	long	magic2 = data -> getLong ();

	if ( magic != RIFF || magic2 != WAVE )
	{
		ok = false;

		return;
	}

	for ( ; data -> getPos () < data -> getLength (); )
	{
		magic  = data -> getLong ();
		length = data -> getLong ();

		if ( magic == FMT )
		{
			WavFmt	format;

			data -> getBytes ( &format, sizeof ( format ) );

			if ( format.encoding != 1 )
			{
				ok = false;

				return;
			}

			numChannels   = format.channels;
			frequency     = format.frequency;
			bitsPerSample = format.bitsPerSample;
		}
		else
		if ( magic == DATA )
		{
			dataOffs   = data -> getPos ();
			dataLength = length;

			break;
		}
		else
			data -> seekCur ( length );
	}

	if ( numChannels < 1 || frequency == 0 || dataOffs == 0 || dataLength == 0 )
		ok = false;
}

WavSoundData :: ~WavSoundData ()
{

}

int		WavSoundData :: getSize () const
{
	return dataLength;
}

											// fill buffer with next audio data
int		WavSoundData :: read ( byte * buf, int size )
{	
	int	bytesLeft = dataLength - (data -> getPos () - dataOffs);

	if ( size < 0 || size > bytesLeft )
		size = bytesLeft;
	
	return data -> getBytes ( buf, size );
}

											// position in sound (in seconds)
bool	WavSoundData :: seek ( float time )
{
	data -> seekAbs ( dataOffs + (int)(time * numChannels * frequency*bitsPerSample/2) );	// XXX - 16 bit ???

	return true;
}

////////////////////////////////////// mp3 ////////////////////////////////////

Mp3SoundData :: Mp3SoundData ( const char * theFileName ) : SoundData ( theFileName )
{
	if ( fp == NULL )
	{
		ok = false;

		return;
	}

	fseek ( fp, 0, SEEK_END );

	fileSize = ftell ( fp );

	fseek ( fp, 0, SEEK_SET );

	bufferLength = 0;
	
	mad_synth_init  ( &synth  );
	mad_stream_init ( &stream );
	mad_frame_init  ( &frame  );

	if ( readFrame () == 0 )
	{
		ok = false;

		return;
	}

	numChannels   = ( frame.header.mode == MAD_MODE_SINGLE_CHANNEL ? 1 : 2 );
	frequency     = frame.header.samplerate;
	bitRate       = frame.header.bitrate;
	bitsPerSample = 16;
	
	SoundData::bitRate = bitRate; //added by rooman 08.03.2015
}

Mp3SoundData :: Mp3SoundData ( Data * theData ) : SoundData ( theData )
{
	fileSize     = data -> getLength ();
	bufferLength = 0;

	data -> seekAbs ( 0 );

	mad_synth_init  ( &synth  );
	mad_stream_init ( &stream );
	mad_frame_init  ( &frame  );

	if ( readFrame () == 0 )
	{
		ok = false;

		return;
	}

	numChannels   = ( frame.header.mode == MAD_MODE_SINGLE_CHANNEL ? 1 : 2 );
	frequency     = frame.header.samplerate;
	bitRate       = frame.header.bitrate;
	bitsPerSample = 16;
	
	SoundData::bitRate = bitRate; //added by rooman 08.03.2015
}

Mp3SoundData :: ~Mp3SoundData ()
{
	mad_synth_finish  ( &synth  );
	mad_stream_finish ( &stream );
	mad_frame_finish  ( &frame  );
}

int	Mp3SoundData :: readFrame ()
{
	while ( true )
	{
		int ret;
		int	savePos = data -> getPos ();
												// read more data
		if ( fp != NULL )
			ret = fread ( buffer + bufferLength, 1, BUFFER_SIZE - bufferLength, fp );
		else
			ret = data -> getBytes ( buffer + bufferLength, BUFFER_SIZE - bufferLength );

		if ( ret <= 0 )
			break;

		bufferLength += ret;

		mad_stream_buffer ( &stream, buffer, bufferLength );

		ret = mad_frame_decode ( &frame, &stream );

		if ( stream.next_frame != NULL )
		{
			int	length = buffer + bufferLength - (byte *)stream.next_frame;

												// copy next frame data to start of buffer
			memmove ( buffer, stream.next_frame, length );

			bufferLength = length;				// set correct length of remaining data
		}

		if ( ret == 0 )
			return 1;
												// if insufficient data break to outer (reading) loop
		if ( stream.error == MAD_ERROR_BUFLEN )
			continue;
	}

	return 0;
}

int 	Mp3SoundData :: getSize () const
{
	return fileSize * 8 / bitRate * numChannels * frequency * 2;
}

bool	Mp3SoundData :: seek ( float time )
{
	unsigned	pos = (unsigned)((double)bitRate / 8.0 * time);

	if ( fp != NULL )
		fseek ( fp, pos, SEEK_SET );
	else
		data -> seekAbs ( pos );

	readFrame ();

	return true;
}

inline	int	resample ( mad_fixed_t sample )
{
	sample += 1 << (MAD_F_FRACBITS - 16);

	if ( sample >= MAD_F_ONE )
		sample = MAD_F_ONE - 1;
	else
	if ( sample < -MAD_F_ONE )
		sample = -MAD_F_ONE;

	return (int)(sample >> (MAD_F_FRACBITS  - 15));
}

int 	Mp3SoundData :: read ( byte * out, int size )
{
	if ( size < 0 )
		size = getSize ();

	int bytesRead = 0;

	while ( bytesRead < size )
	{
		mad_synth_frame ( &synth, &frame );

		mad_pcm     * pcm   = &synth.pcm;
		mad_fixed_t * left  = pcm -> samples [0];
		mad_fixed_t * right = pcm -> samples [1];
		uint16      * data  = (uint16 *)(out + bytesRead);

		for ( size_t length = pcm -> length; length > 0; length-- )
		{
			*data++ = resample ( *left++ );

			if ( numChannels == 2 )
				*data++ = resample ( *right++ );
		}

		bytesRead += pcm -> length * numChannels * 2;

		if ( readFrame () == 0 )
			return bytesRead;
	}

	return bytesRead;
}
