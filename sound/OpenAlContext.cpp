//
// Simple OpenAL wrapper
//
// Author: Alex V. Boreskoff <steps3d@narod.ru>, <alexboreskoff@mtu-net.ru>
//
#include	<cstring>
#include	<string>
#include	<map>
#include	<list>

using namespace std;

#include	"OpenAlContext.h"
#include	"Data.h"
#include	"OggSoundData.h"
#include	"WavSoundData.h"
#include	"Mp3SoundData.h"
#include	"Sound.h"

OpenAlContext :: OpenAlContext () : pos ( 0, 0, 0 ), velocity ( 0, 0, 0 ), viewDir ( 1, 0, 0 ), upDir ( 0, 0, 1 )
{
	device  = NULL;
	context = NULL;

	device = alcOpenDevice ( NULL );
	
	if ( device == NULL )
		return;

	context = alcCreateContext ( device, NULL );

	if ( context == NULL )
		return;

	alcMakeContextCurrent ( context );

											// set listener's properties
	moveTo         ( pos );
	setVelocity    ( velocity );
	setOrientation ( viewDir, upDir );
}

OpenAlContext :: ~OpenAlContext ()
{
	alcDestroyContext ( context );
	alcCloseDevice    ( device  );
}

void	OpenAlContext :: moveTo ( const Vector3D& newPos )
{
	pos = newPos;

	alListenerfv ( AL_POSITION, pos );
}

void	OpenAlContext :: moveBy ( const Vector3D& delta  )
{
	moveTo ( pos + delta );
}

void	OpenAlContext :: setVelocity ( const Vector3D& newVel )
{
	velocity = newVel;

	alListenerfv ( AL_VELOCITY, velocity );
}

void	OpenAlContext :: setOrientation ( const Vector3D& view, const Vector3D& up )
{
	viewDir = view;
	upDir   = up;

	float	orient [6];

	orient [0] = viewDir.x;
	orient [1] = viewDir.y;
	orient [2] = viewDir.z;
	orient [3] = upDir.x;
	orient [4] = upDir.y;
	orient [5] = upDir.z;

	alListenerfv ( AL_ORIENTATION, orient );
}

////////////////////////////////////////////////////////////////////////////////////////////////

//static	map <string, >	decoders;
static	list <Sound *>	sounds;

SoundData * OpenAlContext :: open ( /*const */char * fileName )
{
	char * ext = strrchr ( fileName, '.' );
	/*
	int i = filename.size();
    string buf;
    while((filename[i] != '.') && (i > 0))
    {
        buf = filename[i--] + buf;
        		
    }
	*/
	if ( ext == NULL )
		return NULL;
		
	Data * data = new Data ( fileName );

	if ( data == NULL )
		return NULL;
		
	SoundData * snd = NULL;
	
	if ( !strcmp ( ext + 1, "ogg" ) )
	{
		snd = new OggSoundData ( data );
	} else
	if ( !strcmp ( ext + 1, "wav" ) )
	{
		snd = new WavSoundData ( data );
	} else
	if ( !strcmp ( ext + 1, "mp3" ) )
	{
		snd = new Mp3SoundData ( data );
	}	
	
	if ( snd == NULL )
		return NULL;
		
	if ( snd -> isOk () )
		return snd;
		
	delete snd;
	
	return NULL;
}

bool	OpenAlContext :: registerSound ( Sound * sound )
{
	for ( list <Sound *> :: iterator it = sounds.begin (); it != sounds.end (); ++it )
		if ( *it == sound )
			return false;
	
	sounds.push_back ( sound );
	
	return true;
}

bool	OpenAlContext :: unregisterSound ( Sound * sound )
{
	for ( list <Sound *> :: iterator it = sounds.begin (); it != sounds.end (); ++it )
		if ( *it == sound )
		{
			sounds.erase ( it );
			
			return true;
		}
		
	return false;
}

void	OpenAlContext :: updateSounds ()
{
	for ( list <Sound *> :: iterator it = sounds.begin (); it != sounds.end (); ++it )
		(*it) -> update ();
}

