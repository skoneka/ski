#include "util.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define END_FILE_CHARACTER 0x04

int mygetch()
{
	struct termios oldt,newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag&=~(ICANON|ECHO);
	newt.c_cc[VMIN]=1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW,&oldt);
	return ch;
}

int mygetch0()
{
//	tcflush(STDIN_FILENO,TCIFLUSH);
	struct termios oldt,newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag&=~(ICANON|ECHO);
//	cfmakeraw(&newt);
	newt.c_cc[VMIN]=0;
//	newt.c_cc[VTIME]=1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	//tcflush(TCIOFLUSH,TCIFLUSH);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	
	tcflush(0,TCIFLUSH);
	return ch;
}
//no wait and clear buffer
int mygetch2()
{
//	tcflush(STDIN_FILENO,TCIFLUSH);
	struct termios oldt,newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag&=~(ICANON|ECHO);
//	cfmakeraw(&newt);
	newt.c_cc[VMIN]=0;
//	newt.c_cc[VTIME]=1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	newt.c_cc[VTIME]=0;
	tcsetattr(STDIN_FILENO,TCSANOW,&newt);
	while(getchar()!=-1){}//empties the buffer
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

int linux_getch(void)
{
  struct termios oldstuff;
  struct termios newstuff;
  int    inch;

  tcgetattr(STDIN_FILENO, &oldstuff);
  newstuff = oldstuff;                  /* save old attributes               */
  newstuff.c_lflag &= ~(ICANON | ECHO); /* reset "canonical" and "echo" flags*/
  tcsetattr(STDIN_FILENO, TCSANOW, &newstuff); /* set new attributes         */
  inch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldstuff); /* restore old attributes     */

  if (inch == END_FILE_CHARACTER) {
    inch = EOF;
  }
  return inch;
}



#include		<fcntl.h>
#include		<sys/ioctl.h>
#if defined(__NetBSD__)
# include <termios.h>
# include <termcap.h>
#endif
#if defined(__sun)
# define__lint
# include <sys/types.h>
# include <stropts.h>
# include <curses.h>
# include <sys/conf.h>
# include <termio.h>
# include <term.h>
char *tgoto(char *cap, int col, int row);
#endif
#if defined(__alpha)
# include <termio.h>
# include <term.h>
#endif
#define SLEEP_TIME 1000
 
void	initialise_ios_general(void)
{
#if (defined(__NetBSD__) || defined(__alpha))
	struct termios		termios;
	int				 status;
	status = ioctl(0, TIOCGETA, &termios);
	if (status == -1)
		exit(-1);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	status = ioctl(0, TIOCSETA, &termios);
	if (status == -1)
		exit(-1);
	status = fcntl(0, F_SETFL, O_NONBLOCK);
	if (status == -1)
		exit(-1);
#endif
}
 
void	initialise_ios_sun(void)
{
#if defined(__sun)
	struct termio termio;
	intstatus;
	status = ioctl(0, TCGETA, &termio);
	if (status == -1)
		exit(-1);
	termio.c_lflag &= ~(ICANON | ECHO);
	termio.c_cc[VMIN] = 1;
	termio.c_cc[VTIME] = 0;
	status = ioctl(0, TCSETA, &termio);
	if (status == -1)
		exit(-1);
	status = fcntl(0, F_SETFL, O_NONBLOCK);
	if (status == -1)
		exit(-1);
#endif
}
void	initialise_ios(void)
{
#if defined(__sun)
	initialise_ios_sun();
#else
	initialise_ios_general();
#endif
}
 
unsigned int	get_key(void)
{
	unsigned char c;
	unsigned int key;
	while (read(0, &c, 1) != -1)
		;
	while (read(0, &c, 1) < 0)
		usleep(0);
	key = c;
	usleep(SLEEP_TIME);
	while (read(0, &c, 1) != -1)
		{
		 key <<= 8;
		 key |= c;
		}
	return (key);
}


