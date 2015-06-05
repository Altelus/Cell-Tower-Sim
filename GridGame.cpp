#include "GridGame.h"
#include "Primitives.h"
#include <math.h>

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

void GridGame::initializeGame()
{
	// the background
	//bg = new GameBack("images/map2.gif",stateInfo.windowWidth,stateInfo.windowHeight);
	//bg->setLayerID(0);
	//addSpriteToUpdateList(bg);
	//addSpriteToDrawList(bg);

	Game::initializeGame();
}

float GridGame::GridDX() const
{
	return gridDX;
}

void GridGame::GridDX( float val )
{
	gridDX = val;
}

float GridGame::GridDY() const
{
	return gridDY;
}

void GridGame::GridDY( float val )
{
	gridDY = val;
}

int GridGame::BoardWidth() const
{
	return boardWidth;
}

void GridGame::BoardWidth( int val )
{
	boardWidth = val;
}

int GridGame::BoardHeight() const
{
	return boardHeight;
}

void GridGame::BoardHeight( int val )
{
	boardHeight = val;
}

char** GridGame::Board() const
{
	return board;
}

void GridGame::Board( char** val )
{
	board = val;
}

// ========================================================================================================================
void GridGame::drawForeground()
{
	// lookup values shared in the game
	gridDX = (stateInfo.screenWidth-2*GRID_XMARGIN)/(float)boardWidth;
	gridDY = (stateInfo.screenHeight-2*GRID_YMARGIN)/(float)boardHeight;

	// draw board
	setColor(0.549, 0.439,0.243);
	for(int i = 0; i < boardHeight; i++)
	{
		for(int j = 0, c = board[i][j]; c != 0; j++, c = board[i][j])
		{
			switch(c)
			{
			case '#':
				drawRectangle(true, 
					j*gridDX+GRID_XMARGIN -1, 
					(boardHeight-1-i)*gridDY+GRID_YMARGIN-GRID_OVERLAP, 
					gridDX+1, gridDY+1, 0);

				break;
			}
		}
	}

}

void GridGame::drawHUD()
{
	// draw QOS
	setColor(0, 0, 0);
	drawRectangle(true, stateInfo.screenWidth-GRID_XMARGIN-210, 4, 85, 24, 0);

	setColor(0.863, 0.643, 0.216);
	drawRectangle(false,stateInfo.screenWidth-GRID_XMARGIN-210, 4, 85, 24, 0);
	
	setColor(1, 1, 1);
	char str[20];
	sprintf_s(str, "QOS: %3d%%", stateInfo.score);
	drawText(str,stateInfo.screenWidth-GRID_XMARGIN-210+10, 12);

	Game::drawHUD();
}

// ========================================================================================================================

void GridGame::addSpriteToBumpList(GridSprite *s)
{
	// push the sprite to the back of the list
	if(s)
	{
		_spriteListToBump.push_back(s);
	}
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
