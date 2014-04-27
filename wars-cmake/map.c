#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include "util.h"
#include "state.h"
#include "define.h"
#include "stats.h"
#include "player.h"

//WINDOW *mainwin;

int generateNewLine(const char*, char*);
int copyLine(const char*,char*);
int playerx=DPLAYERX,playery=DPLAYERY;

char map[MAPROWS][MAPCOLS];
char lineseed[MAPCOLS]="ssssssssssssssssssss                    ssssssssssssssssssss";
char linenew[MAPCOLS];
char *linetemp;
int emptyfieldwidth = 20;
int emptyfieldoffset=2;

int bDrawMapFigure=0;
int figureId=0;//0-oval
int figureRadius=3;
int figureCenterX=0;
int figureHeight=4;
int figureBuildHeight=0;


int initMap()
{
//	mainwin=initscr();
	srand(time(NULL));
	return 0;

}

void drawMapFigure(char *linenew)
{
	char filling = ' ';
	char outer   = 's';
	if(figureBuildHeight==0)	figureCenterX=rand()%(emptyfieldwidth-figureRadius);
	linenew[figureCenterX]='s';
	linenew[figureCenterX+1]='s';
	linenew[figureCenterX-1]='s';
	figureBuildHeight++;
	if(figureBuildHeight >=figureHeight) 
	{
		bDrawMapFigure = 0;
		linenew[figureCenterX]=' ';
		linenew[figureCenterX+1]=' ';
		linenew[figureCenterX-1]=' ';
	}
	return;
}
int generateNewLine(const char *lineseed, char *linenew)
{
	copyLine(lineseed,linenew);

	//printf("\nline old: %s\n",lineseed);
	srand(time(NULL));
	int randval=rand()%5-2;
	//printf("Random number: %d\n", randval);
	int i;
	if (randval > 0&&emptyfieldoffset>1)
		for(i=1;i<=randval;i++)
		{
			char *pchar1 = strchr(linenew,' ')-1;
			*pchar1=' ';
			emptyfieldoffset=pchar1-linenew;
			//printf("emptyfieldoffset = %d",emptyfieldoffset);
			char *pchar2 = pchar1 +emptyfieldwidth;
			*pchar2='s';
			//*pchar1 = strrchr(linenew,' ')+1;
			//printf("character>: %c",*pchar1);
			//*pchar1 = ' ';
		}
	else if (randval < 0&&emptyfieldoffset<MAPCOLS-emptyfieldwidth)
		for(i=0;i>randval;i--)
		{
			char *pchar1 = strchr(linenew,' ');
			*pchar1='s';
			emptyfieldoffset = pchar1-linenew;
			
			//printf("emptyfieldoffset = %d",emptyfieldoffset);
			char *pchar2 = pchar1+emptyfieldwidth;
			*pchar2=' ';

			//*pchar1 = strrchr(linenew,' ');
			//printf("character<: %c",*pchar1);
			//*pchar1 = 's';
		}
	else {}
	//copyLine(linenew,lineseed);
	//printf("\nline new: %s\n",linenew);
	
	
	/* //due to fact that the current first line is a seed for next lines any additional routines should modify second not first line
	int randval2=rand()%3;
	if (randval2==0&&bDrawMapFigure==0)
	{
		bDrawMapFigure=1;
	}
	if(bDrawMapFigure==1)
	{
		//drawMapFigure(linenew);
	}

	int randval3=rand()%5;
	if(randval3==0) linenew[emptyfieldoffset+6]='@';
	return 0;
	*/

}
int copyLine(const char *str, char *strnew)
{
	int k;
	for(k=0;k<MAPCOLS;k++)
	{
		strnew[k]=str[k];
	}
	return 0;
}

int generateMap()
{
	//printf("generating map\n");
	int i,j;
	for(i=0;i<MAPROWS;i++)
	{
		for(j=0;j<MAPCOLS;j++)
		{
			map[i][j] = 's';
		}
	}
	for(i=0;i<MAPROWS;i++)
	{
		for(j=20;j<MAPCOLS-20;j++)
		{
			map[i][j] = ' ';
		}
	}
	
	map[playery][playerx] = 'H';
	
	/*for(i=playery;i>0;i--)
	{
		generateNewLine(map[i],map[i-1]);
	}*/
	return 0;
}

int regenerateMap()
{
	int i;
	//map[playery][playerx-1] = ' ';
	for(i=MAPROWS-1;i>0;i--)
	{
		copyLine(map[i-1],map[i]);
	}
	if(map[DPLAYERY][playerx]=='s') setState(STATE_DEAD);
	map[DPLAYERY][playerx] = 'H';
	generateNewLine(map[1],map[0]);
	return 0;
}

int drawMap(WINDOW *drawwin)
{
	char linebuf[MAPCOLS+2];
	//snprintf(linebuf,MAPCOLS+3,)
	wmove(drawwin,0,0);
	int i;
	for(i=0;i<MAPROWS;i++)
	{

			//snprintf(drawBuf[i],MAPCOLS,"%s",map[i]);
			wmove(drawwin,i+1,2);
			snprintf(linebuf,MAPCOLS+3,"%s",map[i]);
			waddstr(drawwin,linebuf);
	}
//	sprintf(linebuf,"                       ");
//	mvwaddstr(drawwin,i+2,2,linebuf);
//	wmove(drawwin,i+5,2);
//	sprintf(linebuf,"SCORE: %d",getPoints());
//	waddstr(drawwin,linebuf);
//	sprintf(linebuf,"----------------------------------------");
//	mvwaddstr(drawwin,i+9,2,linebuf);
//	sprintf(linebuf,"h - help | m - main menu | q - exit game");
//	mvwaddstr(drawwin,i+10,2,linebuf);
	sprintf(linebuf,"\n\n  SCORE: %d",getPoints());
	waddstr(drawwin,linebuf);
	sprintf(linebuf,"----------------------------------------\n");
	waddstr(drawwin,linebuf);
	sprintf(linebuf,"  h - help | m - main menu | q - exit game");
	waddstr(drawwin,linebuf);
	box(drawwin,0,0);//this causes errors in displaying why?
	wrefresh(drawwin);
	return 0;
}
void setPlayerPosition(int x, int y)
{
	playerx = x;
	playery = y;
}
int ch;
int updatePlayer()
{
	ch = mygetch2();
	//initialise_ios();
	//int ch = get_key();
	//printf("%d = %c",ch,ch);
	if(ch==97)  {--playerx;}
	else if(ch==100)  {++playerx;}
	else if(ch=='h') {setState(STATE_HELP);}
	else if(ch=='m') {setState(STATE_MENU);}
	else if(ch==113) {setState(STATE_EXITING);}
	else if(ch==112) {setState(STATE_PAUSE);}
	else {}
	addPoints(1);
	
	if(map[DPLAYERY][playerx]=='s') setState(STATE_DEAD);
	if(map[DPLAYERY][playerx]=='@') addPoints(40);
	
	setThrottle(0.9);
	usleep((int)getThrottle());
	
	//printf("playerx = %d playery = %d state = %d\n", playerx,playery,getState());
	return 0;
}

