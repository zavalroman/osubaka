/*
 * Skin.cxx
 * 
 * 
 */

//SoundData * hitData;
//Sound * hitSound;

void loadGraphicElements ()
{
	skin -> imgMenuButton.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/menu-button-background.png" );
	skin -> imgMenuButton.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> imgMenuButton.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	//skin -> imgBack.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/Default/menu-back-0.png" );
	//skin -> imgBack.width = ilGetInteger ( IL_IMAGE_WIDTH );
	//skin -> imgBack.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> cursor.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/cursor.png" );
	skin -> cursor.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> cursor.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> hitCircle.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/hitcircle.png" );
	skin -> hitCircle.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> hitCircle.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> hitCircleOverlay.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/hitcircleoverlay.png" );
	skin -> hitCircleOverlay.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> hitCircleOverlay.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> approachCircle.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/approachcircle.png" );
	skin -> approachCircle.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> approachCircle.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> sliderB0.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/sliderb0.png" );
	skin -> sliderB0.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> sliderB0.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> sliderFollowCircle.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/sliderfollowcircle.png" );
	skin -> sliderFollowCircle.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> sliderFollowCircle.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> hit0.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/hit0.png" );
	skin -> hit0.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> hit0.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> hit50.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/hit50.png" );
	skin -> hit50.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> hit50.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> hit100.index = ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/hit100.png" );
	skin -> hit100.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> hit100.height = ilGetInteger ( IL_IMAGE_HEIGHT );
	
	skin -> hit300.index =  ilutGLLoadImage ( "../osupp/Skins/GUMI v1.4/hit300.png" );
	skin -> hit300.width = ilGetInteger ( IL_IMAGE_WIDTH );
	skin -> hit300.height = ilGetInteger ( IL_IMAGE_HEIGHT );
}
