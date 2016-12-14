/*
*	curve.h
*	
*/

#ifndef CURVE_H
#define CURVE_H

//#include <iostream>
#include <vector>

class Curve {
public:
	Curve() { 
		pixelLength = 0;
	};
	~Curve() {
		//delete curveX;
		//delete curveY;
	};

	void setControl( std::vector<int>* controlPointsX, std::vector<int>* controlPointsY ) {
		controlX = controlPointsX;
		controlY = controlPointsY;
		
		curveX = new std::vector<float>();
		curveY = new std::vector<float>();
	}
	
	void setLength( float curveLength ) {
		length = curveLength;
	}
	
	std::vector<float>* getCurveX() {
		return curveX;
	}
	std::vector<float>* getCurveY() {
		return curveY;
	}
	
	void reset() {
		length = 0;		
		curveX = 0;
		curveY = 0;
		lenTest = 0;
		pixelLength = 0;
	}
	
protected:		
	
	float length;
	float pixelLength;
	float lenTest;
	
	std::vector<int>* controlX;
	std::vector<int>* controlY;
	
	std::vector<float>* curveX;
	std::vector<float>* curveY;
	
	float newSegmentLength( float posX, float posY );

};

#endif // CURVE_H
