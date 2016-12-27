/*
*	main.cpp
*	osu!baka
*	g++ *cpp -o osubaka -lGL -lGLU -lglut
*/

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <sys/time.h>

#include "skin.h"
#include "picture.h"

struct timeval start, end;
long  mSec, seconds, useconds;

Skin* skin;
Picture* hitPicture;

float ballX;
float ballY;

#include "keyinput.cxx"
#include "render.cxx"
#include "skin.cxx"

void display( void )
{
	/*-------------------------getting milliseconds-----------------------*/			
	gettimeofday ( &end, NULL );
	seconds = end.tv_sec - start.tv_sec;					// вынести в функцию
	useconds = end.tv_usec - start.tv_usec;
	mSec = ( ( seconds ) * 1000 + useconds / 1000.0 ) + 0.5;
	
	//mSec -= msDelay;	 // offset
	/*-------------------------END milliseconds-----------------------*/
		
	hitPicture->timeFlow( mSec );
	hitPicture->sliderCycle( mSec );
	drawObjects();
	
	/*-----------------Clear display---------------------------*/	
	glClearColor	( 0.0f, 0.0f, 0.0f, 1.0f );
	//glClearDepth  ( 1.0 );
	glClear			( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //Clear the color buffer (more buffers later on)
	/*------------------END Clear----------------------------*/
	
	
	glutSwapBuffers();
	glutPostRedisplay(); 
}

void reshape( int width, int height )
{
	glViewport		( 0, 0, (GLsizei)width, (GLsizei)height ); //Set our viewport to the size of our window
	glMatrixMode	( GL_PROJECTION ); //Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity	(); //Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective	( 60, (GLfloat)width / (GLfloat)height, 1.0, 100.0 ); //Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode	( GL_MODELVIEW ); //Switch back to the model view matrix, so that we can start drawing shapes correctly	
}

int main( int argc, char** argv )
{
	//gettimeofday ( &start, NULL );
	
	glutInit				( &argc, argv );
	glutInitDisplayMode		( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH ); //Set up a basic display buffer
	glutInitWindowSize		( SCREEN_WIDTH, SCREEN_HEIGHT ); 
	glutInitWindowPosition	( 100, 0 );
	glutCreateWindow		( "osu!baka" );
	
	glutDisplayFunc			( display );
	glutReshapeFunc			( reshape );
	//glutIdleFunc			(  );
	
	glutKeyboardFunc		( keyPressed );
	glutKeyboardUpFunc		( keyUp );
	glutSetKeyRepeat 	    ( GLUT_KEY_REPEAT_OFF );
	glutSpecialFunc			( keySpecial );
	glutSpecialUpFunc		( keySpecialUp );
/*	
	glutMouseFunc			( mousePressed );
	glutMotionFunc			( cursorActiveMotion );
	glutPassiveMotionFunc  	( cursorPassiveMotion );
	glutSetCursor 			( GLUT_CURSOR_NONE );
*/	
	glEnable 		( GL_BLEND );
	glBlendFunc 	( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable 	  	( GL_TEXTURE_2D );
	glTranslatef	( -2.56, -1.92, -4.6 );
	
	/*----------------------------DevIL-------------------------------*/
	if ( ilGetInteger( IL_VERSION_NUM ) < IL_VERSION ) {
		printf( "Incorrect devil library version\n" );
		return 1;
	}
	if ( ilutGetInteger( ILUT_VERSION_NUM ) < ILUT_VERSION ) {
		printf ( "Incorrect ilut library version\n");
		return 1;
	}	
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer ( ILUT_OPENGL );
	
	skin = new Skin();
								
	loadGraphicElements(); // loadSkin.cxx
	/*---------------END_IMAGES----------------*/
	
	hitPicture = new Picture;
	hitPicture->readHitObjects( "/home/kaktus/develop/osu/songs/airman/Hanatan - Airman ga Taosenai (SOUND HOLIC Ver.) (Natsu) [Insane].osu" );
	hitPicture->createSliders();
	
	gettimeofday ( &start, NULL );
	mSec = 0;
	
	glutMainLoop();
	return 0;
}
