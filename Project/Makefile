CC=gcc
VERSION=release
CFLAGS=-O2

ifeq ($(VERSION), debug)
	CFLAGS=-g
endif

######## MAKE ALL #########

all: main.o functions.o
	$(CC) main.o functions.o -o schools_ranking.out

######## MAKE RULES #########	

main.o: main.c functions.h
	$(CC) -c $(CFLAGS) main.c

functions.o: functions.c functions.h
	$(CC) -c $(CFLAGS) functions.c

run_main: all
	./schools_ranking.out

######## CLEAN #########

clean:
	rm -f *.o *.txt *.out