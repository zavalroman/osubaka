/*
* object.h
*  
*/

#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
	Object ();
	~Object();
	
	/*	color	*/
	float R, G, B, A;
	
	/*	vertites	*/
	float leftBottomX,  leftBottomY;
	float leftTopX,	    leftTopY;
	float rightTopX,    rightTopY;
	float rightBottomX, rightBottomY;
	
	/*	image size	*/
	int width, height;
	
	/*	texture id	*/
	int image;
	
	float x, y;
	
private:
	
};

#endif //OBJECT_H
