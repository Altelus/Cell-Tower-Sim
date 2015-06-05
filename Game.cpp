#include "Game.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

Game::Game()
{
	//background
	stateInfo.bgClearColor.red = 0.031;
	stateInfo.bgClearColor.green =  0.031;
	stateInfo.bgClearColor.blue =  0.031;

	// init state
	stateInfo.gameState = GameStateInfo::STATE_GAMEPLAY;
	_renderingTimer = new Timer("RENDER");
	_updateTimer = new Timer("UPDATE");
	input.W = false;
	input.A = false;
	input.S = false;
	input.D = false;
}

// ########################################################################################################################
// utility functions
// ########################################################################################################################

void Game::setScreenSize(int w, int h) 
{ 
	stateInfo.screenWidth = w; 
	stateInfo.screenHeight = h; 
}

void Game::setNewWindowSize(int width,int height) 
{ 
	stateInfo.windowWidth = width; 
	stateInfo.windowHeight = height; 
}

// used for the mouse function to get actual screen pixel coordinates from the window coordinates
void Game::updateScreenRatio() 
{
	stateInfo.ratioWidth = stateInfo.screenWidth/(float)stateInfo.windowWidth;
	stateInfo.ratioHeight = stateInfo.screenHeight/(float)stateInfo.windowHeight;
}

// ########################################################################################################################
// this gets called automatically about 30 times per second
// ########################################################################################################################

void Game::draw()
{
	PreDraw();
	DrawGame();
	PostDraw();
}

// ************************************************************************************************************************
// set up things that need to happen in order to draw the game, i.e. sorting, splitting things into appropriate lists etc
// ************************************************************************************************************************

void Game::PreDraw()
{
	glViewport(0,0,stateInfo.windowWidth,stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red, stateInfo.bgClearColor.green, stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
	glLoadIdentity(); // clear out the transformation matrix
	glEnable(GL_TEXTURE_2D); // turn on texturing
	_renderingTimer->tick(); // if we update our timer it will tell us the elapsed time since the previous frame that we rendered
	std::sort(_spriteListToDraw.begin(), _spriteListToDraw.end(), [] (Sprite* s1, Sprite* s2) { return (s1->LayerID() < s2->LayerID()); }); // sort the sprites by layerID
}

// ************************************************************************************************************************
// the actual drawing of the current frame of the game
// ************************************************************************************************************************

void Game::DrawGame()
{
	glDisable(GL_TEXTURE_2D);
	drawForeground();
	glEnable(GL_TEXTURE_2D);

	drawSprites();

	glDisable(GL_TEXTURE_2D);
	drawHUD();
	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers(); // this makes it actually show up on the screen
}

// ************************************************************************************************************************
// clean up and set up things for the next frame, usually just memory management or setting up game state boolean values etc.  
// ************************************************************************************************************************

void Game::PostDraw()
{
}

// ************************************************************************************************************************
// push the sprite to the end of the list
// ************************************************************************************************************************

void Game::addSpriteToDrawList(Sprite *s)
{
	// push the sprite to the back of the list
	if(s)
		_spriteListToDraw.push_back(s);
}

// ========================================================================================================================

void Game::addSpriteToUpdateList(Sprite *s)
{
	// push the sprite to the back of the list
	if(s)
	{
		_spriteListToUpdate.push_back(s);
	}
}

// ========================================================================================================================

void Game::deleteSpriteDrawList()
{
	std::vector<Sprite*>::iterator it; 
	for(it=_spriteListToDraw.begin(); it != _spriteListToDraw.end();it++)
	{
		Sprite *s = (*it);
		delete s;
	}
}

// ************************************************************************************************************************
// this function is what actually draws the sprites onto the screen at their appropriate location
// ************************************************************************************************************************

void Game::drawSprites()
{
	std::vector<Sprite*>::iterator it; 
	for(it=_spriteListToDraw.begin(); it != _spriteListToDraw.end();it++)
	{
		Sprite *s = (*it);
		s->draw();
	}
}

// ========================================================================================================================

void Game::updateSprites()
{
	std::vector<Sprite*>::iterator it;

	for(it=_spriteListToUpdate.begin(); it != _spriteListToUpdate.end();it++)
	{
		Sprite *s = (*it);
		s->update();
	}
}

// ########################################################################################################################
// (iteration of) the game loop, if you need to update physics calculations, sprite animation info, or sound etc, it goes in here
// ########################################################################################################################

void Game::update()
{
	_updateTimer->tick(); // update our clock so we have the delta time since the last update
	updateSprites(); // call update on each sprite in list
}

// ************************************************************************************************************************
// this gets called when you press a key down - you are given the key that was pressed and where the (x,y) location of the mouse is when pressed
// ************************************************************************************************************************

void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q':
		exit(1);
		break;
	case 'w':
		input.W = true;
		break;
	case 'a':
		input.A = true;
		break;
	case 's':
		input.S = true;
		break;
	case 'd':
		input.D = true;
		break;
	}
}

// ************************************************************************************************************************
// this gets called when you lift a key up - you are given the key that was pressed and where the (x,y) location of the mouse is when pressed
// ************************************************************************************************************************

void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	case 'w':
		input.W = false;
		break;
	case 'a':
		input.A = false;
		break;
	case 's':
		input.S = false;
		break;
	case 'd':
		input.D = false;
		break;
	}
}

// ************************************************************************************************************************
// this function is called when the mouse is clicked and it handles the input state management
// ************************************************************************************************************************

void Game::mouseClicked(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		input.mouseDown = true;
		input.clickX = x*stateInfo.ratioWidth;
		input.clickY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
		input.button = button;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
	}
	else
	{
		input.mouseDown = false;
	}
}

// ************************************************************************************************************************
// this occurs only when the mouse is pressed down and the mouse has moved.  you are given the x,y locations 
// in window coordinates (from the top left corner) and thus must be converted to screen coordinates using the screen to window pixels ratio
// and the y must be flipped to make the bottom left corner the origin
// ************************************************************************************************************************

void Game::mouseMoved(int x, int y)
{
	/* convert from window to screen pixel coordinates */
	input.currentX = x*stateInfo.ratioWidth;
	input.currentY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;

	if(input.mouseDown)
	{
		if(input.button == GLUT_LEFT_BUTTON)
		{
		}
	}
}

float Game::getCurrentTime()
{
	return _updateTimer->getCurrentTime();
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
