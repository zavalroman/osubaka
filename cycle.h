/*
* cycle.h
*
*/

#ifndef CYCLE_H
#define CYCLE_H

#include "beatmap.h"

class Cycle : public Beatmap {
public:
	Cycle() : Beatmap() {
	
	}
	~Cycle() {
	}
	
	void setMSec( long currentTime ) {
		mSec = currentTime;
	}
	
protected:
	long mSec;
	
	struct tewiMaSlider // tewima_slider
	{	// active slider's perameters
		size_t j; //sliders index
		//int curveLength;
		float msLength;
		float ballMsStep;
		int startTime;
		int endTime;
		int ballCurrentStep;
		bool reverse;
	} tewi;
	
	std::vector<tewiMaSlider> activeSliders;
	std::vector<int> deletedSlider;
};

#endif // CYCLE_H
