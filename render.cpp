/*
*	redner.cpp
*
*/

void paint ( Object *obj )
{
	glBindTexture 	( GL_TEXTURE_2D, obj->image );
	
	glBegin	( GL_QUADS );
	
	glColor4f	 ( obj->R, obj->G, obj->B, obj->A );
	
	glTexCoord2f ( 0, 0 );
	glVertex3f   ( obj->leftBottomX,  obj->leftBottomY,  0 );
	
	glTexCoord2f ( 0, 1 );
	glVertex3f	 ( obj->leftTopX, 	  obj->leftTopY, 	 0 );

	glTexCoord2f ( 1, 1 );
	glVertex3f   ( obj->rightTopX, 	  obj->rightTopY, 	 0 );

	glTexCoord2f ( 1, 0 );
	glVertex3f	 ( obj->rightBottomX, obj->rightBottomY, 0 );
	
	glEnd()
}
