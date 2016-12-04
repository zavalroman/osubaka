//
// SoundData subclass to load mp3 files
//

#ifndef	__MP3_SOUND_DATA__
#define	__MP3_SOUND_DATA__

#include	"SoundData.h"
#include	<mad.h>

class	Mp3SoundData : public SoundData
{
	enum
	{
		BUFFER_SIZE = 4096
	};

	int			fileSize;
	byte		buffer [BUFFER_SIZE];
	byte		outBuf [BUFFER_SIZE];
	int			bufferLength;
	mad_synth	synth;
	mad_stream	stream;
	mad_frame	frame;
	int			bitRate;

public:
	Mp3SoundData  ( Data * theData );
	Mp3SoundData  ( const char * theFileName );
	~Mp3SoundData ();

	virtual	int	getSize () const;

											// fill buffer with next audio data
	virtual	int	read ( byte * buf, int size = -1 );

											// position in sound (in seconds)
	virtual	bool	seek ( float time );

protected:
	int	readFrame ();
};

#endif
