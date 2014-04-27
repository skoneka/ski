#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "state.h"
#include "define.h"
#include "stats.h"

int generateNewLine(const char*, char*);
int copyLine(const char*,char*);
int playerx=DPLAYERX,playery=DPLAYERY;

char map[MAPROWS][MAPCOLS];
char lineseed[MAPCOLS]="ssssssssssssssssssss                    ssssssssssssssssssss";
char linenew[MAPCOLS];
char *linetemp;
int emptyfieldwidth = 20;
int emptyfieldoffset=2;


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
	return 0;

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
	printf("generating map\n");
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

int drawMap()
{
	system("clear");
	int i,j;
	for(i=0;i<MAPROWS;i++)
	{

		for(j=0;j<MAPCOLS;j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
	
	printf("\nScore: %d\n",getPoints());
	printf("----------------------------------------\n"
		   "h - help | m - main menu | q - exit game\n");
	//generateNewLine();
	return 0;
}
void setPlayerPosition(int x, int y)
{
	playerx = x;
	playery = y;
}
int updatePlayer()
{
	int ch = mygetch();
	//printf("%d = %c",ch,ch);
	if(ch==97)  {--playerx;}
	else if(ch==100)  {++playerx;}
	else if(ch=='h') {setState(STATE_HELP);}
	else if(ch=='m') {setState(STATE_MENU);}
	else if(ch==113) {setState(STATE_EXITING);}
	else {}
	setPoints(getPoints()+1);
	
	if(map[DPLAYERY][playerx]=='s') setState(STATE_DEAD);

	//printf("playerx = %d playery = %d state = %d\n", playerx,playery,getState());
	return 0;
}

