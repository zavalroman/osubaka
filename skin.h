/*
 * Skin.h
 * 
 * Copyright 2016 Unknown <roman@kip-n11>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>

class Skin
{
public:
	Skin ()
	{
		//strcpy ( skinName, "GUMI v1.4" );
	}
	~Skin();
	
	struct Image
	{
		size_t index;
		int width;
		int height;
		float posX;
		float posY;
		//float aspectRatio;
	};
	
	Image imgMenuButton;
	Image imgBack;
	Image cursor;
	Image hitCircle;
	Image hitCircleOverlay;
	Image approachCircle;
	Image sliderB0;
	Image sliderFollowCircle;
	Image hit0;
	Image hit50;
	Image hit100;
	Image hit300;
		
private:
	const char * skinName;
};

