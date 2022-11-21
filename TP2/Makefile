CC=gcc
VERSION=release
CFLAGS=-O3

ifeq ($(VERSION), debug)
	CFLAGS=-g
endif

all: exercise_1 exercise_2

######## EXERCISE 1 #########

exercise_1: exchange_values.o exchange.o
	$(CC) -o exercise_1 exchange_values.o exchange.o

exchange_values.o: exchange_values.c
	$(CC) -c $(CFLAGS) exchange_values.c

exchange.o: exchange.c
	$(CC) -c $(CFLAGS) exchange.c

run_exercise_1: exercise_1
	./exercise_1

######## EXERCISE 2 #########

exercise_2: transpose_matrix.o exchange.o
	$(CC) -o exercise_2 transpose_matrix.o exchange.o

transpose_matrix.o: transpose_matrix.c
	$(CC) -c $(CFLAGS) transpose_matrix.c

run_exercise_2: exercise_2
	./exercise_2

######## CLEAN #########

clean:
	rm *.o *.exe all