/*
*	curve.h
*	
*/

#ifndef CURVE_H
#define CURVE_H

#include <vector>

class Curve {
public:
	Curve() { };
	~Curve();

	void setControl( std::vector<int>& controlPointsX, std::vector<int>& controlPointsY ) {
		controlX = controlPointsX;
		controlY = controlPointsY;
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
	
	std::vector<int>& controlX;
	std::vector<int>& controlY;
	
	std::vector<float>* curveX;
	std::vector<float>* curveY;

};

#endif // CURVE_H
