/*
* object.h
*  
*/

#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
	Object () {};
	~Object();
	
	float R, G, B, A;
	float leftBottomX,  leftBottomY;
	float leftTopX,	    leftTopY;
	float rightTopX,    rightTopY;
	float rightBottomX, rightBottomY;
	
};

#endif //OBJECT_H
