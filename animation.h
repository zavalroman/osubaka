/*
* animation.h
*
*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include "state.h"

class Animation : public State {
public:
	Animation() : State() {
	
	}
	~Animation() {
	}

	
	float getApproachCircleSize( int j, long mSec );
	
	
	
private:

};

#endif // ANIMATION_H
