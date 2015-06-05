#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <vector>
#include "Timer.h"
#include "Sprite.h"
#include "GameBack.h"
using namespace std;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// input information related to mouse and keyboard ex. you need to know if a key is currently pressed down

class InputInfo				// this was a struct but making it class opens it for future improvements
{
public:						// this class is for holding data only so it is ok to make it all public

	bool mouseDown;			// is the mouse down?
	bool W;
	bool A;
	bool S;
	bool D;
	int button;				// which mouse button
	float clickX,clickY;	// where the mouse was clicked
	float currentX;
	float currentY;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// convenience structure to hold rgb values

class RGBColor				// this was a struct but making it class opens it for future improvements
{
public:						// this class is for holding data only so it is ok to make it all public

	float red;
	float green;
	float blue;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// this stores anything related to the state of the game i.e. what level are we on?, what is the score? etc.

class GameStateInfo 
{
public:						// this class is for holding data only so it is ok to make it all public

	// names of game states that the game can be in at any moment.  These help you manage the flow of the game.  
	// Especially if you want to do different updates or have different behaviour for input 
	// i.e. mouse and keyboard functions might have different behaviour in-game (STATE_GAMEPLAY) versus when in the Menu (STATE_MAINMENU)
	enum { STATE_GAMEPLAY, STATE_MAINMENU, STATE_CREDITS }  gameState;

	GameStateInfo() : score(0) {};

	int score;
	RGBColor bgClearColor;	// the default clear color of the background
	int windowWidth;		// window width
	int windowHeight;		// window height
	int screenWidth;		// screen width - you can have a 640x480 game screen stretched to 1280x1024
	int screenHeight;		// screen height - you can have a 640x480 game screen stretched to 1280x1024
	float ratioWidth;
	float ratioHeight;
};

// ########################################################################################################################
// the main Game class of the base sprite lib starter code - it handles input, game loop update, display
// ########################################################################################################################

class Game 
{
public:

	// FUNCTIONS = METHODS
	Game(void);
	void setScreenSize(int w, int h);
	void setNewWindowSize(int width,int height);
	void draw();													// draw/rendering routines, called from the main
	void update();													// update routines, called from game loop frequently
	void keyboardDown(unsigned char key, int mouseX, int mouseY);	// input callback functions
	void keyboardUp(unsigned char key, int mouseX, int mouseY);		// input callback functions
	void mouseClicked(int button, int state, int x, int y);			// input callback functions
	void mouseMoved(int x, int y);									// input callback functions
	void updateScreenRatio();										// used for the mouse function to get actual screen pixel coordinates from the window coordinates
	float getCurrentTime();
	virtual void initializeGame() {};								// this function is called to initialize everything related to the game, i..e loading sprites etc.

	// DATA = ATTRIBUTES
	InputInfo input;

protected:

	// FUNCTIONS = METHODS
	virtual void drawForeground() {}
	virtual void drawHUD() {}				// draw statics
	void addSpriteToDrawList(Sprite *s);	// add a sprite to the draw list
	void addSpriteToUpdateList(Sprite *s);	// add a sprite to the update list
	void addSpriteToBumpList(Sprite *s);	// add a sprite to the collision list
	void deleteSpriteDrawList();			// freee up all space used by sprites (this listh should have them all)
	void PreDraw();							// prior to drawing
	void DrawGame();						// actual drawing the frame
	void PostDraw();						// cleanup and prepare for next frame
	void drawSprites();						// draw the sprite list
	void updateSprites();					// update the sprite list

	// DATA = ATTRIBUTES
	GameBack *background;					// the background scroller
	GameStateInfo stateInfo;				// game state info



protected:

	// DATA = ATTRIBUTES
	Timer* _renderingTimer;					// timer for rendering and animation
	Timer* _updateTimer;					// timer for physics/collisions etc.
	vector<Sprite*> _spriteListToDraw;		// sprite list to draw
	vector<Sprite*> _spriteListToUpdate;	// sprite list to detect collisions
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#endif
