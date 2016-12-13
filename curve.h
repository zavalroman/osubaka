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
	
protected:		
	
	float length;
	float pixelLength;
	
	
	std::vector<int>* controlX;
	std::vector<int>* controlY;
	
	std::vector<float>* curveX;
	std::vector<float>* curveY;
	

};

#endif // CURVE_H
