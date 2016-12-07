
/*
*	keyinput.cpp
* 
*/


void keyPressed( unsigned char key, int x, int y )
{	
	if ( key == 'z' || key == 'Z' )
	{	/*
		click = true;
		clickX = cursorX;
		clickY = cursorY;
		osuShunkan = mSec;
		osuKeyPressed = true;
		*/
		//cout << " Z pressed" << endl;
	}
		
	if ( key == 'x' || key == 'X' )
	{	/*
		click = true;
		clickX = cursorX;
		clickY = cursorY;
		osuShunkan = mSec;
		osuKeyPressed = true;
		*/
		//cout << " X pressed " << endl;
	}
	
	if (key == 'q')
	{	/*
		mSec += 5;
		cout << " mSec  " << mSec << endl;
		*/
	}
		
	if (key == 'w')
	{	/*
		mSec += 50;
		cout << " mSec  " << mSec << endl;
		*/
	}
	
	if (key == '1')
	{	/*
		samples -> playHS ( 0 );
		msDelay = 10;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '2')
	{	/*
		samples -> playHS ( 1 );
		msDelay = 20;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '3')
	{	/*
		samples -> playHS ( 2 );
		msDelay = 30;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '4')
	{	/*
		samples -> playHS ( 3 );
		msDelay = 40;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '5')
	{	/*
		samples -> playHS ( 4 );
		msDelay = 50;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '6')
	{	/*
		samples -> playHS ( 5 );
		msDelay = 60;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '7')
	{	/*
		samples -> playHS ( 6 );
		msDelay = 70;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '8')
	{	/*
		samples -> playHS ( 7 );
		msDelay = 80;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '9')
	{	/*
		samples -> playHS ( 8);
		msDelay = 90;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	
	if (key == '0')
	{	/*
		samples -> playHS ( 9 );
		msDelay = 100;
		cout << " msDelay  " << msDelay << endl;
		*/
	}
	//long filterMS;
	//gettimeofday ( &start, NULL );
	
	if ( key == 27 ) // ESC
	{	/*
		if ( stateGame )
		{
			stateGame = false;
			delete sound;

			delete analysis;
			delete beatmap;

			hitScores.clear();
		}
		return;
		*/
	}
	/*
	if ( !stateGame )
		interface -> doFilter ( key );
		*/
/*was commented
	gettimeofday ( &end, NULL );
	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	filterMS = ( ( seconds ) * 1000 + useconds / 1000.0 ) + 0.5;
	cout << "FILTER MS " << filterMS << endl;
*/	
/*
	keyStates [ key ] = true; //Set the state of the current key to pressed
	*/
}

void keyUp( unsigned char key, int x, int y )
{
	if (key == 'a')
	{
	}
	
	if ( key == 'x' || key == 'X' )
	{	/*
		osuKeyPressed = false;
		*/
	}
	
	if ( key == 'z' || key == 'Z' )
	{	/*
		osuKeyPressed = false;
		*/
	}
	/*
	keyStates [ key ] = false; //Set the state of the current key to not pressed
	*/
}

void keySpecial( int key, int x, int y )
{
	//if ( key == BSPACE )
	//{
		//cout << "BACKSPACE" << endl;
	//}
}

void keySpecialUp( int key, int x, int y )
{
	
}

void keyOperations()
{/*
	if ( keyStates [ 'a' ] )
	{	
	}
		
	if ( keyStates [ 'p' ] )
	{
		//sound -> play();
		//glutTimerFunc(0, timf, 0);
		//fps = 0;
		//Pause = false;
	}
		
	if ( keyStates [ 'h' ] )
	{
		//sound -> pause();
		//Pause = true;
	}
		
	if ( keyStates [ 's' ] )
	{
		//sound -> stop();
	}
		
	if ( keyStates [ 't' ] )
	{
		//timeFlag = true;
		//int pos = data -> getPos();
		//int bitRate = data -> getBitRate();
		//songTime = (unsigned)( ( double ) pos * 8.0 / ( bitRate / 1000 ) );
			
		//cout << songTime << endl;
	}
*/
}

