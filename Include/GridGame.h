#ifndef _GRIDGAME_H_
#define _GRIDGAME_H_

#include <vector>
#include "Game.h"
#include "GridSprite.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#define GRID_XMARGIN 5.f
#define GRID_YMARGIN 5.f
#define GRID_OVERLAP 2.f

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

class GridGame : public Game
{
public:

	// FUNCTIONS = METHODS
	virtual void initializeGame();
	virtual void checkBumps() {};

	// DATA = ATTRIBUTES
	float GridDX() const;
	void GridDX(float val);

	float GridDY() const;
	void GridDY(float val);
	
	int BoardWidth() const;
	void BoardWidth(int val);
	
	int BoardHeight() const;
	void BoardHeight(int val);
	
	char** Board() const;
	void Board(char** val);

protected:

	// FUNCTIONS = METHODS
	virtual void drawForeground();
	virtual void drawHUD();
	void addSpriteToBumpList(GridSprite *s);

	// DATA = ATTRIBUTES
	vector<GridSprite*> _spriteListToBump;	// sprite list to detect collisions

	float gridDX;
	float gridDY;
	int boardWidth;
	int boardHeight;
	char** board;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#endif
