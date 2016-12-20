

float activeSliderEndCircleX, activeSliderEndCircleY;

void drawHitScore ( float R, float G, float B, float xPos, float yPos, float circleSize, size_t type )
{
	ILuint image;
	
	if ( type & 64 ) {
		image = (ILuint)skin->hit300.index;
		circleSize *= 2;
	} else
		if ( type & 32 ) {
			image = (ILuint)skin->hit100.index;
		} else
			if ( type & 16 ) {
				image = (ILuint)skin->hit50.index;
			} else
			{
				image = (ILuint)skin->hit0.index;
			}
			/*
	switch ( type )
	{
		case 0 : 
		{
			image = (ILuint)skin -> hit0.index;
			break;
		}
		case 50 : 
		{
			image = (ILuint)skin -> hit50.index;
			break;
		}
		case 100 : 
		{
			image = (ILuint)skin -> hit100.index;
			break;
		}
		case 300 : 
		{
			image = (ILuint)skin -> hit300.index;
			circleSize *= 2;
			break;
		}
	}
	*/
	glBindTexture 	( GL_TEXTURE_2D, image );
	
	glBegin	( GL_QUADS );
	
	glColor3f	 ( R, G, B );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( xPos-circleSize, yPos-circleSize, 0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( xPos-circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( xPos+circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( xPos+circleSize, yPos-circleSize, 0 );
	
	glEnd();
	
}

void circle ( float R, float G, float B, float xPos, float yPos, float circleSize, GLuint image )
{
	glBindTexture 	( GL_TEXTURE_2D, image );
	
	
	glBegin	( GL_QUADS );
	
	glColor3f	 ( R, G, B );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( xPos-circleSize, yPos-circleSize, 0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( xPos-circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( xPos+circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( xPos+circleSize, yPos-circleSize, 0 );
	
	glEnd();
	
}

void drawSliders ( float xPos, float yPos )
{
	float circleSize = 0.38;
	glBindTexture 	( GL_TEXTURE_2D, skin->hitCircleOverlay.index );
		
	glBegin	( GL_QUADS );
	
	glColor4f	 ( 1, 1, 1, 0.3 );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( xPos-circleSize, yPos-circleSize, 0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( xPos-circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( xPos+circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( xPos+circleSize, yPos-circleSize, 0 );
	
	glEnd();
}

void drawBall ( float xPos, float yPos )
{	
	float circleSize = 0.4;

	glEnable	  	( GL_TEXTURE_2D );
	
	glBindTexture 	( GL_TEXTURE_2D, skin->sliderB0.index );
	
	glBegin	( GL_QUADS );
	
	glColor4f	 ( 1, 1, 1, 1 );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( xPos-circleSize, yPos-circleSize, 0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( xPos-circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( xPos+circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( xPos+circleSize, yPos-circleSize, 0 );
	
	glEnd();
	
}

void drawFollowCircle ()
{	
	float circleSize = 0.75;
	
	float xPos = ballX;
	float yPos = ballY;
	glEnable	  	( GL_TEXTURE_2D );
	
	glBindTexture 	( GL_TEXTURE_2D, skin->sliderFollowCircle.index );
	
	glBegin	( GL_QUADS );
	
	glColor4f	 ( 1, 1, 1, 1 );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( xPos-circleSize, yPos-circleSize, 0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( xPos-circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( xPos+circleSize, yPos+circleSize, 0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( xPos+circleSize, yPos-circleSize, 0 );
	
	glEnd();
	
}

void drawObjects( void ) //  в друзья добавить?
{
	int j; 
	
	/*					pre activeSliders objects 					*/
	if ( beatmap->firstRenderObj >= 0 ) // что-то сделать с этим?
	{
		for ( int k = beatmap->firstRenderObj; k >= beatmap->lastRenderObj; k-- )
		{
			if ( beatmap->isSlider( k ) ) 
			{
				for ( int i = 0; i < beatmap->getCurveLen( k ); i++ )
					drawSliders ( beatmap->getCurveX( k, i ), beatmap->getCurveY( k, i ) );// draw slider's body
				circle( 0.46,  0.79,    0,  beatmap->getSlEndX( k ),  beatmap->getSlEndY( k ), 0.4, skin->hitCircle.index );
				circle(  0.5, 	  1,  0.4,  beatmap->getSlEndX( k ),  beatmap->getSlEndY( k ), 0.4, skin->hitCircleOverlay.index );
				if (  beatmap->theRepeat( j ) ) { // draw repeate arrow
					circle ( 1, 1, 1, beatmap -> getSlEndX( k ),  beatmap -> getSlEndY( k ), 0.4, skin -> reverseArrow.index );
				}				
			}
			circle( 0.46, 0.79, 0,  beatmap->getObjX( k ),  beatmap->getObjY( k ), beatmap->getApproachCircleSize( k, mSec ), skin->approachCircle.index );
			circle( 0.46, 0.79, 0,  beatmap->getObjX( k ),  beatmap->getObjY( k ), 0.4, skin->hitCircle.index );
			circle(    1, 	 1, 1,  beatmap->getObjX( k ),  beatmap->getObjY( k ), 0.4, skin->hitCircleOverlay.index );		
		}
	} else beatmap->firstRenderObj = 0; //?
	
	for ( int i = 0; i < beatmap->getActiveSlAmount(); i++ )	{ // draw active sliders
		j = beatmap->getActiveSlId( i );
		for ( int l = 0 ; l < beatmap->getCurveLen( j ); l++ )
					drawSliders( beatmap->getCurveX( j, l ), beatmap->getCurveY( j, l ) );// draw body of slider
		// draw end circle			
		circle( 0.46, 0.79,   0,  beatmap->getSlEndX( j ),  beatmap->getSlEndY( j ), 0.4, skin->hitCircle.index );
		circle(  0.5,    1, 0.4,  beatmap->getSlEndX( j ),  beatmap->getSlEndY( j ), 0.4, skin->hitCircleOverlay.index );
		// draw first circle
		circle( 0.46, 0.79, 0,  beatmap->getObjX( j ),  beatmap->getObjY( j ), 0.4, skin->hitCircle.index );
		circle(    1, 	 1, 1,  beatmap->getObjX( j ),  beatmap->getObjY( j ), 0.4, skin->hitCircleOverlay.index );
		/*
		if (  beatmap->theRepeat( j ) ) // draw repeate arrow
			if ( beatmap->getCurrentRep( j ) & 1 ) {
				circle( 1, 1, 1, beatmap->getSlEndX( j ),  beatmap->getSlEndY( j ), 0.4, skin->reverseArrow.index );
			} else {
				circle( 1, 1, 1, beatmap->getObjX( j ),    beatmap->getObjY( j ),   0.4, skin->reverseArrow.index );
			}	
		*/
		//	draw ball
		ballX = beatmap->getBallX( i ); // сделать локальной переменной?
		ballY = beatmap->getBallY( i );
		drawBall( ballX, ballY );
		// draw follow circle	   !!!
	}

}
