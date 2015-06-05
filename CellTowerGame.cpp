#include "CellTowerGame.h"
#include "Primitives.h"
#include "ActorSprite.h"
#include "CellTowerSprite.h"

#define MAX_CARS 40
// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

CellTowerGame::CellTowerGame()
{
	// the board layout
	boardHeight = 20;
	board = new char*[boardHeight];
	board[0] = "########################################";
	board[1] = "   #     #        #           #        #";
	board[2] = "   #  #  #  ############################";
	board[3] = "############# # # #  # #  # # # # #    #";
	board[4] = "    #    #  ##### ######  # # # # #    #";
	board[5] = "    #    #        #    #  #########    #";
	board[6] = "    #    ################     #  #     #";
	board[7] = "    #             #    #####  #####    #";
	board[8] = "    ###############        #  #   #    #";
	board[9] = "    #             #        #  #######  #";
	board[10] = "    #             #        #  #     #  #";
	board[11] = "    #             #        #############";
	board[12] = "    #             #        #           #";
	board[13] = "###################        #        ####";
	board[14] = "# # #          #           #       ##  #";
	board[15] = "# # ############           #      ##   #";
	board[16] = "# # #    #     ####################    #";
	board[17] = "#####    #        #        #           #";
	board[18] = "    #    #        #        #############";
	board[19] = "    ########################            ";

	actors[0] = "########################################";
	actors[1] = "   #     #        #           #        #";
	actors[2] = "   #  #  #  ############################";
	actors[3] = "############# # # #  # #  # # # # #    #";
	actors[4] = "    #    #  ##### ######  # # # # #    #";
	actors[5] = "    #    #        #    #  #########    #";
	actors[6] = "    #    ################     #  #     #";
	actors[7] = "   T#             #    #####  #####    #";
	actors[8] = "    ###############        #  #   #    #";
	actors[9] = "    #             #        #  #######  #";
	actors[10] = "    #             #        #  #     #  #";
	actors[11] = "    #             #        #############";
	actors[12] = "    #             #        #           #";
	actors[13] = "###################        #        ####";
	actors[14] = "# # #          #           #      T##  #";
	actors[15] = "# # ############           #      ##   #";
	actors[16] = "# # #    #     ####################    #";
	actors[17] = "#####    #        #        #           #";
	actors[18] = "    #    #        #        #############";
	actors[19] = "    ########################            ";

	boardWidth = strlen(board[0]);

	_avgQoSTimer = new Timer("QOS");

	_lastUpdateTime = _avgQoSTimer->getCurrentTime();
	_curAvgQoS = 0;
}

CellTowerGame::~CellTowerGame()
{
	deleteSpriteDrawList();
	delete board;
}

// ========================================================================================================================

void CellTowerGame::initializeGame()
{
	int pX = 0;
	int pY = 0;

	//randomly spawn sprites at available positions
	for (int i = 0; i < MAX_CARS; i++)
	{
		do
		{
			pX = rand () % boardWidth;
			pY = rand () % boardHeight;
		}
		while (actors[pY][pX] != '#');

		actors[pY][pX] = 'X';
	}

	// the background
	/*
	background = new GameBack("images/map2.gif",stateInfo.windowWidth,stateInfo.windowHeight);
	background->setLayerID(0);
	addSpriteToUpdateList(background);
	addSpriteToDrawList(background);
	*/

	ActorSprite* xs;
	CellTowerSprite* ts;

	// create actors
	for(int i = 0; i < boardHeight; i++)
	{
		for(int j = 0, c = actors[i][j]; j < boardWidth ; j++)
		{
			c = actors[i][j];
			switch(c)
			{
			case 'P': //http://opengameart.org/content/car-racer
				player = new PlayerSprite("images/cars.png");
				player->FramesToMove(5);
				player->setGridPosition(j,i); 
				player->setNumberOfAnimations(4);
				player->setSpriteFrameSize(14,30);
				player->addSpriteAnimFrame(0,0,0);
				player->addSpriteAnimFrame(1,27,0);
				player->addSpriteAnimFrame(2,53,0);
				player->addSpriteAnimFrame(3,80,0);
				player->setCurrentAnimation(2);
				player->setLayerID(2);
				addSpriteToDrawList(player);
				addSpriteToUpdateList(player);
				addSpriteToBumpList(player);
				break;
			//case 'P':
			//	player = new PlayerSprite("images/dkong.png");
			//	player->_framesToMove = 5;
			//	player->setGridPosition(j,i); 
			//	player->setNumberOfAnimations(1);
			//	player->setSpriteFrameSize(55, 60);
			//	//player->addSpriteAnimRow(0, 50, 2, 60, 0, 7);
			//	player->addSpriteAnimFrame(0, 0, 0);
			//	player->addSpriteAnimFrame(0, 0, 0);
			//	player->addSpriteAnimFrame(0, 0, 0);
			//	player->addSpriteAnimFrame(0, 60-1, 0);
			//	player->addSpriteAnimFrame(0, 120-2, 0);
			//	player->addSpriteAnimFrame(0, 180-3, 0);
			//	player->addSpriteAnimFrame(0, 240-4, 0);
			//	player->addSpriteAnimFrame(0, 350-5, 0);
			//	player->addSpriteAnimFrame(0, 350-5, 0);
			//	player->addSpriteAnimFrame(0, 350-5, 0);
			//	player->addSpriteAnimFrame(0, 240-4, 0);
			//	player->addSpriteAnimFrame(0, 180-3, 0);
			//	player->addSpriteAnimFrame(0, 120-2, 0);
			//	player->addSpriteAnimFrame(0, 60-1, 0);
			//	player->setLayerID(2);
			//	addSpriteToDrawList(player);
			//	addSpriteToUpdateList(player);
			//	addSpriteToBumpList(player);
			//	break;
			case 'X': //http://opengameart.org/content/car-racer
				xs = new ActorSprite("images/cars.png");
				xs->FramesToMove(10);
				xs->setGridPosition(j,i); 
				xs->setNumberOfAnimations(4);
				xs->setSpriteFrameSize(14,30);
				xs->addSpriteAnimFrame(0,0,0);
				xs->addSpriteAnimFrame(1,27,0);
				xs->addSpriteAnimFrame(2,53,0);
				xs->addSpriteAnimFrame(3,80,0);
				xs->setLayerID(1);
				//xs->setCurrentAnimation(0);
				xs->setCurrentAnimation(rand() % 4);
				addSpriteToDrawList(xs);
				addSpriteToUpdateList(xs);
				addSpriteToBumpList(xs);

				
				break;
			case 'T': //http://opengameart.org/content/sensorradar-tower
				ts = new CellTowerSprite("images/cellTower.png");
				ts->FramesToMove(10);
				ts->setGridPosition(j,i); 
				ts->setNumberOfAnimations(1);
				ts->setSpriteFrameSize(25,34);
				ts->addSpriteAnimFrame(0,0,0);
				ts->setLayerID(1);

				addSpriteToDrawList(ts);
				addSpriteToUpdateList(ts);
				addSpriteToBumpList(ts);
				break;
			}

		}
	}

	GridGame::initializeGame();
}
void CellTowerGame::drawHUD()
{
	GridGame::drawHUD();

	//draw time
	setColor(0.706, 0.49, 0.094);
	drawRectangle(true, 0, stateInfo.screenHeight-5*GRID_XMARGIN, 95, 20, 0);

	setColor(0.863, 0.643, 0.216);
	drawRectangle(false, 0, stateInfo.screenHeight-5*GRID_XMARGIN, 95, 20, 0);

	setColor(1, 0.933, 0.659);
	char str[20];

	int curTime = _updateTimer->getCurrentTime() / 1000;
	sprintf_s(str, "%02d:%02d", curTime / 60, curTime % 60);
	drawTextLarge(str, 25, stateInfo.screenHeight-4*GRID_XMARGIN);

	//draw avg QOS
	setColor(0, 0, 0);
	drawRectangle(true, stateInfo.screenWidth-GRID_XMARGIN-115, 4, 115, 24, 0);

	setColor(0.863, 0.643, 0.216);
	drawRectangle(false,stateInfo.screenWidth-GRID_XMARGIN-115, 4, 115, 24, 0);

	setColor(1, 1, 1);
	sprintf_s(str, "AVG QOS: %3d%%", _curAvgQoS);
	drawText(str, stateInfo.screenWidth-GRID_XMARGIN-115+10, 12);
}

void CellTowerGame::checkBumps()
{
	std::vector<GridSprite*>::iterator it; 
	std::vector<GridSprite*>::iterator it2; 

	float distX;
	float distY;
	float dist;

	int spriteCount = 0;
	int totalQoS = 0;

	for(it=_spriteListToBump.begin(); it != _spriteListToBump.end();it++)
	{
		GridSprite *s1 = (*it);

		for(it2=_spriteListToBump.begin(); it2 != _spriteListToBump.end();it2++)
		{
			GridSprite *s2 = (*it2);

			if (s1 != s2)
			{
				if (s1->TypeID() == CELLTOWER_GRID_SPRITE && s2->TypeID() != CELLTOWER_GRID_SPRITE)
				{
					//check circle collision between cell tower and other sprites
					distX = s1->GridX() - s2->GridX();
					distY = s1->GridY() - s2->GridY();
					dist = sqrt((distX*distX) + (distY*distY));
					if (dist <= (s1->Range() + s2->Range()))
					{
						s2->Qos(100);
					}
				}
			}
		}

		if (s1->TypeID() != CELLTOWER_GRID_SPRITE)
		{
			spriteCount++;
		}
	}

	//tally up total QOS and dim sprites not in range of cell tower 
	for(it=_spriteListToBump.begin(); it != _spriteListToBump.end();it++)
	{
		if ((*it)->Qos() || (*it)->TypeID() == CELLTOWER_GRID_SPRITE)
		{
			totalQoS += (*it)->Qos();
			(*it)->setLightingRGB(1, 1, 1);
		}
		else
		{
			(*it)->setLightingRGB (0.65, 0.65, 0.65);
		}
	}

	//current avg qos
	stateInfo.score = totalQoS/spriteCount;

	_avgQoSTimer->tick();

	//update qos in 1 sec intervals and calculate running avg qos 
	if ((_avgQoSTimer->getCurrentTime() - _lastUpdateTime)/1000.f > 1)
	{
		_lastUpdateTime = _avgQoSTimer->getCurrentTime();
		
		_avgQoS.push_back(stateInfo.score);

		totalQoS = 0;
		spriteCount = _avgQoS.size();

		for (int i = 0; i < spriteCount; i++)
		{
			totalQoS +=_avgQoS[i];
		}

		_curAvgQoS = totalQoS/spriteCount;
	}
	
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
