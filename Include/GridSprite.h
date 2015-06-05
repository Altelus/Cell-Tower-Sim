#ifndef _GRIDSPRITE_H_
#define _GRIDSPRITE_H_

#include "Sprite.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#define PLAYER_GRID_SPRITE 1
#define ACTOR_GRID_SPRITE 2
#define CELLTOWER_GRID_SPRITE 3

class GridSprite : public Sprite
{
public:

	// FUNCTIONS = METHODS
	GridSprite(string spriteSheetFilename);;
	virtual GridSprite& operator= (const GridSprite&);
	virtual ~GridSprite();

	void setGridPosition(int x, int y);
	void StartMoving();

	int FramesCount() const;
	void FramesCount(int val);

	int FramesToMove() const;
	void FramesToMove(int val);

	int FramesToWait() const;
	void FramesToWait(int val);

	int GridX() const;
	void GridX(int val);

	int GridY() const;
	void GridY(int val);

	int GridDX() const;
	void GridDX(int val);

	int GridDY() const;
	void GridDY(int val);

	int TypeID() const;
	void TypeID(int val);

	int Range() const;
	void Range(int val);

	int Qos() const;
	void Qos(int val);

	void GridSpriteCount(int val);

	bool IsMoving() const;
	void IsMoving(bool val);
protected:

	// FUNCTIONS = METHODS
	virtual void draw();
	virtual void update();

	// DATA = ATTRIBUTES
	int _framesToMove;
	int _framesToWait;	
	int _gridX;
	int _gridY;
	int _gridDX;
	int _gridDY;
	int _typeID;
	int _range;
	int _qos;
	bool _isMoving;
	static int _gridSpriteCount;
	
private:
	// DATA = ATTRIBUTES
	int _framesCount;

};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#endif
