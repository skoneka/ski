OBJS = main.o map.o screens.o state.o util.o stats.o
SRCS = main.c map.c screens.c state.c util.c stats.c
CC=gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)



#main.o: main.c map.h state.h define.h util.h

#map.o: map.c map.h

#screens.o: screens.c screens.h

#state.o: state.c state.h

#util.o: util.c util.h


all: ski
	
ski: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ski

clean:
	\rm *.o *~ ski
	
