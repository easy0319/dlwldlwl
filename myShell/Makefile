CC = gcc
CFLAGS =
OBJS = myShell.c
LIBS =
all : myShell myMv myCp myDate

myShell:$(OBJS)
	$(CC) $(CFLAGS) -o myShell $(OBJS) $(LIBS)
	
myMv:	myMv.c
	$(CC) $(CFLAGS) -o myMv myMv.c

myCp:	myCp.c
	$(CC) $(CFLAGS)	-o myCp myCp.c

myDate:	myDate.c
	$(CC) $(CFLAGS)	-o myDate myDate.c

clean:
	rm -f myShell myMv myCp myDate
