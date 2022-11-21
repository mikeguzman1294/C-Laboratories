#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Definition of constants
#define MAX_FNAME_LENGTH 256
#define BYTE_NUMBER 10

// Struct proposed by professor
struct filestructure
{
	char filename[MAX_FNAME_LENGTH];
	unsigned int num_of_bytes;
};
typedef struct filestructure filestruct;


// File Packing Function
void file_packing(char *packed_file_name, int num_of_files, char **array_of_names)
{
	FILE *file_arr;
	FILE *packed_file;
	char *txt;
	char str[100];
	
	//open file and store the name
	packed_file = fopen(packed_file_name, "w+");
	//struct local variable
	filestruct packed;
	strcpy(packed.filename,packed_file_name);

	//for each file to pack
	for (int i=0; i< num_of_files; i++)
		{
		
		file_arr = fopen(array_of_names[i],"rb");//read a binary file
		strcpy(packed.filename,array_of_names[i]);

		if (file_arr != NULL)
		{
			//get the total number of bytes of the file
			fseek(file_arr, 0, SEEK_END);
			packed.num_of_bytes = ftell(file_arr);
			
			//read all the text and allocate it memory
			txt = (char*)malloc(packed.num_of_bytes*sizeof(char));
			fseek(file_arr, 0, SEEK_SET);
			fread(txt, sizeof(char), packed.num_of_bytes, file_arr);
			
			//write the name of the file with a length of 256 bytes
			fwrite(packed.filename, sizeof(char), MAX_FNAME_LENGTH, packed_file);
			
			//convert the number of bytes to a string and write it with a length of 10 bytes
			sprintf(str,"%d",packed.num_of_bytes);
			fwrite(str, sizeof(char), BYTE_NUMBER, packed_file);
			fprintf(packed_file,"\n");
			
			//write the text
			fwrite(txt, sizeof(char), packed.num_of_bytes, packed_file);
			free(txt);
			fclose(file_arr);
		}
	
	}
	fclose(packed_file);
} // End of File Packing Function

// File Unpacking Function
void file_unpacking(char *packed_file_name)
{
	FILE* unpack_file;
	unpack_file=fopen(packed_file_name,"r");
	FILE* file_out;
	
	//new struct variable
	filestruct unpack;

	int entire_file_bytes;
	char *entire_txt;
	char number_of_bytes[BYTE_NUMBER];
	int num;
	int n=0;
	
	//new directory to store unpacked files
	char *dirname="files_folder";
		
	if (unpack_file != NULL)
	{
		//read the total number of bytes for all the packed file
		fseek(unpack_file, 0, SEEK_END);
		entire_file_bytes = ftell(unpack_file);
		fseek(unpack_file,0, SEEK_SET);
		//open the new directory to save the files
    		chdir(dirname);
		
		while(n < entire_file_bytes)
		{
			//Get to the beginning of the file to unpack
			fseek(unpack_file,n, SEEK_SET);
			
			//Save the filename and create a file with that name
			fread(unpack.filename, sizeof(char), MAX_FNAME_LENGTH, unpack_file);
			file_out= fopen(unpack.filename, "w+");
			n += MAX_FNAME_LENGTH;

			//Read the file length
			fread(number_of_bytes, sizeof(char), BYTE_NUMBER, unpack_file);
			n += BYTE_NUMBER+1; //+1 because of the '\n' character
			//allocate memory to the text
			entire_txt=(char*)malloc(sizeof(char)*atoi(number_of_bytes));
			fseek(unpack_file,n, SEEK_SET);
			
			//read the text and then write it to the unpacked file
			fread(entire_txt, sizeof(char), atoi(number_of_bytes), unpack_file);
			fwrite(entire_txt, sizeof(char), atoi(number_of_bytes), file_out);
			
			n += atoi(number_of_bytes); //increment n
			
			free(entire_txt);
			fclose(file_out);
			}
		fclose(unpack_file);		
	}
} // End of File Unpacking Function