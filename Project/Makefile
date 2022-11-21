CC=gcc
VERSION=release
CFLAGS=-O3

ifeq ($(VERSION), debug)
	CFLAGS=-g
endif

######## MAKE ALL #########

all: main.o functions.o
	$(CC) -o schools_ranking.out main.o functions.o

######## MAKE RULES #########	

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

functions.o: functions.c
	$(CC) -c $(CFLAGS) functions.c

run_main: all
	./schools_ranking.out

######## CLEAN #########

clean:
	rm *.o *.exe *.txt *.out all