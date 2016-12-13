/*
*	bezier.h
*	
*/

#ifndef BEZIER_H
#define BEZIER_H

#include <vector>

#include "curve.h"

class Bezier : public Curve {
public:
	Bezier() : Curve () {
		
	};
	~Bezier() {
		
	};
	
	void doMath();
	
private:
	float lenTest;

	long double f ( int N );
	float getBezierBasis( int i, int n, float t );
	float newSegmentLength( float posX, float posY );
	void createCurve( float tStep, int refNum, int bendStart, bool last );
  
  
};

#endif // BEZIER_H
