//
// Sound data class for OpenAL
//

#ifndef	__SOUND_DATA__
#define	__SOUND_DATA__

#include	<stdio.h>
#include	"TypeDefs.h"

class	Data;

class	SoundData
{
protected:
	Data  * data;
	FILE  * fp;
	int		numChannels;
	int		frequency;
	int		bitsPerSample;
	bool	ok;
	int 	bitRate; //added by rooman 08.03.2015
	
public:
	SoundData ( Data * theData );
	SoundData ( const char * theFileName );
	virtual	~SoundData ();
	
	int getBitRate () //added by rooman 08.03.2015
	{
		return bitRate;
	}
	
	int	getNumChannels () const
	{
		return numChannels;
	}

	int	getFrequency () const
	{
		return frequency;
	}

	int	getBitsPerSample () const
	{
		return bitsPerSample;
	}
	
	virtual	bool	isOk () const;

											// get size in bytes of unpacked audio data
	virtual	int		getSize () const = 0;

											// fill buffer with next audio data
	virtual	int	read ( byte * buf, int size = -1 ) = 0;

											// position in sound (in seconds)
	virtual	bool	seek ( float time ) = 0;
	
											// whether we're at end of sound data
	virtual	bool	atEnd () const;
	
	virtual	int		getPos () const; //added by rooman 08.03.2015
	
};

#endif
