
/*
*	beatmap.h
* 
*/

#ifndef BEATMAP_H
#define BEATMAP_H

#include <vector>

class Beatmap {
public:
	Beatmap();
	~Beatmap() {
		for ( int i = 0; i < hitObjects.size(); i++ ) {
			delete sliders[ i ].curveX;
			delete sliders[ i ].curveY;
		}
	}
	bool readHitObjects( const char* pathToOsuFile );
	bool generateSliders();
	
private:	
	struct ControlPoints {
		std::vector<int> x;
		std::vector<int> y;
	} cpTemplar;
	
	struct Slider {
		char 	type[1];
		std::vector<float>* curveX;
		std::vector<float>* curveY;
		int 	passes;
		float 	length;
		int 	edgeSound;
	} slTemplar;
	
	struct HitObject {
		int 	x;
		int 	y;
		int 	time;
		int 	type;
		int 	hitSound;
		
		int 	sliderId;
		//...additional
	} objTemplar;
	
	std::vector<ControlPoints> slControl;
	std::vector<Slider> sliders;
	std::vector<HitObject> hitObjects;
	
	
};


#endif // BEATMAP_H
