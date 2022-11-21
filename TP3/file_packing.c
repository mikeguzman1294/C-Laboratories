#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "packing_GUZMAN.h"

// Main Function
void main(int argc, char **argv)
{
	// Create an array to store n-argc file names
	char* file_names[argc];

	// Take the first cmd argument as the folder name	
	char* packed_file_name = argv[1];
	int num_of_files = argc-2;
	
	// We get more than one file name argument through terminal	
	if( argc > 2 )
	{
		for (int i=0; i<argc-2; i++)
		{
			file_names[i] = argv[i+2];
		}
		printf("Received several file names.\nFiles will be packed into a file folder.");
		file_packing(packed_file_name, num_of_files, file_names);		
	}
	// We get only one file name (folder)
	else if ( argc == 2)
	{
		printf("Received only one file name.\nThis folder will be unpacked.");
		system("mkdir files_folder"); //create new directory
		file_unpacking(packed_file_name);		
	}
	else
	{
		printf("No arguments were provided.\nNothing will be done.");
	}		
} // End of main function