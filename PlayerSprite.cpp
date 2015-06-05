#include <stdlib.h>
#include "GridGame.h"
#include "PlayerSprite.h"

extern GridGame *theGame;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

PlayerSprite::PlayerSprite( string spriteSheetFilename ) : GridSprite(spriteSheetFilename)
{
	_gridDX = 0;
	_gridDY = 0; 
	_typeID = PLAYER_GRID_SPRITE;
}

void PlayerSprite::update()
{
	if (!_isMoving) 
	{
		// figure next DX DY
		// prefered random direction
		int dir = -1;
		if (theGame->input.D)
			dir = 0;
		if (theGame->input.A)
			dir = 1;
		if (theGame->input.S)
			dir = 2;
		if (theGame->input.W)
			dir = 3;

		_gridDX = 0;
		_gridDY = 0;
		if (dir == 0 && _gridX+1<theGame->BoardWidth() && theGame->Board()[_gridY][_gridX+1]=='#')
		{
			_gridDX = 1;
			_gridDY = 0;
		}
		else if (dir == 1 && 0 <= _gridX-1 && theGame->Board()[_gridY][_gridX-1]=='#')
		{
			_gridDX = -1;
			_gridDY = 0;
		}
		else if (dir == 2 && _gridY+1<theGame->BoardHeight() && theGame->Board()[_gridY+1][_gridX]=='#')
		{
			_gridDX = 0;
			_gridDY = 1;
		}
		else if (dir == 3 && 0 <= _gridY-1 && theGame->Board()[_gridY-1][_gridX]=='#')
		{
			_gridDX = 0;
			_gridDY = -1;
		}
		//if(_gridDX != 0 || _gridDY != 0) 
		//{
		//	StartMoving();
		//}
		StartMoving();
	}

	//set sprite to face appropriate direction
	if (_gridDX == 1)
		setOrientation(-90);
	else if (_gridDX == -1)
		setOrientation(90);
	else if (_gridDY == 1)
		setOrientation(180);
	else if (_gridDY == -1)
		setOrientation(0);

	setCenter(sz.width/2,sz.height/2);

	GridSprite::update();
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

