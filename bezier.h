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

	long double f ( int N );
	float getBezierBasis( int i, int n, float t );
	void createCurve( float tStep, int refNum, int bendStart, bool last );
  
  
};

#endif // BEZIER_H
