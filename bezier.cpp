/*
 *	bezier.cpp 
 * 
 */


#include <iostream>
#include <math.h>

#include "bezier.h"

//Bezier::Bezier()
//{
//}

void Bezier::doMath()
{
	int bendStart, bendEnd, refNum;
	float tStep, msLength, ndLength = 0;
	std::vector<int> slNodeAdr;	//links to nodes in slider
	std::vector<float> nodeLength;

	/*----------Linear length between control points------------------*/
	for ( int i = 0; i < controlX->size(); i++ )
	{
		if ( ( i == controlX->size() - 1 ) ||
			 ( controlX->at( i ) == controlX->at( i + 1 ) &&
			   controlY->at( i ) == controlY->at( i + 1 ) ) ) 
		{
			slNodeAdr.push_back( i ); // необходимо ли -1? ниже проверить!
			nodeLength.push_back( ndLength );
			ndLength = 0;
		} else {
			ndLength += sqrt ( pow( controlX->at( i ) - controlX->at( i + 1 ), 2 ) + 
							   pow( controlY->at( i ) - controlY->at( i + 1 ), 2 ) );						   
		}
	}
	/*--------------------Total linear lenght-------------------------*/
	ndLength = 0; // придумать другое имя?
	for ( int i = 0; i < nodeLength.size(); i++ ) 
		ndLength += nodeLength[ i ];
		
	/*---------Calc sampling frequency in nodes and go----------------*/
	pixelLength = 0;
	bendStart = 0;
	for ( int i = 0; i < slNodeAdr.size(); i++ )
	{
		if ( i != 0 ) bendStart = bendEnd + 1;
		bendEnd = slNodeAdr[ i ]; // если слайдер начинается с узла?
		refNum = bendEnd - bendStart;
		tStep = nodeLength[ i ] * length / ndLength;

		bool last = false;
		if ( i == slNodeAdr.size() - 1 ) last = true;
		
		createCurve( tStep, refNum, bendStart, last );
	}	
}

long double Bezier::f( int N ) 
{	//factorial
	if ( N < 0 )
		return 0;
	if ( N == 0 )
		return 1;
	else
		return N * f ( N - 1 );
}

float Bezier::getBezierBasis( int i, int n, float t )
{
	return ( f(n) / ( f(i) * f(n - i) ) ) * pow( t, i ) * pow( 1 - t, n - i );
}

float Bezier::newSegmentLength( float posX, float posY )
{
	return sqrt ( pow( curveX->back() - posX, 2 ) + 
				  pow( curveY->back() - posY, 2 ) );
}
	 
void Bezier::createCurve( float tStep, int refNum, int bendStart, bool last )
{	
	float posX, posY;
																										   // вынести 5.0 наверх?
	for ( float t = 0; t < 1 + ( 5.0 / tStep ); t += 5.0 / tStep  )  // с "5.0" что делать? глобальная переменная? 
	{
		if ( t > 1.0 ) t = 1.0;																		
		posX = 0.0;	 posY = 0.0;

		for ( int i = 0; i <= refNum; i++ ) {
			posX += getBezierBasis( i, refNum, t ) * controlX->at( bendStart + i );
			posY += getBezierBasis( i, refNum, t ) * controlY->at( bendStart + i );
		}
		
		if ( curveX->size() > 0 )
		{	lenTest = pixelLength;
			float lenBuf = newSegmentLength( posX, posY );
			pixelLength += lenBuf;	
		
			if ( pixelLength > length ) //return true;
			{
				float requireSegment = length - lenTest;
				requireSegment = requireSegment / lenBuf;
	 
				float vecX = posX - curveX->back(); 
				float vecY = posY - curveY->back();
				
				vecX = vecX * requireSegment; // возможно, вынести в curve.cpp
				vecY = vecY * requireSegment;
				
				posX = curveX->back() + vecX;
				posY = curveY->back() + vecY;
				//posX = ( objects [ *j ].curveX.back() + posX ) / 2.0; 
				//posY = ( objects [ *j ].curveY.back() + posY ) / 2.0;
				
				lenTest += newSegmentLength( posX, posY );
				curveX->push_back( posX );
				curveY->push_back( posY );
				std::cout << posX << "  " << posY << "\n";
				return;
			}
		}
		
		
		//lenTest = slPixelLength;
		if ( curveX->size() == 0 || !( posX == curveX->back() && //check for duplicate
									   posY == curveY->back() ) ) 
		{
			curveX->push_back( posX );
			curveY->push_back( posY );
			std::cout << posX << "  " << posY << "\n";
		}
		if ( t == 1.0 ) t = 2.0;
	}
	
	/*
	if ( objects [ *j ].slLength > lenTest + 0.1 && last )
	{	cout << "CHAECK  BEZIER    " << objects [ *j ].slLength - lenTest << endl;
		float requireSegment = objects [ *j ].slLength - lenTest;
		
		float refX_2 = (float)objects [ *j ].slRefPointX.back();
		float refY_2 = (float)objects [ *j ].slRefPointY.back();
		
		float lenBuf = newSegmentLength ( j, &refX_2, &refY_2 );
		requireSegment = requireSegment / lenBuf;
		
		float vecX = refX_2 - objects [ *j ].curveX.back(); 
		float vecY = refY_2 - objects [ *j ].curveY.back();
				
		vecX = vecX * requireSegment;
		vecY = vecY * requireSegment;
				
		posX = objects [ *j ].curveX.back() + vecX;
		posY = objects [ *j ].curveY.back() + vecY;
				
		lenTest += newSegmentLength ( j, &posX, &posY );
		objects [ *j ].curveX.push_back ( posX );
		objects [ *j ].curveY.push_back ( posY );
	}
	*/
}
