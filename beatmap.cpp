
#include "beatmap.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
//#include <stdlib.h>
#include <cmath>

#include "bezier.h"
#include "circum.h"

Beatmap::Beatmap()
{
	
}

bool Beatmap::readHitObjects( const char* pathToOsuFile )
{
	bool hoFlag = false;
	bool tpFlag = false;
	int hoCount = 0;
	int slCount = 0;
	char comma;
	char slMuChar[50];
	
	std::string line;
	std::fstream* osuFile = new std::fstream;
	
	osuFile->open( pathToOsuFile );
	
	if ( !osuFile ) {
		std::cout << "ERROR: osu file is not open\n";
		return false;
	}
	
	while ( getline( *osuFile, line ) ) {
		//std::cout << line.length() << "\n";
		
		if ( line.find("SliderMultiplier:") != std::string::npos ) {
			strcpy( slMuChar, line.c_str() );	// ПЕРЕДЕЛАТЬ &strBuf [ 17 ]
			slMuChar[0] = slMuChar[17];
			slMuChar[1] = slMuChar[18];
			slMuChar[2] = slMuChar[19];
			slMulti = atof( slMuChar );			
		}
			
		/*---------------------[TimingPoints]-------------------------*/
		if ( tpFlag && line.size() == 1 ) tpFlag = false;
			
		if ( tpFlag ) // tpFlag rename pls - why?
		{	// эй-эй! а не заменить ли все считываения строки на эту функцию? - зачем?				
			std::istringstream( line ) >> tempPoint.offset >> comma >> tempPoint.mpb >> comma 
				>> tempPoint.timeSignature >> comma >> tempPoint.sampleType >> comma
					>> tempPoint.sampleSet >> 	comma >> tempPoint.volume >> comma
						>> tempPoint.unknown >>  comma >> tempPoint.kiai;
				
			float MPB, mpbFactor; 	
			if ( tempPoint.mpb < 0 ) {
				mpbFactor = fabs( tempPoint.mpb / 100 );
			} else {
				MPB = tempPoint.mpb;
				mpbFactor = 1;
			}
			tempPoint.slVelosity = ( MPB * mpbFactor ) / ( slMulti * 100 );
			
			points.push_back ( tempPoint );
		}
			
		if ( line.find("[TimingPoints]") != std::string::npos ) tpFlag = true;
		
		/*-----------------------[HitObjects]-------------------------*/
		if ( line.find("[HitObjects]") != std::string::npos )
			hoFlag = true;
		
		if ( hoFlag ) {
			hitObjects.push_back( objTemplar );
			
			*osuFile >> hitObjects[ hoCount ].x;
			osuFile->get(); // missing comma
			
			*osuFile >> hitObjects[ hoCount ].y;
			osuFile->get();
			
			*osuFile >> hitObjects[ hoCount ].time;
			osuFile->get();
			
			*osuFile >>	hitObjects[ hoCount ].type;
			osuFile->get();
			
			*osuFile >> hitObjects[ hoCount ].hitSound;
		
			/*
			cirles
			1 ==  0000 0000 0000 0001
			?5 == 0000 0000 0000 0101
			sliders
			2 ==  0000 0000 0000 0010
			6 ==  0000 0000 0000 0110
			22 == 0000 0000 0001 0110
			38 == 0000 0000 0010 0110
			spinners
			12 == 0000 0000 0000 1100
			*/
			
			//if ( intBuf == 2 || intBuf == 6 || intBuf == 22 || intBuf == 38 ) // if slider
			if ( hitObjects[ hoCount ].type & 2 ) { // if slider
				slControl.push_back( cpTemplar );
				  sliders.push_back( slTemplar );
				
				hitObjects[ hoCount ].sliderId = slCount;
				
				slControl[ slCount ].x.push_back( hitObjects[ hoCount ].x );
				slControl[ slCount ].y.push_back( hitObjects[ hoCount ].y );
				
				osuFile->get();
				osuFile->get( sliders[ slCount ].type[0] );
				osuFile->get();
					
				int j = 1;	
				char catchComma = 0;
				while ( catchComma != ',' ) {
					slControl[ slCount ].x.push_back( j ); // create new slot in vector
					slControl[ slCount ].y.push_back( j );	
				
					*osuFile >> slControl[ slCount ].x[ j ];
					osuFile->get();
					*osuFile >> slControl[ slCount ].y[ j ];
					osuFile->get( catchComma );
				
					j++;
				}		
				*osuFile >> sliders[ slCount ].passes;
				osuFile->get();
				*osuFile >> sliders[ slCount ].length;
				osuFile->get();
				*osuFile >> sliders[ slCount ].edgeSound;
				
				slCount++;
			} else {
				hitObjects[ hoCount ].sliderId = -1;
			}
			//std::cout << hitObjects[ hoCount ].x << "  " << hitObjects[ hoCount ].y << std::endl;
			
			hoCount++;
		}
	}
	hitObjects.pop_back();
	
	osuFile->close();
	delete osuFile;
	return true;
}

bool Beatmap::createSliders()
{
	Bezier bezier;
	Circum circum;
	
	for ( int i = 0; i < slControl.size(); ++i ) {
		if ( sliders[ i ].type[0] == 'P' ) {		
			circum.setControl( &slControl[ i ].x, &slControl[ i ].y );
			circum.setLength( sliders[ i ].length );
			circum.doMath();
			sliders[ i ].curveX = circum.getCurveX();
			sliders[ i ].curveY = circum.getCurveY();
			circum.reset();
		} else {
			bezier.setControl( &slControl[ i ].x, &slControl[ i ].y );
			bezier.setLength( sliders[ i ].length );
			bezier.doMath();
			sliders[ i ].curveX = bezier.getCurveX();
			sliders[ i ].curveY = bezier.getCurveY();
			bezier.reset();
		}
	}
/*
	for ( int i = 0; i < sliders.size(); i++ ) {
		std::cout << sliders[i].type[0] << std::endl;
		for ( int j = 0; j < sliders[ i ].curveX->size(); j++ ) {
			std::cout << sliders[i].curveX->at(j) << "   " << sliders[i].curveY->at(j) << std::endl;
		}
	}
*/
}

