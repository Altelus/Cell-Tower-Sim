#include "Sprite.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

Sprite::Sprite(string spriteSheetFilename)
{
	this->loadSpriteSheet(spriteSheetFilename.c_str());
	currentAnimation = 0;
	layerID = 0;
	theta = 0;
	centerX = centerY = 0;

	_r =  _g = _b = 1;
}

Sprite& Sprite::operator=(const Sprite& sprite)
{
	this->sz = sprite.sz;
	this->sheet = sprite.sheet;
	this->numberOfAnimations = sprite.numberOfAnimations;
	this->currentAnimation = sprite.currentAnimation;

	this->_r = sprite._r;
	this->_g = sprite._g;
	this->_b = sprite._b;

	this->positionX = sprite.positionX;
	this->positionY = sprite.positionY;
	this->centerX = sprite.centerX;
	this->centerY = sprite.centerY;
	this->theta = sprite.theta;
	this->layerID = sprite.layerID;

	this->animations = sprite.animations;

	return *this;
}

void Sprite::setCurrentAnimation( int anim )
{
	currentAnimation = anim; if(currentAnimation >= animations.size()) currentAnimation = 0;
}

void Sprite::setLayerID( float value )
{
	layerID = value;
}

void Sprite::setCenter( float x, float y )
{
	centerX = x; centerY = y;
}

void Sprite::setPosition( float x, float y )
{
	positionX = x; positionY = y;
}
void Sprite::setOrientation( float _theta )
{
	theta = _theta;
}
float Sprite::getOrientation()
{
	return theta;
}

void Sprite::nextFrame()
{
	animations[currentAnimation]->nextFrame();
}

int Sprite::LayerID() const
{
	return layerID;
}

void Sprite::LayerID( int val )
{
	layerID = val;
}

XY_Coordinate::XY_Coordinate( float _x, float _y, float _u, float _v )
{
	x=_x; y=_y; u = _u; v=_v;
}

void Sprite::setLightingRGB( float r, float g, float b )
{
	_r = r; _g = g; _b = b;
}

// ########################################################################################################################

void Sprite::loadSpriteSheet(const char *filename)
{
	sheet.textureID = ilutGLLoadImage((char*)filename);
	sheet.width = ilGetInteger(IL_IMAGE_WIDTH);
	sheet.height = ilGetInteger(IL_IMAGE_HEIGHT);
}

// ########################################################################################################################

void Sprite::setSpriteFrameSize(int width, int height)
{
	sz.width = width;
	sz.height = height;
	sz.normalizedWidth = (float)width/(float)sheet.width;
	sz.normalizedHeight = (float)height/(float)sheet.height;
}

// ########################################################################################################################

void Sprite::setNumberOfAnimations(int num)
{
	numberOfAnimations = num;
	animations.reserve(num);
	for(int i=0;i<num;i++)
	{
		SpriteAnimation *anim = new SpriteAnimation();
		animations.push_back(anim);
	}
}

// ########################################################################################################################
// this adds a sprite animation frame to the end of the particular animation list 
// (x,y) specify the pixel values of the bottom left corner of the frame
// animationNumber specifies which animation (i.e. JUMP, RUN, etc) you could use enum's for easier coding 
// ########################################################################################################################

void Sprite::addSpriteAnimFrame(int animationNumber, int x, int y)
{
	float u = (float)x/sheet.width;
	float v = (float)y/sheet.height;

	XY_Coordinate *xy = new XY_Coordinate(x,y, u,v);
	animations[animationNumber]->coords.push_back(xy);
}

// ########################################################################################################################

void Sprite::addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames)
{
	float x,y;
	x = startX;
	y = startY;
	for(int i=0;i<numFrames;i++)
	{
		x += spacingX;
		y += spacingY;
		addSpriteAnimFrame(animationNumber, x,y);
	}
}

// ########################################################################################################################
// this draws the sprite texture at its current frame of its current animation
// it positions the sprite based on the transformation formula: v' = RotationMatrix*(v-center) + position
// where position is the bottom left corner of the sprite and v is each corner of the sprite rectangle, v' is the transformed corner
// and RotationMatrix is defined by the sprite's theta value (counter clockwise)
// ########################################################################################################################

void Sprite::draw()
{
	/* draw the sprite */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();

	/* position the sprite into the particular pixel location */
	glTranslatef(positionX,positionY,0);

	// apply the rotation around the center of the sprite
	glTranslatef(centerX,centerY,0);
	glRotatef(theta, 0,0,1);
	glTranslatef(-centerX,-centerY,0);

	/* get the texture coordinate from the sprite so we know which frame to draw */
	SpriteAnimation *anim = animations[currentAnimation];
	int currentFrame = anim->currentFrame;
	float u = anim->coords[currentFrame]->u;
	float v = anim->coords[currentFrame]->v;

	//glColor3f(1,1,1);
	glColor3f(_r, _g, _b);
	/* bind the appropriate texture frame */
	glBindTexture(GL_TEXTURE_2D,sheet.textureID);
	/* draw the image as a quad the size of the first loaded image */
	glBegin(GL_QUADS);
	glTexCoord2f(u,v);
	glVertex3f(0,0,0);

	glTexCoord2f(u,v+sz.normalizedHeight);
	glVertex3f(0,sz.height,0);

	glTexCoord2f(u+sz.normalizedWidth,v+sz.normalizedHeight);
	glVertex3f(sz.width,sz.height,0);

	glTexCoord2f(u+sz.normalizedWidth,v);
	glVertex3f(sz.width,0,0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

// ########################################################################################################################
// this function could update things like physics and position
// ########################################################################################################################

void Sprite::update()
{
	nextFrame();
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
