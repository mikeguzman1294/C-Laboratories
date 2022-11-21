CC=gcc
VERSION=release
CFLAGS=-O3

ifeq ($(VERSION), debug)
	CFLAGS=-g
endif

all: exercise_1 exercise_2 exercise_3 exercise_4 exercise_5

######## EXERCISE 1 #########

exercise_1: myfirstprogram.o
	$(CC) -o exercise_1 myfirstprogram.o

myfirstprogram.o: myfirstprogram.c
	$(CC) -c $(CFLAGS) myfirstprogram.c

run_exercise_1: exercise_1
	./exercise_1

######## EXERCISE 2 #########

exercise_2: sizeDataTypes.o
	$(CC) -o exercise_2 sizeDataTypes.o

sizeDataTypes.o: sizeDataTypes.c
	$(CC) -c $(CFLAGS) sizeDataTypes.c

run_exercise_2: exercise_2
	./exercise_2

######## EXERCISE 3 #########

exercise_3: logical_use.o logical.o
	$(CC) -o exercise_3 logical_use.o logical.o

logical_use.o: logical_use.c
	$(CC) -c $(CFLAGS) logical_use.c

logical.o: logical.c
	$(CC) -c $(CFLAGS) logical.c

run_exercise_3: exercise_3
	./exercise_3

######## EXERCISE 4 #########

exercise_4: printableCharacters.o
	$(CC) -o exercise_4 printableCharacters.o

printableCharacters.o: printableCharacters.c
	$(CC) -c $(CFLAGS) printableCharacters.c

run_exercise_4: exercise_4
	./exercise_4

######## EXERCISE 5 #########

exercise_5: currencyConversion.o
	$(CC) -o exercise_5 currencyConversion.o

currencyConversion.o: currencyConversion.c
	$(CC) -c $(CFLAGS) currencyConversion.c

run_exercise_5: exercise_5
	./exercise_5

######## CLEAN #########

clean:
	rm *.o *.exe all