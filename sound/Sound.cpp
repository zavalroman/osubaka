//
// Sound source wrapper for OpenAL
//
// Author: Alex V. Boreskoff
//

//#include	<stdio.h>

#include	"Sound.h"
#include	"SoundData.h"
#include	"OpenAlContext.h"

Sound :: Sound  ( SoundData * data, bool theLoop  )
{
	dataSource = data;

	if ( dataSource == NULL )
		return;

	looping = theLoop;
	stream  = true;

	if ( dataSource -> getNumChannels () == 2 )		// stereo
		if ( dataSource -> getBitsPerSample () == 16 )
			format = AL_FORMAT_STEREO16;
		else
			format = AL_FORMAT_STEREO8;
	else
		if ( dataSource -> getBitsPerSample () == 16 )
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_MONO8;

	if ( dataSource -> getSize () < BUFFER_SIZE * 2 )
		stream = false;

	if ( stream )
	{
		buf           = new byte [BUFFER_SIZE * 2];
		currentBuffer = 0;

		alGenBuffers ( 2, buffer  );
		alGenSources ( 1, &source );
	}
	else
	{
		buf = new byte [dataSource -> getSize ()];

		int size = dataSource -> read ( buf );

		alGenBuffers ( 1, buffer );
		alBufferData ( buffer[0], format, buf, size, dataSource -> getFrequency () );
		alGenSources ( 1,&source );

		alSourcei ( source, AL_BUFFER, buffer[0] );
		alSourcei ( source, AL_LOOPING, looping ? AL_TRUE : AL_FALSE );

		delete buf;
	}
}

Sound :: ~Sound ()
{
	if( dataSource == NULL )
		return;

	delete dataSource;

	if ( stream )
		delete buf;

	alDeleteSources ( 1, &source );

	if ( stream )
		alDeleteBuffers ( 2, buffer );
	else
		alDeleteBuffers ( 1, buffer );
}

bool	Sound :: isPlaying () const
{
	ALint state;

	alGetSourcei ( source, AL_SOURCE_STATE, &state );

	return state == AL_PLAYING;
}

bool	Sound :: atEnd () const
{
	if ( isPlaying () )
		return false;

	return dataSource -> atEnd ();
}

void	Sound :: setPos ( const Vector3D& newPos )
{
	pos = newPos;

	alSourcefv ( source, AL_POSITION, pos );
}

void	Sound :: setVelocity ( const Vector3D& newVel )
{
	velocity = newVel;

	alSourcefv ( source, AL_VELOCITY, velocity );
}

void	Sound :: setPitch ( float newPitch )
{
	pitch = newPitch;

	alSourcef ( source, AL_PITCH, pitch );
}

void	Sound :: setGain ( float newGain )
{
	gain = newGain;

	alSourcef ( source, AL_GAIN, gain );
}

void	Sound :: setLooping ( bool flag )
{
	looping = flag;

	alSourcei ( source,AL_LOOPING, looping ? AL_TRUE : AL_FALSE );
}

void	Sound :: play ()
{
	ALint 	state;
	int		size;

	alGetSourcei ( source, AL_SOURCE_STATE, &state );
	
	if ( state == AL_PLAYING )
		return;
	
	if ( state != AL_PAUSED && stream )
	{
		size = dataSource -> read ( buf, BUFFER_SIZE );

		alBufferData ( buffer [0], format, buf, size, dataSource -> getFrequency () );

		size = dataSource -> read ( buf, BUFFER_SIZE );

		alBufferData         ( buffer [1], format, buf, size,
		                       dataSource -> getFrequency () );
		alSourceQueueBuffers ( source, 2, buffer );

		OpenAlContext :: registerSound ( this );
	}
	//std::cout << "source " << source << std::endl;
	alSourcePlay ( source );
}

void	Sound :: pause ()
{
	alSourcePause ( source );
}

void	Sound :: rewind ()
{
	alSourceRewind ( source );
}

void	Sound :: stop ()
{
	alSourceStop ( source );

	dataSource -> seek ( 0 );

	if ( stream )
	{
		ALint queued;

		alGetSourcei ( source,AL_BUFFERS_QUEUED,&queued );

		if ( queued > 0 )
			alSourceUnqueueBuffers ( source, 2, buffer );

		OpenAlContext :: unregisterSound ( this );

		currentBuffer = 0;
	}
}

void	Sound :: update ()
{
ALuint	error;

	if ( stream )
	{
		ALint processed;

		alGetSourcei ( source, AL_BUFFERS_PROCESSED, &processed );

//		if ( processed > 0 && looping && dataSource -> atEnd () )
//			dataSource -> seek ( 0 );

		if ( processed == 0 )
			return;

		if ( processed == 1 )
		{
			alSourceUnqueueBuffers ( source, 1, &buffer [currentBuffer] );

			int size = dataSource -> read ( buf, BUFFER_SIZE );

			if ( size > 0 || (size == 0 && looping) )
			{
				alBufferData         ( buffer [currentBuffer], format, buf, size,
				                       dataSource -> getFrequency () );

				alSourceQueueBuffers ( source, 1, &buffer [currentBuffer] );

				if ( size < BUFFER_SIZE && looping )
					dataSource -> seek ( 0 );
			}
			else
			{
				int queued;

				alGetSourcei ( source, AL_BUFFERS_QUEUED, &queued );

				if ( queued == 0 )
					dataSource -> seek ( 0 );
			}

			currentBuffer = 1 - currentBuffer;
		}
		else
		if ( processed == 2 )
		{
			alSourceUnqueueBuffers ( source, 2, buffer );

			currentBuffer = 0;

			play ();
		}
	}
}
