#include <stdlib.h>
#include "GridGame.h"
#include "ActorSprite.h"

extern GridGame *theGame;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

ActorSprite::ActorSprite( string spriteSheetFilename ) : GridSprite(spriteSheetFilename)
{
	_typeID = ACTOR_GRID_SPRITE;
}

void ActorSprite::draw()
{
	GridSprite::draw();
}

void ActorSprite::update()
{
	if (!_isMoving) 
	{
#pragma region ranDXY
		// figure next DX DY
		// 4/12 = 33.33% chance to change direction
		int dir = rand() % 12; 
		if (dir < 4) 
		{
			// prefered random direction
			if (dir == 0 && _gridX+1<theGame->BoardWidth() && theGame->Board()[_gridY][_gridX+1]=='#' && _gridDX != -1)
			{//right
				_gridDX = 1;
				_gridDY = 0;
			}
			else if (dir == 1 && 0 <= _gridX-1 && theGame->Board()[_gridY][_gridX-1]=='#' && _gridDX != 1)
			{//left
				_gridDX = -1;
				_gridDY = 0;
			}
			else if (dir == 2 && _gridY+1<theGame->BoardHeight() && theGame->Board()[_gridY+1][_gridX]=='#' && _gridDY != -1)
			{//up
				_gridDX = 0;
				_gridDY = 1;
			}
			else if (dir == 3 && 0 <= _gridY-1 && theGame->Board()[_gridY-1][_gridX]=='#' && _gridDY != 1)
			{//down
				_gridDX = 0;
				_gridDY = -1;
			}
			// just firs avail direction
			else if (_gridX+1 < theGame->BoardWidth() && theGame->Board()[_gridY][_gridX+1]=='#' && _gridDX != -1)
			{
				_gridDX = 1;
				_gridDY = 0;
			}
			else if (0 <= _gridX-1 && theGame->Board()[_gridY][_gridX-1]=='#' && _gridDX != 1)
			{
				_gridDX = -1;
				_gridDY = 0;
			}
			else if (_gridY+1 < theGame->BoardHeight() && theGame->Board()[_gridY+1][_gridX]=='#' && _gridDY != -1)
			{
				_gridDX = 0;
				_gridDY = 1;
			}
			else if (0 <= _gridY-1 && theGame->Board()[_gridY-1][_gridX]=='#' && _gridDY != 1)
			{
				_gridDX = 0;
				_gridDY = -1;
			}
			else
			{
				dir = 4;
			}

		}
#pragma endregion

		if(dir >= 4 &&_gridDX != 0)
		{
			if (0 <= _gridX+_gridDX && _gridX+_gridDX < theGame->BoardWidth() && theGame->Board()[_gridY][_gridX+_gridDX]=='#')
				; // continue
			else
			{ //collision with wall while moving on x axis, randomly change direction to up/down if possible
				int randDY = rand() % 2;
				if (randDY == 0)
				{
					if (_gridY+1<theGame->BoardHeight() && theGame->Board()[_gridY+1][_gridX]=='#')
					{//up
						_gridDX = 0;
						_gridDY = 1;
					}
					else if (0 <= _gridY-1 && theGame->Board()[_gridY-1][_gridX]=='#')
					{//down
						_gridDX = 0;
						_gridDY = -1;
					}
					else
					{
						_gridDX = -_gridDX;
					}
				}
				else if (randDY == 1)
				{
					if (0 <= _gridY-1 && theGame->Board()[_gridY-1][_gridX]=='#')
					{//down
						_gridDX = 0;
						_gridDY = -1;
					}
					else if (_gridY+1<theGame->BoardHeight() && theGame->Board()[_gridY+1][_gridX]=='#')
					{//up
						_gridDX = 0;
						_gridDY = 1;
					}
					else
					{
						_gridDX = -_gridDX;
					}
				}
			}
		}
		// DY - DY preference
		else if(dir >= 4 && _gridDY != 0)
		{
			if (0 <= _gridY+_gridDY && _gridY+_gridDY < theGame->BoardHeight() && theGame->Board()[_gridY+_gridDY][_gridX]=='#')
				; // continue
			else
			{ //collision with wall while moving on y axis, randomly change direction to right/left if possible
				int randDX = rand() % 2;
				if (randDX == 0)
				{
					if  (_gridX+1<theGame->BoardWidth() && theGame->Board()[_gridY][_gridX+1]=='#')
					{//right
						_gridDX = 1;
						_gridDY = 0;
					}
					else if (0 <= _gridX-1 && theGame->Board()[_gridY][_gridX-1]=='#')
					{//left
						_gridDX = -1;
						_gridDY = 0;
					}
					else
					{
						_gridDY = -_gridDY;
					}
				}
				else if (randDX == 1)
				{
					if (0 <= _gridX-1 && theGame->Board()[_gridY][_gridX-1]=='#')
					{//left
						_gridDX = -1;
						_gridDY = 0;
					}
					else if  (_gridX+1<theGame->BoardWidth() && theGame->Board()[_gridY][_gridX+1]=='#')
					{//right
						_gridDX = 1;
						_gridDY = 0;
					}
					else
					{
						_gridDY = -_gridDY;
					}
				}
			}
		}
		StartMoving();
	}

	//set sprite to face appropriate direction
	if (_gridDX == 1)
		setOrientation(-90);
	else if (_gridDX == -1)
		setOrientation(90);
	else if (_gridDY == 1)
		setOrientation(-180);
	else if (_gridDY == -1)
		setOrientation(0);

	setCenter(sz.width/2,sz.height/2);

	GridSprite::update();
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

