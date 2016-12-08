
#include "beatmap.h"

#include <iostream>
#include <fstream>
#include <cstring>
//#include <sstring>
#include <string>
//#include <regex>

Beatmap::Beatmap()
{
	
}

bool Beatmap::readHitObjects( const char* pathToOsuFile )
{
	bool hoFlag = false;
	int hoCount = 0;
	int slCount = 0;
	
	std::string line;
	std::fstream* osuFile = new std::fstream;
	
	osuFile->open( pathToOsuFile );
	
	if ( !osuFile ) {
		std::cout << "ERROR: osu file is not open\n";
		return false;
	}
	
	while ( getline( *osuFile, line ) ) {
		std::cout << line.length() << "\n";
		
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
				control.push_back( cpTemplar );
				control[ slCount ].hoId = hoCount;
				control[ slCount ].x.push_back( hitObjects[ hoCount ].x );
				control[ slCount ].y.push_back( hitObjects[ hoCount ].y );
				
				osuFile->get();
				osuFile->get( hitObjects[ hoCount ].slType[0] );
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
				*osuFile >> hitObjects[ hoCount ].slPasses;
				osuFile->get();
				*osuFile >> hitObjects[ hoCount ].slLength;
				osuFile->get();
				*osuFile >> hitObjects[ hoCount ].slEdgeSound;
				
				slCount++;
			} // endif slider
			//std::cout << hitObjects[ hoCount ].x << "  " << hitObjects[ hoCount ].y << std::endl;
			
			hoCount++;
		}
	}
	hitObjects.pop_back();
	
	osuFile->close();
	delete osuFile;
	return true;
}

bool Beatmap::generateSliders()
{
	int hoId;
	for ( int i = 0; i < slControl.size(); ++i ) {
		hoId = slControl[ i ].hoId;
		switch ( hitObjects[ hoId ].slType ) {
			case 'B': {
				
				break;
			}
			case 'P': {
				break;
			}
			//case 'C': {
			//	break;
			//}
			case 'L': {
				break;
			}
			default: {
				std::cout << "ERROR: slider type not found\n";
				return false;
			}
		}
	}
}
