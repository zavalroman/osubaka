//
// Simple OpenAL wrapper
//
// Author: Alex V. Boreskoff <steps3d@narod.ru>, <alexboreskoff@mtu-net.ru>
//

#ifndef	__OPENAL_CONTEXT__
#define	__OPENAL_CONTEXT__

#include	<stdio.h>
#include	<AL/al.h>
#include	<AL/alc.h>
#include	"Vector3D.h"
#include	 <cstddef>

class	SoundData;
class	Sound;

class	OpenAlContext
{
protected:	
	ALCdevice  * device;					// device & context for working with OpenAL
	ALCcontext * context;
	Vector3D	 pos;						// listener's position
	Vector3D	 velocity;					// listeners velocity (for Doppler effect)
	Vector3D	 viewDir;					// listener's orientation - view and up vectors
	Vector3D	 upDir;

public:
	OpenAlContext  ();
	~OpenAlContext ();

	bool	isOk () const
	{
		return device != NULL && context != NULL;
	}

	const Vector3D&	getPos () const
	{
		return pos;
	}

	const Vector3D&	getVelocity () const
	{
		return velocity;
	}

	const Vector3D& getViewDir () const
	{
		return viewDir;
	}

	const Vector3D&	getUpDir () const
	{
		return upDir;
	}

	void	moveTo         ( const Vector3D& newPos );
	void	moveBy         ( const Vector3D& delta  );
	void	setVelocity    ( const Vector3D& newVel );
	void	setOrientation ( const Vector3D& view, const Vector3D& up );
	
	static	SoundData * open            ( /*const */ char * fileName );
	static	bool		registerSound   ( Sound * sound );
	static	bool		unregisterSound ( Sound * sound );
	static	void		updateSounds    ();
};

#endif

