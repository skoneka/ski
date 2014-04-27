/*
 * =====================================================================================
 *
 *       Filename:  player.c
 *
 *    Description:  <CURSOR>
 *
 *        Version:  1.0
 *        Created:  07.05.2009 17:45:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */
#include "player.h"

#define MAXTIME 1000000 //in microseconds
float throttle;

void setThrottle(float val)
{
	throttle = MAXTIME-val*MAXTIME;
}

float getThrottle()
{
	return throttle;
}
