//
// SoundData subclass to load ogg files
//

#ifndef	__OGG_SOUND_DATA__
#define	__OGG_SOUND_DATA__

#include	"SoundData.h"
#include	"Data.h"
#include	<vorbis/vorbisfile.h>

class	OggSoundData : public SoundData
{
	OggVorbis_File	file;
	vorbis_info	  * info;

public:
	OggSoundData  ( Data * theData );
	OggSoundData  ( const char * theFileName );
	~OggSoundData ();

	virtual	int	getSize () const;

											// fill buffer with next audio data
	virtual	int	read ( byte * buf, int size = -1 );

											// position in sound (in seconds)
	virtual	bool	seek ( float time );

protected:
	static	size_t readFunc  ( void * ptr, size_t size, size_t nmemb, void * datasource )
	{
		OggSoundData * dt   = (OggSoundData *) datasource;
		Data         * data = dt -> data;

		if ( data -> getPos () >= data -> getLength () )
  			return 0;

  		return (size_t)data -> getBytes ( ptr, size * nmemb );
	}

	static	int    seekFunc  ( void * datasource, ogg_int64_t offset, int whence )
	{
		OggSoundData * dt   = (OggSoundData *) datasource;
		Data         * data = dt -> data;

		if ( whence == SEEK_SET )
  			data -> seekAbs ( (int) offset );
		else
		if ( whence == SEEK_CUR )
  			data -> seekCur ( (int) offset );
		else
		if ( whence == SEEK_END )
  			data -> seekAbs ( data -> getLength () + (int) offset );

  		return data -> getPos ();
	}

	static	int    closeFunc ( void * datasource )
	{
		return 0;
	}

	static	long   tellFunc  ( void * datasource )
	{
		OggSoundData * dt   = (OggSoundData *) datasource;
		Data         * data = dt -> data;

		return data -> getPos ();
	}
};

#endif

