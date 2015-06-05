#include <stdlib.h>
#include "GridGame.h"
#include "CellTowerSprite.h"
#include "Primitives.h"

extern GridGame *theGame;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

CellTowerSprite::CellTowerSprite( string spriteSheetFilename ) : GridSprite(spriteSheetFilename)
{
	_typeID = CELLTOWER_GRID_SPRITE;
	_range = 15;
	_signalPhase = 0;
	_lastUpdateTime = theGame->getCurrentTime();
}

void CellTowerSprite::draw()
{
	GridSprite::draw();

	//update phase of signal wave
	if ((theGame->getCurrentTime() - _lastUpdateTime)/1000.f > .05)
	{
		_lastUpdateTime = theGame->getCurrentTime();

		_signalPhase++;
		if (_signalPhase > _range)
		{
			_signalPhase = 0;
		}
	}
	//fade from white to black as signal reaches the end of range
	float fadeColor = (_signalPhase*12)/255.f;

	//circle line width diminishes as signal reaches the end if range
	int lineWidth;
	if (_signalPhase < _range*(1.0/3.0))
	{
		lineWidth = 3;
	}
	else if (_signalPhase < _range*(2.0/3.0))
	{
		lineWidth = 2;
	}
	else
	{
		lineWidth = 1;
	}

	glDisable(GL_TEXTURE_2D);
	//setColor(0.969, 0.969, 0.961);
	setColor(1-fadeColor,1-fadeColor, 1-fadeColor);

	drawCircle(50,(_signalPhase)*theGame->GridDX() - GRID_XMARGIN -GRID_OVERLAP, positionX + sz.height/2-GRID_XMARGIN, positionY + sz.height/2-GRID_YMARGIN, lineWidth);
	//drawCircle(50,(_signalPhase)*theGame->GridDX() - GRID_XMARGIN -GRID_OVERLAP, positionX, positionY);

	glEnable(GL_TEXTURE_2D);
}

void CellTowerSprite::update()
{
	StartMoving();

	GridSprite::update();

	positionX -= sz.width/2-2*GRID_XMARGIN;
	positionY -= sz.height/2-4*GRID_YMARGIN;
}


// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

