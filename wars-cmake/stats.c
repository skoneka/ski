#include "stats.h"

int pointscounter=0;
int savedpointscounter=0;

int getPoints()
{
	return pointscounter;
}
void setPoints(int val)
{
	pointscounter=val;
}
void  addPoints(int val)
{
	setPoints(getPoints()+val);
}
int getSavedPoints()
{
	return savedpointscounter;
}
void savePoints()
{
	savedpointscounter=pointscounter;
}
