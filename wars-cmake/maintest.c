#include <stdio.h>
#include "util.h"

int main(int argc, char *argv[])
{
	int ch=0;;
	while(ch!=113||ch!='q')
	{
		int ch = mygetch();
		printf("%d = %c\n",ch,ch);
	}
}
