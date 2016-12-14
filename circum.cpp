/*
 *	circum.cpp 
 * 
 */

#define PI 3.1415926535

#include <iostream>
#include <math.h>

#include "circum.h"

//Circum::Circum()
//{
//}

void Circum::doMath()
{
	createCircum();
}

bool Circum::getBow ( float i, float intersecX, float intersecY, float R, bool last )
{
	float posX, posY;
	
	posX = intersecX + R * cos( i );
	posY = intersecY - R * sin( i ); 
	
	if ( curveX->size() > 0 )
	{	lenTest = pixelLength;
		float lenBuf = newSegmentLength( posX, posY );
		pixelLength += lenBuf;	
		
		if ( pixelLength > length )
		{	//cout << " SL PIXEL CIRCUM   " << slPixelLength << "    " << objects [ *j ].slLength << endl;
			float requireSegment = length - lenTest;
			requireSegment = requireSegment / lenBuf;
				
			float vecX = posX - curveX->back(); 
			float vecY = posY - curveY->back();
			
			vecX = vecX * requireSegment;
			vecY = vecY * requireSegment;
			
			posX = curveX->back() + vecX;
			posY = curveY->back() + vecY;
				
			lenBuf = newSegmentLength( posX, posY );
			lenTest += lenBuf;
			//cout << " LEN BUF   " << lenBuf << " lenTest   " << lenTest << endl;
			curveX->push_back( posX );
			curveY->push_back( posY );
			return true;
		}
	}
	
	if ( curveX->size() > 0 ) lenTest += newSegmentLength( posX, posY );
	
	curveX->push_back( posX );
	curveY->push_back( posY );
	
	if ( length > lenTest + 0.1 && last )
	{	//cout << " 		CHAECK CURCUM " << endl;
		float requireSegment = length - lenTest;
		
		float refX_2 = (float)controlX->at( 2 );
		float refY_2 = (float)controlY->at( 2 );
		
		float lenBuf = newSegmentLength( refX_2, refY_2 );
		requireSegment = requireSegment / lenBuf;
		
		float vecX = refX_2 - curveX->back(); 
		float vecY = refY_2 - curveY->back();
				
		vecX = vecX * requireSegment;
		vecY = vecY * requireSegment;
				
		posX = curveX->back() + vecX;
		posY = curveY->back() + vecY;
				
		lenTest += newSegmentLength ( posX, posY );
		curveX->push_back( posX );
		curveY->push_back( posY );
	}
	return false;
}

void Circum::createCircum()
{
	float midX_1, midY_1, midX_2, midY_2;
	float xA, yA, xB, yB, xC, yC, xD, yD, K, a, b, c, pi;
	float refX_0, refY_0, refX_1, refY_1, refX_2, refY_2;
	//bool dekita = false;
	
	refX_0 = (float)controlX->at( 0 ); 
	refY_0 = (float)controlY->at( 0 );
	refX_1 = (float)controlX->at( 1 );
	refY_1 = (float)controlY->at( 1 );
	refX_2 = (float)controlX->at( 2 );
	refY_2 = (float)controlY->at( 2 );
	
	midX_1 = ( refX_0 + refX_1 ) / 2.0; 
	midY_1 = ( refY_0 + refY_1 ) / 2.0;
	
	midX_2 = ( refX_1 + refX_2 ) / 2.0; 
	midY_2 = ( refY_1 + refY_2 ) / 2.0;
	
	xA = midX_1; 		yA = midY_1;
	xB = refX_1; 		yB = refY_1;
	
	K = ( xA - xB ) / ( yA - yB );
	
	b = 5;

	a =  0.0001 -  atan ( K );
	
	xC = xA + b * cos( a );
	yC = yA + b * sin( a );	

////////////////////////////////////////////////

	xA = midX_2; 		yA = midY_2;
	xB = refX_2; 		yB = refY_2;

	K = ( xA - xB ) / ( yA - yB );

	a =  0.0001 -  atan (  K );
	
	xD = xA + b * cos( a );
	yD = yA + b * sin( a );
	
	float T, W, L, M, G;
	
	K = yC - midY_1;
	T = midX_1 * midY_1 - midX_1 * yC;
	W = xC - midX_1;
	L = xD - midX_2;
	M = midX_2 * midY_2 - xD * midY_2;
	G = yD - midY_2;
	
	if ( W == 0 ) W = 0.00000001;   // а для G, L, K?
	
	float intersecX = ( T * L + W * ( L * midY_1 + M + G * midX_2 ) ) / ( W * G - K * L );
	
	float intersecY = ( ( intersecX * K + T ) / W ) + midY_1;
	
	//cout << " INTERSEC    " << intersecX << "     " << intersecY << endl; 
	float R;
	//R = sqrt ( pow ( intersecX - refX_0, 2 ) + 
	//					pow ( intersecY - refY_0, 2 ) );								  
	//cout << " R " << R ;  // сравнить и  лишнее удалить
	//R = sqrt ( pow ( intersecX - refX_1, 2 ) + 
	//					pow ( intersecY - refY_1, 2 ) );	 
	//cout << "       " << R ;
	R = sqrt ( pow ( intersecX - refX_2, 2 ) + 
						pow ( intersecY - refY_2, 2 ) );	 
	//cout << "      " << R << endl;
					 
	float angel = ( refX_0 - intersecX ) / R; 
	if ( angel > 1 ) angel = 1; if ( angel < -1 ) angel = -1;	 
	float startBow = acos( angel );	
	
	angel = ( refX_2 - intersecX ) / R;
	if ( angel > 1 ) angel = 1; if ( angel < -1 ) angel = -1;
	float stopBow = acos( angel );
	
	angel = ( refX_1 - intersecX ) / R;
	if ( angel > 1 ) angel = 1; if ( angel < -1 ) angel = -1;
	float midBow = acos( angel );
	
	if ( intersecY - refY_0 < 0 ) startBow = PI*2 - startBow;
	if ( intersecY - refY_2 < 0 ) stopBow = PI*2 - stopBow;
	if ( intersecY - refY_1 < 0 ) midBow = PI*2 - midBow;
	
	float CSTEP = 0.06; // в глобальную переменную? связать с безьёвским шагом
	
	if ( startBow < midBow && midBow < stopBow )
		for ( float i = startBow; i < stopBow; i += CSTEP  )
		{
			if ( i + CSTEP < stopBow )
			{
				if ( getBow ( i, intersecX, intersecY, R, false ) ) break;
			}
			else
			{
				getBow ( i, intersecX, intersecY, R, true );
			}
		}
	else
		if ( startBow > midBow && midBow > stopBow )
			for ( float i = startBow; i > stopBow; i -= CSTEP  )
				if ( i - CSTEP > stopBow )
				{
					if ( getBow ( i, intersecX, intersecY, R, false ) ) break;
				}
				else
				{
					getBow ( i, intersecX, intersecY, R, true );
				}
		else
			if ( startBow > midBow && midBow < stopBow && startBow > stopBow )
				for ( float i = -( 2*PI - startBow ); i < stopBow; i += CSTEP  )
					if ( i + CSTEP < stopBow )
					{
						if ( getBow ( i, intersecX, intersecY, R, false ) ) break;
					}
					else
					{
						getBow ( i, intersecX, intersecY, R, true );
					}
			else
				if ( startBow < midBow && midBow > stopBow && startBow < stopBow ) 
					for ( float i = startBow; i > -( 2*PI - stopBow ); i -= CSTEP  )
						if ( i - CSTEP > -( 2*PI - stopBow ) )
						{
							if ( getBow ( i, intersecX, intersecY, R, false ) ) break;
						}
						else
						{
							getBow ( i, intersecX, intersecY, R, true );
						}
				else
					if ( startBow < midBow && midBow > stopBow )
						for ( float i = -( 2*PI - startBow ); i < stopBow; i += CSTEP  )
							if ( i + CSTEP < stopBow )
							{
								if ( getBow ( i, intersecX, intersecY, R, false ) ) break;
							}
							else
							{
								getBow ( i, intersecX, intersecY, R, true );
							}
					else
						if ( startBow > midBow && midBow < stopBow )
							for ( float i = startBow; i > -( 2*PI - stopBow ); i -= CSTEP  )
								if ( i - CSTEP > -( 2*PI - stopBow ) )
								{
									if ( getBow ( i, intersecX, intersecY, R, false ) ) break;
								}
								else
								{
									getBow ( i, intersecX, intersecY, R, true );
								}
						else std::cout << " SLIDER CIRCUM CREATE ERROR " << std::endl;
}
