#include <stdlib.h>
#include <time.h>
#include "GridGame.h"
#include "GridSprite.h"

extern GridGame *theGame;
int GridSprite::_gridSpriteCount = 0;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

GridSprite::GridSprite( string spriteSheetFilename ) : Sprite(spriteSheetFilename)
{
	_framesToMove = 10; 
	_framesToWait = 0; 
	_isMoving = true; 
	_framesCount = 0;
	_gridDX = 1; 
	_gridDY = 0; 
	_typeID = 0;
	_range = 0;
	_qos = 0;

	_gridSpriteCount++;
}

GridSprite& GridSprite::operator=(const GridSprite& gs)
{
	Sprite:operator=(gs);

	this->_framesToMove = gs._framesToMove; 
	this->_framesToWait =gs._framesToWait;
	this->_isMoving = gs._isMoving;
	this->_framesCount = gs._framesCount;
	this->_gridX = gs._gridX;
	this->_gridY = gs._gridY;
	this->_gridDX = gs._gridDX; 
	this->_gridDY = gs._gridDY; 
	this->_typeID = gs._typeID;
	this->_range = gs._range;

	return *this;
}

GridSprite::~GridSprite()
{
	_gridSpriteCount--;
}

void GridSprite::setGridPosition( int x, int y )
{
	_gridX = x; _gridY = y;
}

void GridSprite::StartMoving()
{
	_framesCount = 0; _isMoving = true;
}

int GridSprite::FramesCount() const
{
	return _framesCount;
}

void GridSprite::FramesCount( int val )
{
	_framesCount = val;
}

int GridSprite::FramesToMove() const
{
	return _framesToMove;
}

void GridSprite::FramesToMove( int val )
{
	_framesToMove = val;
}

int GridSprite::FramesToWait() const
{
	return _framesToWait;
}

void GridSprite::FramesToWait( int val )
{
	_framesToWait = val;
}

int GridSprite::GridX() const
{
	return _gridX;
}

void GridSprite::GridX( int val )
{
	_gridX = val;
}

int GridSprite::GridY() const
{
	return _gridY;
}

void GridSprite::GridY( int val )
{
	_gridY = val;
}

int GridSprite::GridDX() const
{
	return _gridDX;
}

void GridSprite::GridDX( int val )
{
	_gridDX = val;
}

int GridSprite::GridDY() const
{
	return _gridDY;
}

void GridSprite::GridDY( int val )
{
	_gridDY = val;
}

int GridSprite::TypeID() const
{
	return _typeID;
}

void GridSprite::TypeID( int val )
{
	_typeID = val;
}

int GridSprite::Range() const
{
	return _range;
}

void GridSprite::Range( int val )
{
	_range = val;
}

int GridSprite::Qos() const
{
	return _qos;
}

void GridSprite::Qos( int val )
{
	_qos = val;
}

bool GridSprite::IsMoving() const
{
	return _isMoving;
}

void GridSprite::IsMoving( bool val )
{
	_isMoving = val;
}

void GridSprite::draw()
{
	Sprite::draw();
}

void GridSprite::update()
{
	_framesCount++;
	_qos = 0;

	if (_isMoving) 
	{
		positionX =  _gridX*theGame->GridDX()+GRID_XMARGIN-GRID_OVERLAP + _framesCount*_gridDX*theGame->GridDX()/_framesToMove;
		positionY =  (theGame->BoardHeight()-1-_gridY)*theGame->GridDY()+GRID_YMARGIN-GRID_OVERLAP - _framesCount*_gridDY*theGame->GridDY()/_framesToMove;
					
		if(_framesCount>=_framesToMove) 
		{
			_gridX += _gridDX;
			_gridY += _gridDY;
			_isMoving = false;
			_framesCount = 0;
			//theGame->checkBumps();
		}
	}

	Sprite::update();
}

void GridSprite::GridSpriteCount( int val )
{
	_gridSpriteCount = val;
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

