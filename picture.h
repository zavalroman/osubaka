/*
* picture.h
*
*/

#ifndef PICTURE_H
#define PICTURE_H

#include "state.h"

class Picture : public State {
public:
	Picture() : State() {
		approachTime = 500.0;
	}
	~Picture() {
	}

	void setApproachTime( float approachMSec ) {
		approachTime = approachMSec;
	}
	
	float getApproachCircleSize( int j );
	
	
	
private:
	//float approachTime;

};

#endif // PICTURE_H
