
#include <math.h>

#include "curve.h"

//Curve::Curve()
//{
//}

float Curve::newSegmentLength( float posX, float posY )
{
	return sqrt ( pow( curveX->back() - posX, 2 ) + 
				  pow( curveY->back() - posY, 2 ) );
}
