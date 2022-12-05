/**
 * @file functions.c
 * @author Miguel Guzman (miguel.guzman@imt-atlantique.net)
 * @brief File containing auxiliary function definitions for 
 * retrieving/sorting/printing schools
 * @version 1.0
 * @date 2022-11-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

/**
 * @brief Checks if a pair of school sorting parameters is valid
 * 
 * @param attribute_index Index that refers to a school attribute
 * @param order String code that states a sorting order
 * @param num_attributes Number of attributes per school
 * @return int Status value
 */
int validateSortingParameters(int attribute_index, char* order, int num_attributes)
{
	if( ((attribute_index < 1) || (attribute_index > num_attributes)) || (strcmp(order, "asc") != 0) && (strcmp(order, "desc") != 0) )
		return -1;
	else
		return 0;
}

/**
 * @brief Gets the total number of schools given a raw HTML format text file
 * 
 * @param ranking_file File pointer for HTML raw data
 * @param max_chars Max length for the array of chars where each line read is stored
 * @return int Total number of schools in a HTML text file
 */
int getTotalSchools(FILE* ranking_file, int max_chars)
{
  char temp[max_chars];
  int schoolsCounter = 0;

	// Loop through the file to search for a school inforamtion section
  while(fgets(temp, max_chars, ranking_file) != NULL) 
  {
		if((strstr(temp, "data-url=\"/article/")) != NULL) 
			schoolsCounter++;
  }

  // Move the file pointer to the start
  fseek(ranking_file, 0, SEEK_SET);

  return schoolsCounter;
}

/**
 * @brief Extracts an attribute as a raw string given a string containing an attribute
 * 
 * @param file_line String containing a file line information
 * @return char* Attribute in raw string format
 */
char* getAttribute(char* file_line)
{
  // Save all possible char separators in an array (string)
  const char * separators = "<>";
  // Retrieve first token (empty space)
  char * strToken = strtok( file_line, separators);
  // Initialize a read token number counter
  int current_token_number = 1;
	
  // Loop until the 4th token is read since it contains the attribute information
  while ( current_token_number != 4 ) 
  {
		// Get the next token. NULL shall be used to tokenize current string without resetting pointer.
		strToken = strtok( NULL, separators );
		// Increase read token number counter
		current_token_number++;
  }
  // Return last read token (4th token with attribute information)
  return strToken;
}

/**
 * @brief Sets an atrribute value with its correct data type for a school individual
 * 
 * @param attribute_index Index that refers to a school attribute
 * @param raw_attribute Attribute in raw string format
 * @param current_school Pointer to school individual structure
 */
void fillSchoolInfo(int attribute_index, char* raw_attribute, school* current_school)
{
  switch (attribute_index)
  {
	case 1:
	  /* Global Ranking Attribute */
	  current_school->global_ranking = atoi(raw_attribute);
	  break;
	case 2:
	  /* School Name Attribute */
	  strcpy(current_school->name, raw_attribute);
	  //current_school->name = raw_attribute;
	  break;
	case 3:
	  /* Global Score Attribute */
	  current_school->global_score = atof(raw_attribute);
	  break;
	case 4:
	  /* Insertion Ranking Attribute */
	  current_school->insertion_ranking = atoi(raw_attribute);
	  break;
	case 5:
	  /* Enterprise Ranking Attribute */
	  current_school->enterprise_ranking = atoi(raw_attribute);
	  break;
	case 6:
	  /* Research Ranking Attribute */
	  current_school->research_ranking = atoi(raw_attribute);
	  break;
	case 7:
	  /* Research Ranking Attribute */
	  current_school->international_ranking = atoi(raw_attribute);
	  break;    
	default:
	  printf("\nReceived an invalid attribute index.\n");
	  break;
  }
}

/**
 * @brief Prints a school individual to terminal
 * 
 * @param myschool Pointer to school individual structure
 */
void printSchool(school* myschool)
{
	printf("\n\t%d\t\t%s\t\t%.2f\t\t%d\t\t%d\t\t%d\t\t%d\n", 
					myschool->global_ranking,
					myschool->name,
					myschool->global_score,
					myschool->insertion_ranking,
					myschool->enterprise_ranking,
					myschool->research_ranking,
					myschool->international_ranking);
}

/**
 * @brief Prints all schools in a school array to terminal
 * 
 * @param schools Pointer to an array of schools structure
 * @param num_schools Total number of schools in a HTML text file
 */
void printAllSchools(school* schools, int num_schools)
{
	printf("\nGlobal Ranking\tSchool Name\tGlobal Score\tInsertion Ranking\t"
		     "Enterprise Ranking\tResearch Ranking\tInternational Ranking\n");
	for(int i=0; i < num_schools; i++)
	{
		printSchool(&schools[i]);
	}
}

/**
 * @brief Prints a school individual to a given file
 * 
 * @param myschool Pointer to school individual structure
 * @param ranking_file Pointer to a text file for writing
 */
void printSchoolToFile(school* myschool, FILE* ranking_file)
{
	fprintf(ranking_file, "\n\t%d\t\t%s\t\t%.2f\t\t%d\t\t%d\t\t%d\t\t%d\n", 
					 myschool->global_ranking,
					 myschool->name,
					 myschool->global_score,
					 myschool->insertion_ranking,
					 myschool->enterprise_ranking,
					 myschool->research_ranking,
					 myschool->international_ranking);
}

/**
 * @brief Prints all schools in a school array to a newly created file
 * 
 * @param schools Pointer to an array of schools structure
 * @param num_schools Total number of schools in a HTML text file
 */
void printAllSchoolsToFile(school* schools, int num_schools)
{
  FILE *write_file;
  write_file = fopen("sorted_schools.txt", "w"); /*Creating file for writing*/
  
  if(write_file != NULL)
  {
    fprintf(write_file, "%s",
         "\nGlobal Ranking\tSchool Name\tGlobal Score\tInsertion Ranking\t"
		     "Enterprise Ranking\tResearch Ranking\tInternational Ranking\n");
	  
		for(int i=0; i < num_schools; i++)
	  {
		  printSchoolToFile(&schools[i], write_file);
	  }
		/* Closing the writing file */
    fclose(write_file);
  }
}

/**
 * @brief Sorts a school array given a sorting attribute and a sorting order
 * 
 * @param schools Pointer to an array of schools structure
 * @param num_schools Total number of schools in a HTML text file
 * @param attribute_index Index that refers to a school attribute
 * @param order String code that states a sorting order
 */
void sortSchools(school* schools, int num_schools, int attribute_index, char* order)
{
  switch (attribute_index)
  {
	case 1:
	  /* Global Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_globalRanking_asc : cmp_globalRanking_desc));
	  break;
	case 2:
	  /* School Name Attribute */	  
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_name_asc : cmp_name_desc));
	  break;
	case 3:
	  /* Global Score Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_globalScore_asc : cmp_globalScore_desc));
	  break;
	case 4:
	  /* Insertion Ranking Attribute */		
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_insertionRanking_asc : cmp_insertionRanking_desc));
	  break;
	case 5:
	  /* Enterprise Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_enterpriseRanking_asc : cmp_enterpriseRanking_desc));
	  break;
	case 6:
	  /* Research Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_researchRanking_asc : cmp_researchRanking_desc));
	  break;
	case 7:		
	  /* Research Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") == 0 ? cmp_internationalRanking_asc : cmp_internationalRanking_desc));
	  break;    
	default:
	  printf("\nReceived an invalid attribute index.\n");
	  break;
  }
}

/**
 * @brief Compares two school individuals given their global ranking in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_globalRanking_asc(const void * a, const void * b)
{
	return ( (((school*)a)->global_ranking > ((school*)b)->global_ranking) - (((school*)a)->global_ranking < ((school*)b)->global_ranking) );
}

/**
 * @brief Compares two school individuals given their global ranking in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_globalRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->global_ranking < ((school*)b)->global_ranking) - (((school*)a)->global_ranking > ((school*)b)->global_ranking) );
}

/**
 * @brief Compares two school individuals given their name in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_name_asc(const void * a, const void * b)
{
	return strcmp( ((school*)a)->name, ((school*)b)->name );
}

/**
 * @brief Compares two school individuals given their name in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_name_desc(const void * a, const void * b)
{
  return strcmp( ((school*)b)->name, ((school*)a)->name );
}

/**
 * @brief Compares two school individuals given their global score in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_globalScore_asc(const void * a, const void * b)
{
  return ( (((school*)a)->global_score > ((school*)b)->global_score) -(((school*)a)->global_score < ((school*)b)->global_score) );
}

/**
 * @brief Compares two school individuals given their global score in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_globalScore_desc(const void * a, const void * b)
{
  return ( (((school*)a)->global_score < ((school*)b)->global_score) - (((school*)a)->global_score > ((school*)b)->global_score) );
}

/**
 * @brief Compares two school individuals given their insertion ranking in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_insertionRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->insertion_ranking > ((school*)b)->insertion_ranking) - (((school*)a)->insertion_ranking < ((school*)b)->insertion_ranking) );
}

/**
 * @brief Compares two school individuals given their insertion ranking in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_insertionRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->insertion_ranking < ((school*)b)->insertion_ranking) - (((school*)a)->insertion_ranking > ((school*)b)->insertion_ranking) );
}

/**
 * @brief Compares two school individuals given their enterprise ranking in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_enterpriseRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->enterprise_ranking > ((school*)b)->enterprise_ranking) - (((school*)a)->enterprise_ranking < ((school*)b)->enterprise_ranking) );
}

/**
 * @brief Compares two school individuals given their enterprise ranking in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_enterpriseRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->enterprise_ranking < ((school*)b)->enterprise_ranking) - (((school*)a)->enterprise_ranking > ((school*)b)->enterprise_ranking) );
}

/**
 * @brief Compares two school individuals given their research ranking in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_researchRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->research_ranking > ((school*)b)->research_ranking) - (((school*)a)->research_ranking < ((school*)b)->research_ranking) );
}

/**
 * @brief Compares two school individuals given their research ranking in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_researchRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->research_ranking < ((school*)b)->research_ranking) - (((school*)a)->research_ranking > ((school*)b)->research_ranking) );
}

/**
 * @brief Compares two school individuals given their international ranking in ascending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_internationalRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->international_ranking > ((school*)b)->international_ranking) - (((school*)a)->international_ranking < ((school*)b)->international_ranking) );
}

/**
 * @brief Compares two school individuals given their international ranking in descending order
 * 
 * @param a Pointer to element of school array
 * @param b Pointer to element of school array
 * @return int Comparison result for sorting function
 */
int cmp_internationalRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->international_ranking < ((school*)b)->international_ranking) - (((school*)a)->international_ranking > ((school*)b)->international_ranking) );
}