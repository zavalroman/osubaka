/*
*	bezier.h
*	
*/

#ifndef BEZIER_H
#define BEZIER_H

#include <vector>

class Bezier {
public:
	Bezier() {}
	~Bezier();
	
	void setControl( std::vector<int>& controlX, std::vector<int>& controlY );
	
	std::vector<float>* getCurveX() {
		return curveX;
	}
	std::vector<float>* getCurveY() {
		return curveY;
	}
	
private:
  
  std::vector<float>* curveX;
  std::vector<float>* curveY;
  
};

#endif // BEZIER_H
