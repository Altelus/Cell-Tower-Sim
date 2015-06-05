#include "GameBack.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

GameBack::GameBack(std::string filename, int width, int height) 
	: Sprite(filename) 
{
	_scrollSpeed = 4;
	this->setNumberOfAnimations(1);
	this->addSpriteAnimFrame(0, 0,0);
	this->setSpriteFrameSize(width,height);
	this->setPosition(0,0);
}

// ########################################################################################################################

void GameBack::SetScrollingSpeed(float speed)
{
	_scrollSpeed = speed;
}

// ########################################################################################################################
// method override so the background scrolling sprite must do something different than a traditional sprite 
// you will probably want to have boolean flags like isScrolling, etc and only move if it is scrolling since you might want to control the scrolling behaviour
// ########################################################################################################################

void GameBack::update()
{
	this->animations[0] -> coords[0] -> x += _scrollSpeed; // update our x position by scrollingSpeed pixels

	// check if we've gone too far
	if(this->animations[0]->coords[0]->x >= (float)sheet.width - sz.width)
	{
		this->animations[0]->coords[0]->x = sheet.width-sz.width;
	}
	// u must be normalized for texturing purposes, u,v must be between [0,1] */
	this->animations[0]->coords[0]->u = (float)this->animations[0]->coords[0]->x/(float)sheet.width;
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
