#include <stdio.h>
#include "map.h"
#include "state.h"
#include "define.h"
#include "util.h"
#include "stats.h"
#include "screens.h"

int gameLoop();
int destroy();
int init();
int init(int argc, char *argv[]);


int main(int argc, char *argv[])
{
	init(argc,argv);

	while(getState()!=STATE_EXITING)
	{
		gameLoop();
	}

	destroy();
	return 0;
}

int init(int argc, char *argv[])
{
	initWindows();
	initMap();
	generateMap();
	setState(STATE_MENU);
	return 0;
}

int destroy()
{
	destroyWindows();
	return 0;
}

int gameLoop()
{
	switch(getState())
	{
		case STATE_ALIVE:
			showGame();
			break;
		case STATE_DEAD:
			savePoints();
			setPoints(0);
			showDead();
			break;
		case STATE_EXITING:
			break;
		case STATE_HELP:
			showHelp();
			break;
		case STATE_MENU:
			showMenu();
			break;
		case STATE_RESTART:
			setPoints(0);
			generateMap();
			setPlayerPosition(DPLAYERX,DPLAYERY);
			setState(STATE_ALIVE);
			break;
		case STATE_ERROR:
			printf("Program ecountered an error. Exiting..");
			setState(STATE_EXITING);
			break;
		case STATE_PAUSE:
			showPause();
			break;
		default:
			printf("Program ecountered an error in main loop. Exiting..");
			setState(STATE_EXITING);
			break;
	}
	return 0;
}

void cleaner()
{
	//destroyWindow();
}

