#ifndef _MAP_H_
#define _MAP_H_
#include <curses.h>
//int generateNewLine(const char*, char*);
int generateMap();
int regenerateMap();
int drawMap(WINDOW *drawwin);
int updatePlayer();
int isDone();
void setPlayerPosition(int x, int y);
//extern static int pointscounter=0;
#endif //_MAP_H_

