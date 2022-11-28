#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"

#define MAX_LINE 2048
#define NUM_ATTRIBUTES 7

// Website URL https://www.usinenouvelle.com/comparatif-des-ecoles-d-ingenieurs-2022

// Main Function
int main(int argc, char** argv)
{    
  // Declare sorting arguments variables
  int attribute_index;
  char order[4];

  /* 
    Check number of arguments to be input through command line.
    First argument is always the program name.
    So if we intend to pass 2 parameters, 3 cmd parameters should be expected.
  */
  /*if(argc == 3)
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
    scanf(" %d", &attribute_index);
    printf("\nChoose sorting order:\nAscending order = 'asc'\nDescending order = 'desc'"
           "\nEnter the sorting order here:\t");
    scanf(" %s", &order);
  }

  printf("\nAttribute index: %d\n", attribute_index);
  printf("\nOrder: %s\n", order);*/
  
  
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
  myfile = fopen("usinenouvelle.txt", "r"); /*Opening of the file for reading*/

  // Get the number of schools contained in text file for array memory allocation
  int total_schools = getTotalSchools(myfile, MAX_LINE);

  // Dinamically allocate memory for the array of school structures
  school* school_array;
  school_array = (school*)malloc(sizeof(school) * total_schools);

  // Declare/initialize variables for parsing text file
  char temp[MAX_LINE];
  int attribute_counter = 1;
  int school_counter = 0;

  // While loop for traversing text file to extract school information
  while(fgets(temp, MAX_LINE, myfile) != NULL) 
  {
    if((strstr(temp, "data-url=\"/article/")) != NULL) 
    {
      while(attribute_counter <= NUM_ATTRIBUTES)
      {
        fgets(temp, MAX_LINE, myfile);
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
  //sortSchools(school_array, total_schools, attribute_index, order);
  sortSchools(school_array, total_schools, 4, "asc");
  
  // Print all schools
  printAllSchools(school_array, total_schools);


  printAllSchoolsToFile(school_array, total_schools);

  // Free the memory allocated for the schools array
  free(school_array);

  return 0;
}// End of main function