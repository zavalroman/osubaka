
#include "picture.h"

//Picture::Picture()
//{

//}


float Picture::getApproachCircleSize( int j )
{
	return 0.35 + ( (float)( hitObjects[ j ].time - mSec ) * 0.9 )  / approachTime; // 0.9 & 0.35 to variables
}
	
