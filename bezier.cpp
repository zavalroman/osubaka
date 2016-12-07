/*
 *	bezier.cpp 
 * 
 */


#include <iostream>

#include "bezier.h"

Bezier::Bezier()
{
}

void Bezier::setControl( std::vector<int>& controlX, std::vector<int>& controlY )
{
	int bendStart, bendEnd, refNum;
	float tStep, msLength, ndLength = 0;
	std::vector<int>   slNodeAdr;	//links to nodes in slider
	std::vector<float> nodeLength;

	for ( size_t i = 0; i < objects[ j ].slRefPointX.size(); i++ )
	{
		if ( ( objects[ j ].slRefPointX[ i ] == objects[ j ].slRefPointX[ i + 1 ] &&
				   objects[ j ].slRefPointY[ i ] == objects[ j ].slRefPointY[ i + 1 ] ) ||
					i == objects[ j ].slRefPointX.size() - 1 )
		{
			slNodeAdr.push_back( i ); // необходимо ли -1? ниже проверить!
			nodeLength.push_back( ndLength );
			ndLength = 0;
		} else {
			ndLength += 
			sqrt ( pow( objects[ j ].slRefPointX[ i ] - objects[ j ].slRefPointX[ i + 1 ], 2 ) + 
						 pow( objects[ j ].slRefPointY[ i ] - objects[ j ].slRefPointY[ i + 1 ], 2 ) );						   
		}
	}
	
	ndLength = 0; // исключить?
	for ( size_t i = 0; i < nodeLength.size(); i++ ) 
		ndLength += nodeLength[ i ];
	
	slPixelLength = 0;
	bendStart = 0;
	for ( size_t i = 0; i < slNodeAdr.size(); i++ )
	{
		if ( i != 0 ) bendStart = bendEnd + 1;
		bendEnd = slNodeAdr [ i ]; // если слайдер начинается с узла?
		refNum = bendEnd - bendStart;
		tStep = nodeLength [ i ] * objects [ j ].slLength / ndLength;

		bool last = false;
		if ( i == slNodeAdr.size() - 1 ) last = true;
		if ( objects [ j ].slType [ 0 ] == 80  ) 
			createSliderCircum ( &j, &tStep );
		else
			createSliderBezier ( &j, &tStep, &refNum, &bendStart, last );
	}	

	slNodeAdr.clear();
	nodeLength.clear();
}
