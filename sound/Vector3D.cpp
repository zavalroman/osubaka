//
// Basic class for 3d vectors.
// Supports all basic vector operations
//
// Author: Alex V. Boreskoff
//

#include	<stdlib.h>
#include	"Vector3D.h"
/*
static	inline	float	rnd ()		// return float random number in [-1,1]
{
	return 2.0f * float ( rand () ) / float ( RAND_MAX ) - 1.0f;
}
*/
Vector3D	Vector3D :: getRandomVector ( float len )
{
	Vector3D	v;

	for ( ; ; )
	{
		v.x = 0;//rnd ();
		v.y = 0;//rnd ();
		v.z = 0;//rnd ();

		if ( v.lengthSq () < EPS )
			continue;

		v *= len / v.length ();

		return v;
	}
}

Vector3D&	Vector3D :: clamp ( float lower, float upper )
{
	if ( x < lower )
		x = lower;
	else
	if ( x > upper )
		x = upper;

	if ( y < lower )
		y = lower;
	else
	if ( y > upper )
		y = upper;
			
	if ( z < lower )
		z = lower;
	else
	if ( z > upper )
		z = upper;

	return *this;
}

