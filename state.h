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
		firstRenderObj 	   = 0;
		lastRenderObj      = 0;
		//postLastObj		   = 0;
		bufFirst           = -1;
		bufLast			   = 0;
		tpStep			   = 0;
		
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
	int getActiveSlLen( int j );
	float getActiveCurveX( int j, int i );
	float getActiveCurveY( int j, int i );
	int getCurveLen( int j );
	float getCurveX( int j, int i );
	float getCurveY( int j, int i );
	float getSlEndX( int j );
	float getSlEndY( int j );
	
	void timeFlow();
	int sliderCycle();
	
protected:
	long mSec;
	int firstRenderObj, lastRenderObj;
	
	struct tewiMaSlider // tewima_slider
	{	// active slider's perameters
		int objId;
		int slId; //sliders index // не надо?
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
