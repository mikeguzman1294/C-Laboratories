CC=gcc
VERSION=release
CFLAGS=-O3

ifeq ($(VERSION), debug)
	CFLAGS=-g
endif

all: exercise_1 exercise_2 exercise_3

######## EXERCISE 1 #########

exercise_1: gaussian_plot.o
	$(CC) -o exercise_1 gaussian_plot.o

gaussian_plot.o: gaussian_plot.c
	$(CC) -c $(CFLAGS) gaussian_plot.c

run_exercise_1: exercise_1
	./exercise_1 3 0.6 20

######## EXERCISE 2 #########

exercise_2: binary_file.o
	$(CC) -o exercise_2 binary_file.o

binary_file.o: binary_file.c
	$(CC) -c $(CFLAGS) binary_file.c

run_exercise_2: exercise_2
	./exercise_2

######## EXERCISE 3 #########

exercise_3: file_packing.o packing_GUZMAN.o
	$(CC) -o exercise_3 file_packing.o packing_GUZMAN.o

packing_GUZMAN.o: packing_GUZMAN.c packing_GUZMAN.h
	$(CC) -c $(CFLAGS) packing_GUZMAN.c

file_packing.o: file_packing.c packing_GUZMAN.h
	$(CC) -c $(CFLAGS) file_packing.c

run_exercise_3: exercise_3
	./exercise_3 folder dummy.txt dummy2.txt

######## CLEAN #########

clean:
	rm *.o *.exe all