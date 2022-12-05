/**
 * @file main.c
 * @author Miguel Guzman (miguel.guzman@imt-atlantique.net)
 * @brief Main File for extracting & sorting Usine Nouvelle's ranking
 * 
 * This file contains the main function that extracts HTML code from Usine
 * Nouvelle's schools of engineering ranking website into a text file.
 * The text file is read to retrieve the information regarding the schools
 * ranking and this information is deposited inside a data structure that 
 * can be sorted given user-defined sorting parameters.
 * The sorted list of schools is printed into a text file for the user.
 * @see https://www.usinenouvelle.com/comparatif-des-ecoles-d-ingenieurs-2022
 * @version 1.0
 * @date 2022-11-28
 * 
 * @copyright Copyright (c) 2022 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_LINE 2048
#define NUM_ATTRIBUTES 7

/**
 * @brief Main Function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv)
{    
  // Declare sorting arguments' variables
  int attribute_index;
  char order[5];

  /* 
    Check number of arguments to be input through command line.
    First argument is always the program name.
    So if we intend to pass 2 parameters, 3 cmd parameters should be expected.
    If the exact number of expected cmd arguments is not passed use standard input by default.
  */
  if(argc == 3)
  {
    // Extract values from cmd arguments
    attribute_index = atoi(argv[1]);
    strcpy(order, argv[2]);    
  }
  else
  {
    // Enter values through scanf
    printf("\nChoose sorting attribute index given the following table:"
           "\nGlobal Ranking = 1\nSchool Name = 2\nGlobal Score = 3\nInsertion Ranking = 4"
		       "\nEnterprise Ranking = 5\nResearch Ranking = 6\nInternational Ranking = 7"
           "\nEnter the attribute index here:\t");
    (void)!scanf(" %d", &attribute_index);
    printf("\nChoose sorting order:\nAscending order = 'asc'\nDescending order = 'desc'"
           "\nEnter the sorting order here:\t");
    (void)!scanf(" %s", order);
  }

	// Check if the entered sorting parameters are valid, if they are not then end the program execution
	if(validateSortingParameters(attribute_index, order, NUM_ATTRIBUTES) == -1)
	{
		printf("Entered invalid sorting parameters.\nEnding program...\n");
		return -1;
	}

  // Call wget from system command line to import given website html information into a text file in local drive
  int systemRet = system("wget --quiet --output-document=usinenouvelle.txt https://www.usinenouvelle.com/comparatif-des-ecoles-d-ingenieurs-2022");
    
  // Error handling since system is not guaranteed to succeed
  if(systemRet == -1)
  {
    // The system method failed
    printf("System method failed.\nUnable to retrieve content from webpage.\nEnding program...\n");
    return -1;
  }   

  FILE *myfile; /*Declaration of file pointer*/    
  myfile = fopen("usinenouvelle.txt", "r"); /*Opening of the text file for reading*/

  // Get the number of schools contained in text file for the array memory allocation
  int total_schools = getTotalSchools(myfile, MAX_LINE);

  // Dinamically allocate memory for the array of school structures
  school* school_array;
  school_array = (school*)malloc(sizeof(school) * total_schools);

  // Declare/initialize variables for parsing text file
  char temp[MAX_LINE];
  int attribute_counter = 1;
  int school_counter = 0;

  // While loop for traversing text file to extract school information
  while( (school_counter < total_schools) && (fgets(temp, MAX_LINE, myfile) != NULL) ) 
  {
    if((strstr(temp, "data-url=\"/article/")) != NULL) 
    {
      while( (attribute_counter <= NUM_ATTRIBUTES) && (fgets(temp, MAX_LINE, myfile) != NULL) )
      {        
        if( (strstr(temp, "<td ><a href=")) != NULL || (strstr(temp, "<td class=")) != NULL)
        {
          fillSchoolInfo(attribute_counter, getAttribute(temp), &school_array[school_counter]);
          attribute_counter++;
        }
      }      
      // Reset attribute counter after extracting full information of a school
      attribute_counter = 1;
      // Increment school counter after extracting all attributes of a school individual
      school_counter++;
    }
  }

  /* Closing the reading file */
  fclose(myfile);

  // Sort school array according to user-defined input parameters
  sortSchools(school_array, total_schools, attribute_index, order);
  
  // Uncomment next line to print all schools to terminal for debugging
  //printAllSchools(school_array, total_schools);

  // Print all schools to text file for user
  printAllSchoolsToFile(school_array, total_schools);

  // Free the memory allocated for the schools array
  free(school_array);

  return 0;
}// End of main function