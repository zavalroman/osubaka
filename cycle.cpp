/*
* cycle.cpp
*
*/

#include "cycle.h"

void Cycle::timeFlow( long mSec )
{
	while ( hitObjects[ firstRenderObj + 1 ].time <= mSec + approachTime ) firstRenderObj++;
	
	while ( hitObjects[ lastRenderObj ].time < mSec ) lastRenderObj++;

	while ( points[ tpStep + 1 ].offset <= mSec ) tpStep++;
}


int Cycle::sliderCycle( long mSec )
{
	int sound = 0;

	if ( firstRenderObj >= 0 ) // ?пояснить за изящность/при создании кривых перед игрой, убрать
	{	// create new ( active ) slider
		/* за ненадобностью
		if ( isSlider( firstRenderObj ) && bufFirst != firstRenderObj )
		{	//create curve for slider
			bufFirst = firstRenderObj; // bufFirst change to static local?
			creationCurve( firstRenderObj ); //size_t?
		}
		*/
		
		if ( bufLast != lastRenderObj && isSlider ( lastRenderObj - 1 ) )
		{   //new active slider
			bufLast = lastRenderObj;	// bufLast change to static local?
			
			tewi.j = hitObjects[ lastRenderObj - 1 ].sliderId;
			//tewiTemplar.curveLength = objects [ tewiTemplar.j ].curveX.size() - 1;   // -1 -1 -1??
			tewi.msLength = points[ tpStep ].slVelosity * sliders[ tewi.j ].length;
			tewi.ballMsStep = tewi.msLength / sliders[ tewi.j ].curveX.size(); // добавить минус?
			tewi.startTime = sliders[ tewi.j ].time;
			tewi.endTime = 0.5 + tewi.startTime + tewi.msLength * sliders[ tewi.j ].passes; //																														
			tewi.ballCurrentStep = 0;
			tewi.reverse = false;
			activeSliders.push_back( tewi );		
		}
	}
	
	for ( size_t i = 0; i < activeSliders.size(); i++ )
	{ //active sliders cycle
		if ( activeSliders[ i ].endTime < mSec ) { // delete active slider
			deletedSlider.push_back( activeSliders[ i ].j );	// DELETED SLIDER
			activeSliders.erase( activeSliders.begin() + i );
		}
		
		if ( !activeSliders [ i ].reverse )
		{ //cout << " reverse false " << endl;
			activeSliders[ i ].ballCurrentStep = 0.5 + (float)( mSec - activeSliders[ i ].startTime ) / activeSliders[ i ].ballMsStep; //calc new position for ball
					
			if ( activeSliders[ i ].ballCurrentStep > sliders[ activeSliders[ i ].j ].curveX.size() - 1 ) // совпадают ли крайние опорные элементы расчетным?
			{	//ball reverse
				activeSliders[ i ].ballCurrentStep = sliders[ activeSliders[ i ].j ].curveX.size() - 1; // единица!
				activeSliders[ i ].startTime += 0.5 + activeSliders[ i ].msLength;
				activeSliders[ i ].reverse = true;
				sound = 1;
			}
		} else {
			activeSliders[ i ].ballCurrentStep = 0.5 + sliders[ activeSliders[ i ].j ].curveX.size() - 1 - // единица
						( (float)( mSec - activeSliders[ i ].startTime ) / activeSliders[ i ].ballMsStep );
			
			if ( activeSliders[ i ].ballCurrentStep <= 0 ) {
				activeSliders[ i ].ballCurrentStep = 0;
				activeSliders[ i ].startTime += 0.5 + activeSliders[ i ].msLength;
				activeSliders[ i ].reverse = false;
				sound = 1;
			}
		}	
	}

	if ( sound == 1 && activeSliders[ 0 ].endTime > mSec + 40 )   // <-- велосипед какой-то // или всё же костыль?
		return 1; 
	return 0;
}
