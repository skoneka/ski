#include "screens.h"
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "map.h"
#include "stats.h"
#include "state.h"
#include "util.h"
int inputok=1;
//extern poinscounter;
int showDead()
{
	system("clear");
	printf("ASCIISKI by Artur Skonecki\n\n\n"
			":==:==:==:==:==:YOU ARE DEAD:==:==:==:==:==:\n\n"
			"Your score: %d points\n\n"
			"You can now:\n"
			"Q - exit game\n"
			"C - continue playing\n"
			"R - restart game\n\n"
			, getSavedPoints()
			);
	if(inputok==0) printf("There is no such option. Try again.\n");
	printf(">> ");

	int ch= mygetch();
	switch(ch)
	{
		case 113:
			setState(STATE_EXITING);
			inputok=1;
			break;
		case 'c'://continue playing
			setState(STATE_ALIVE);

			inputok=1;
			break;
		case 114://restartgame
			setState(STATE_RESTART);
			inputok=1;
			break;
		default:
			inputok=0;
			break;
	}
	return 0;
}

int showMenu()
{
		system("clear");
	printf("ASCIISKI by Artur Skonecki\n\n\n"
			":==:==:==:==:==:MAIN MENU:==:==:==:==:==:\n\n"
			"WARNING: game recognizes only lower-case letters\n\n"
			"You can now:\n"
			"S - start game\n"
			"C - continue game\n"
			"H - show help\n"
			"Q - exit game\n\n"
			);
	if(inputok==0) printf("There is no such option. Try again.\n");
	printf(">> ");

	int ch= mygetch();
	switch(ch)
	{
		case 113:
			setState(STATE_EXITING);
			inputok=1;
			break;
		case 'h'://showHelp
			setState(STATE_HELP);
			inputok=1;
			break;
		case 'c':
			setState(STATE_ALIVE);
			break;
		case 115://start game
			setState(STATE_RESTART);
			inputok=1;
			break;
		default:
			inputok=0;
			break;
	}
	return 0;

}

int showHelp()
{
		system("clear");
	printf("ASCIISKI by Artur Skonecki\n\n\n"
			":==:==:==:==:==:HELP:==:==:==:==:==:\n\n"
			"You are an adventurous skier.\n"
			"Your mission: survive as long as possible\n\n"
			"WARNING: game recognizes only lower-case letters\n\n"
			"CONTROLS:\n"
			"a - move left\n"
			"d - move right\n"
			"h - show this help\n"
			"m - return to menu\n"
			"q - exit\n\n"
			"You can now:\n"
			"M - return to menu\n"
			"R - return to game\n\n"

			);
	if(inputok==0) printf("There is no such option. Try again.\n");
	printf(">> ");

	int ch= mygetch();
	switch(ch)
	{
		case 113:
			setState(STATE_EXITING);
			inputok=1;
			break;
		case 'm':
			setState(STATE_MENU);
			inputok=1;
			break;
		case 114:
			setState(STATE_ALIVE);
			inputok=1;
			break;
		default:
			inputok=0;
			break;
	}
	return 0;
}
