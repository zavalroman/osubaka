
/*
*	Beatmap.h
* 
*/

#ifndef BEATMAP_H
#define BEATMAP_H

#include <vector>

class Beatmap {
public:
	Beatmap( const char* pathToOsuFile );
private:

	int vers;
	/*	General	*/
	char* AudioFilename;

	struct HitObject
	{
		int 	x;
		int 	y;
		int 	time;
		int 	type;
		int 	hitSound;
		char 	slType[1];
		std::vector<int> slControlX; 
		std::vector<int> slControlY;
		std::vector<float> curveX;
		std::vector<float> curveY;
		int 	slPasses;
		float 	slLength;
		int 	slEdgeSound;
		//...additional
	} objTemplar;
	
	std::vector<HitObject> hitObjects;
};


#endif // BEATMAP_H
