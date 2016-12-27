/*
* state.h
*
*/

#ifndef STATE_H
#define STATE_H

#include "beatmap.h"

class State : public Beatmap {
public:
	State() : Beatmap() {
	
	}
	~State() {
	}
	
	void setTime( long currentTime ) {
		mSec = currentTime;
	}
	
	void setFirstRenderObjId( int j );
	int getFirstRenderObjId();
	int getLastRenderObjId();
	float getCircleX( int j );
	float getCircleY( int j );
	
	int getActiveSlId( int i );
	int getActiveSlAmount( void );
	int getCurveLen( int j );
	float getCurveX( int j, int i );
	float getCurveY( int j, int i );
	float getSlEndX( int j );
	float getSlEndY( int j );
	
	void timeFlow( long mSec );
	int sliderCycle( long mSec );
	
protected:
	long mSec;
	int firstRenderObj, lastRenderObj;
	
	struct tewiMaSlider // tewima_slider
	{	// active slider's perameters
		int j; //sliders index
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

#endif // State_H
