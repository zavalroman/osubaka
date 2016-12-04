//
// SoundData subclass to load wav files
//

#ifndef	__WAV_SOUND_DATA__
#define	__WAV_SOUND_DATA__

#include	"SoundData.h"

class	WavSoundData : public SoundData
{
	int	dataOffs;
	int	dataLength;

public:
	WavSoundData  ( const char * theFileName );
	WavSoundData  ( Data * data );
	~WavSoundData ();

	virtual	int	getSize () const;
											// fill buffer with next audio data
	virtual	int	read ( byte * buf, int size = -1 );

											// position in sound (in seconds)
	virtual	bool	seek ( float time );

	enum
	{
		RIFF = 0x46464952,
		WAVE = 0x45564157,
		FMT  = 0x20746D66,
		DATA = 0x61746164,
	};
};

#endif

