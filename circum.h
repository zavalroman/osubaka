/*
*	circum.h
*	
*/

#ifndef CIRCUM_H
#define CIRCUM_H

#include <vector>

#include "curve.h"

class Circum : public Curve {
public:
	Circum() : Curve () {
		
	};
	~Circum() {
		
	};
	
	void doMath();
	
private:
	bool getBow( float i, float intersecX, float intersecY, float R, bool last );
	void createCircum();

};

#endif // CIRCUM_H
