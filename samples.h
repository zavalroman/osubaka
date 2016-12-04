/*
 * samples.h
 * 
 * 
 */
 
#ifndef SAMPLES_H
#define SAMPLES_H

#include <iostream>
#include <cstring>

#include "Sound/OpenAlContext.h"
#include "Sound/Sound.h"
#include "Sound/SoundData.h"

class Samples
{
public:
	Samples( const char* defaultPath, const char* skinPath );
	
	void playHitSound( int clickResult, int sampleType );
	void playHS( int j );
	
private:
	struct hs_set
	{
		SoundData* data;
		Sound* sound;
	};
	
	hs_set baseHs[21];
	
	OpenAlContext context; // прояснить момент в голову...
	
	SoundData* data_;
	Sound* sound_;
		
	const char* sections[3] = { "normal-", "soft-", "drum-" };
	const char* types[7] = { "hitnormal", "hitwhistle", "hitfinish", "hitclap", "sliderslide", "slidertick", "sliderwhistle" };

	
	void loadHitSound( int bit, const char* place, int hsSet );
};

#endif // SAMPLES_H
