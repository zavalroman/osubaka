//
// Sound source wrapper for OpenAL
//
// Author: Alex V. Boreskoff
//

#ifndef	__SOUND_SOURCE__
#define	__SOUND_SOURCE__

#include	<AL/al.h>
#include	<AL/alc.h>
#include	"Vector3D.h"
#include	"TypeDefs.h"					// for byte, uint16 & etc
//#include "iostream"

class	Data;
class	SoundData;

class	Sound
{
protected:
	SoundData * dataSource;
	bool		looping;
	bool		stream;
	ALuint		format;
	ALuint		source;
	ALuint		buffer [2];						// id's of OpenAL buffers
	int			currentBuffer;
	byte      * buf;							// buffer for sound data
	Vector3D	pos;						 	// sound source position
	Vector3D	velocity;						// sound source velocity
	float		pitch;
	float		gain;

public:
	Sound  ( SoundData * data, bool theLoop = false );
	~Sound ();

	const Vector3D&	getPos () const
	{
		return pos;
	}

	const Vector3D&	getVelocity () const
	{
		return velocity;
	}

	float	getGain () const
	{
		return gain;
	}

	float	getPitch () const
	{
		return pitch;
	}

	bool	getLooping () const
	{
		return looping;
	}

	bool	isPlaying () const;
	bool	atEnd     () const;
	
	void	setPos      ( const Vector3D& newPos );
	void	setVelocity ( const Vector3D& newVel );
	void	setPitch    ( float newPitch );
	void	setGain     ( float newGain  );
	void	setLooping  ( bool flag      );

	void	play   ();
	void	pause  ();
	void	stop   ();
	void	rewind ();
	void	update ();

	enum
	{
		BUFFER_SIZE = 512536 //default 65536. changed by rooman
	};
};

#endif
