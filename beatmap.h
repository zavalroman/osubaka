
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
	bool createSliders();
	
	bool isSlider( int j ) {
		return hitObjects[ j ].sliderId == -1 ? false : true;
	}
	void reset() {
		bufLast = 0;
	}
	
protected:
	struct timingPoint // timing_point
	{
		int offset;
		float mpb;
		int timeSignature;
		int sampleType;
		int sampleSet;
		int volume;
		bool unknown;
		bool kiai;
		float slVelosity;
	} tempPoint;
	
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
	
	std::vector<timingPoint> 	points;
	std::vector<ControlPoints>  slControl;
	std::vector<Slider> 		sliders;
	std::vector<HitObject> 		hitObjects;
	
	/* Difficulty */
	float approachTime;
	int odTime;
	float slMulti;

	int tpStep;
	
	int bufFirst, bufLast, passCount;
	bool reverse;
};


#endif // BEATMAP_H
