
#include "beatmap.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstring>
#include <regex>

Beatmap::Beatmap( const char* pathToOsuFile )
{
	bool hoFlag = false;
	int hoCount = 0;
	
	string line;
	fstream* osuFile = new fstream;
	
	osuFile->open( pathToOsuFile );
	
	if ( !osuFile ) {
		std::cout << "Error occured while open osu file\n";
		return;
	}
	
	
	
	while ( getline( *osuFile, line ) ) {
		if ( strBuf.find("[HithitObjects]") != std::string::npos )
			hoFlag = true
		
		if ( hoFlag ) {
			hitObjects.push_back( objTemplar );
			
			*osuFile >> hitObjects[ hoCount ].x;
			hitObjects[ hoCount ].slControlX.push_back( hitObjects[ hoCount ].x );
			osuFile->get(); // missing comma
			
			*osuFile >> hitObjects[ hoCount ].y;
			hitObjects[ hoCount ].slControlY.push_back( hitObjects[ hoCount ].y );
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
			if ( hitObjects[ hoCount ].type & 2 ) // if slider
			{
				osuFile->get();
				osuFile->get( hitObjects[ hoCount ].slType[0] );
				osuFile->get();
					
				int j = 1;	
				char catchComma = 0;
				while ( catchComma != ',' )
				{
					hitObjects[ hoCount ].slControlX.push_back( j ); // create new slot in vector
					hitObjects[ hoCount ].slControlY.push_back( j );	
				
					*osuFile >> hitObjects[ hoCount ].slControlX[ j ];
					osuFile->get();
					*osuFile >> hitObjects[ hoCount ].slControlY[ j ];
					osuFile->get( catchComma );
				
					j++;
				}		
				*osuFile >> hitObjects [ hoCount ].slPasses;
				osuFile->get();
				*osuFile >> hitObjects [ hoCount ].slLength;
				osuFile->get();
				*osuFile >> hitObjects [ hoCount ].slEdgeSound;
			}
			hoCount++;
		}
	}
	
	
	delete osuFile;
}
