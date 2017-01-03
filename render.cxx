/*
 * render.cxx
 * 
 * 
 * 
 */


//void drawObject( float R, float G, float B, float xPos, float yPos, float circleSize, GLuint image )
/*
void drawObject( Object* object )
{
	glBindTexture( GL_TEXTURE_2D, 		 Object->imageId );	
	
	glBegin	     ( GL_QUADS );
	
	glColor4f	 ( Object->R, Object->G, Object->B,    Object->A );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( Object->leftBottomX,  Object->leftBottomY,  0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( Object->leftTopX, 	 Object->leftTopY,     0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( Object->rightTopX, 	 Object->rightTopY,    0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( Object->rightBottomX, Object->rightBottomY, 0 );
	
	glEnd();
	
}

void drawArray()
{
    //glDepthMask(true);

    //glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
    //glClear      ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glEnable 	( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable    ( GL_TEXTURE_2D );

    //glEnable(GL_DEPTH_TEST);
    //program1.bind();
    //program1.setUniformValue(matrixUniform1, modelview);
    program1.release();
    glDisable	( GL_DEPTH_TEST );

    GLfloat vertices[] = { i,i,
                           texture->width()+i,i,
                           texture->width()+i,texture->height()+i,
                           i,texture->height()+i,
                           i+200,i+200,
                           texture->width()+i+200,i+200,
                           texture->width()+i+200,texture->height()+i+200,
                           i+200,texture->height()+i+200
                         };
    GLfloat texVertices[] = { 0,0, 1,0, 1,1, 0,1,
                                0,0, 1,0, 1,1, 0,1};

    //glEnable ( GL_TEXTURE_2D );

    //glColor4f(1.0,0.0,0.0,0.5);
    glEnableClienthitPicture(GL_VERTEX_ARRAY);
    glEnableClienthitPicture(GL_TEXTURE_COORD_ARRAY_EXT);
    //glEnableClienthitPicture(GL_COLOR_ARRAY);
    texture->bind();

    //glColor4f(1.0,0.0,0.0,0.5);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
    glDrawArrays(GL_QUADS, 0, 8);
/*
    glBegin	( GL_QUADS );

        glColor4f	 ( 1.0, 1.0, 1.0, 1.0 );

        glTexCoord2f ( 0, 0 );
        glVertex3f   ( i, i, 0 );

        glTexCoord2f ( 0, 1 );
        glVertex3f	 ( texture->width()+i, i, 0 );

        glTexCoord2f ( 1, 1 );
        glVertex3f   ( texture->width()+i, texture->height()+i, 0 );

        glTexCoord2f ( 1, 0 );
        glVertex3f	 ( i, texture->height()+i, 0 );

    glEnd();

    //glEnableClienthitPicture(GL_COLOR_ARRAY);
    glDisableClienthitPicture(GL_TEXTURE_COORD_ARRAY_EXT);
    glDisableClienthitPicture(GL_VERTEX_ARRAY);

    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_BLEND );
}
*/


void circle( float R, float G, float B, float xPos, float yPos, float circleSize, GLuint image )
{
	glBindTexture ( GL_TEXTURE_2D, image );
	
	
	glBegin		 ( GL_QUADS );
	
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
	glBindTexture 	( GL_TEXTURE_2D, skin->hitCircle.index );
		
	glBegin		 ( GL_QUADS );
	
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

void drawObjects( void ) //  в друзья добавить?
{
	int j; 
	
	int firstObj = hitPicture->getFirstRenderObjId();
	int lastObj = hitPicture->getLastRenderObjId();
	
	/*-----------------pre activeSliders objects----------------------*/
	if ( firstObj >= 0 ) // что-то сделать с этим?
	{
		for ( int k = firstObj; k >= lastObj; k-- )
		{
			if ( hitPicture->isSlider( k ) ) 
			{
				for ( int i = 0; i < hitPicture->getCurveLen( k ); i++ )
					drawSliders( hitPicture->getCurveX( k, i ), hitPicture->getCurveY( k, i ) );// draw slider's body
				circle( 0.46,  0.79,    0,  hitPicture->getSlEndX( k ),  hitPicture->getSlEndY( k ), 0.4, skin->hitCircle.index );
				circle(  0.5, 	  1,  0.4,  hitPicture->getSlEndX( k ),  hitPicture->getSlEndY( k ), 0.4, skin->hitCircleOverlay.index );
				//if (  hitPicture->theRepeat( j ) ) { // draw repeate arrow
					//circle ( 1, 1, 1, hitPicture -> getSlEndX( k ),  hitPicture -> getSlEndY( k ), 0.4, skin -> reverseArrow.index );
				//}				
			}
			circle( 0.46, 0.79, 0,  hitPicture->getCircleX( k ),  hitPicture->getCircleY( k ), hitPicture->getApproachCircleSize( k ), skin->approachCircle.index );
			circle( 0.46, 0.79, 0,  hitPicture->getCircleX( k ),  hitPicture->getCircleY( k ), 0.4, skin->hitCircle.index );
			circle(    1, 	 1, 1,  hitPicture->getCircleX( k ),  hitPicture->getCircleY( k ), 0.4, skin->hitCircleOverlay.index );	
		}
	} else hitPicture->setFirstRenderObjId( 0 ); //?
	//std::cout << hitPicture->getActiveSlAmount() << std::endl;
	for ( int i = 0; i < hitPicture->getActiveSlAmount(); i++ )	{ // draw active sliders
		j = hitPicture->getActiveSlId( i );
		//std::cout << "active sl len " << hitPicture->getActiveSlLen( 0 ) << std::endl;
		for ( int l = 0 ; l < hitPicture->getCurveLen( j ); l++ ) {
			//std::cout << "for active " << hitPicture->getActiveCurveX( j, l ) << std::endl;
			drawSliders( hitPicture->getCurveX( j, l ), hitPicture->getCurveY( j, l ) );// draw body of slider
					
		}
		
		// draw end circle		
		circle( 0.46, 0.79,   0,  hitPicture->getSlEndX( j ),  hitPicture->getSlEndY( j ), 0.4, skin->hitCircle.index );
		circle(  0.5,    1, 0.4,  hitPicture->getSlEndX( j ),  hitPicture->getSlEndY( j ), 0.4, skin->hitCircleOverlay.index );
		// draw first circle
		circle( 0.46, 0.79, 0,  hitPicture->getCircleX( j ),  hitPicture->getCircleY( j ), 0.4, skin->hitCircle.index );
		circle(    1, 	 1, 1,  hitPicture->getCircleX( j ),  hitPicture->getCircleY( j ), 0.4, skin->hitCircleOverlay.index );
		//std::cout << "draw\n";
		/*
		if (  hitPicture->theRepeat( j ) ) // draw repeate arrow
			if ( hitPicture->getCurrentRep( j ) & 1 ) {
				circle( 1, 1, 1, hitPicture->getSlEndX( j ),  hitPicture->getSlEndY( j ), 0.4, skin->reverseArrow.index );
			} else {
				circle( 1, 1, 1, hitPicture->getObjX( j ),    hitPicture->getObjY( j ),   0.4, skin->reverseArrow.index );
			}	
		*/
		//	draw ball
		//ballX = hitPicture->getBallX( i ); // сделать локальной переменной?
		//ballY = hitPicture->getBallY( i );
		//drawBall( ballX, ballY );
		// draw follow circle	   !!!
	}

}
