#include <stdlib.h>
#include <ctime>
#include "CellTowerGame.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// global info

#define WINDOW_SCREEN_WIDTH 854
#define WINDOW_SCREEN_HEIGHT 480
#define WINDOW_WIDTH 854
#define WINDOW_HEIGHT 480

// global sprite info
#define FRAMES_PER_SECOND 15
#define FRAME_DELAY_SPRITE 1000/FRAMES_PER_SECOND

GridGame *theGame;	// the game object

// ########################################################################################################################
// this is the openGL callback display global function - delegates drawing to the game
// ########################################################################################################################

void DisplayCallbackFunction(void)
{
	theGame->draw();
}

// ########################################################################################################################
// this is the mouse and keyboard callback global functions - delegates key events to the game
// ########################################################################################################################

void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	std::cout << "Keycode:"<<(int)key<<std::endl;
	theGame->keyboardDown(key,x,y);

}

void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	theGame->keyboardUp(key,x,y);
}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	theGame->mouseClicked(button,state,x,y);
	glutPostRedisplay();
}

void MouseMotionCallbackFunction(int x, int y)
{
	theGame->mouseMoved(x,y);
	glutPostRedisplay();
}

// ########################################################################################################################
// this is called many times per second (this enables you to animate things, no drawing, just changing the state)
// then it calls for a redisplay and to be called back again in FRAME_DELAY_SPRITE milliseconds
// ########################################################################################################################

void TimerCallbackFunction(int value)
{
	theGame->update();
	theGame->checkBumps();

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY_SPRITE,TimerCallbackFunction,0);
}

// ########################################################################################################################
// this is called whenever the window is resized - and sets up the projection matrix properly, currently set up for an orthographic view (2D only)
// ########################################################################################################################

void WindowReshapeCallbackFunction(int w,int h)
{
	float asp = (float)w/(float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WINDOW_SCREEN_WIDTH,0,WINDOW_SCREEN_HEIGHT);
	
	theGame->setNewWindowSize(w,h);
	theGame->setScreenSize(WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);
	theGame->updateScreenRatio();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// ########################################################################################################################
// initialize the DevIL library properly
// ########################################################################################################################

void initImageLibrary()
{
	glEnable(GL_TEXTURE_2D);
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

int main(int argc, char **argv)
{
	srand(time(0));

	// initialize the window and OpenGL
	glutInit(&argc,argv);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutCreateWindow("Cell Tower Simulator");

	// register callback functions
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutTimerFunc(1,TimerCallbackFunction,0);
	
	// initialize the image library engine
	initImageLibrary();

	// init the game
	theGame = new CellTowerGame();
	theGame -> setNewWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	theGame -> initializeGame();

	// start the event handler
	glutMainLoop();
	return 0;
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
