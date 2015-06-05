#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "GL/glut.h"
#include "IL/ilut.h"
using namespace std;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

class XY_Coordinate
{
public:			// this class is for holding data only so it is ok to make it all public

	// FUNCTIONS = METHODS
	XY_Coordinate(float _x, float _y, float _u, float _v);

	// DATA = ATTRIBUTES
	float x;
	float y;
	float u;
	float v;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

class SpriteAnimation 
{
public:

	SpriteAnimation(void)
	{
		currentFrame = 0;
		doesLoop = true;
	}

	void nextFrame()
	{
		int numFrames = coords.size();
		currentFrame++;
		if(currentFrame >= numFrames)
		{
			if(doesLoop) currentFrame = 0;
			else currentFrame = numFrames - 1;
		}
	}

	void setLooping(bool loop) {doesLoop = loop;}

	vector<XY_Coordinate*> coords; // each animation has a list of x,y coordinates that can be cycled through
	bool doesLoop;
	int currentFrame;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

typedef struct _SpriteSheetInfo
{
	unsigned int textureID;
	float width,height;
}SpriteSheetInfo;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

typedef struct _SpriteSize
{
	float width, height;
	float normalizedWidth,normalizedHeight;
}SpriteSize;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// this class takes care of everything related to sprites - loading/drawing/setting states etc.

class Sprite
{
public:

	// FUNCTIONS = METHODS

	Sprite(string spriteSheetFilename);

	virtual void draw();
	virtual void update();
	virtual Sprite& operator= (const Sprite&);

	void loadSpriteSheet(const char *filename);
	void setSpriteFrameSize(int width, int height);
	void setNumberOfAnimations(int num);
	void addSpriteAnimFrame(int animationNumber, int x, int y);
	void addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames);
	void setCurrentAnimation(int anim);
	void setLayerID(float value);
	void setCenter(float x, float y);
	void setPosition(float x, float y);
	void setOrientation(float _theta);
	float getOrientation();
	void nextFrame();
	void setLightingRGB(float r, float g, float b);

	int LayerID() const;
	void LayerID(int val);
protected:
	// DATA = ATTRIBUTES

	SpriteSize sz;
	SpriteSheetInfo sheet;
	unsigned int numberOfAnimations;
	unsigned int currentAnimation;

	float _r;
	float _g;
	float _b;

	float positionX;
	float positionY;
	float centerX;
	float centerY;
	float theta;							// orientation
	int layerID;							// which layer this sprite is on, lower is further away, background is 0, foreground > 0

	vector<SpriteAnimation*> animations;	// list of animations
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#endif
