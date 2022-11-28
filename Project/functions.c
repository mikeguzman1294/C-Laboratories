#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int getTotalSchools(FILE* ranking_file, int max_chars)
{
  char temp[max_chars];
  int schoolsCounter = 0;

  while(fgets(temp, max_chars, ranking_file) != NULL) 
  {
		if((strstr(temp, "data-url=\"/article/")) != NULL) 
			schoolsCounter++;
  }

  // Move the file pointer to the start
  fseek(ranking_file, 0, SEEK_SET);

  return schoolsCounter;
}

char* getAttribute(char* file_line)
{
  // Save all possible char separators in an array (string)
  const char * separators = "<>";
  // Retrieve first token (empty space)
  char * strToken = strtok( file_line, separators);
  // Initialize a read token number counter
  int current_token_number = 1;
	
  // Loop until the 4th token is read since it contains the attribut information
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

void printAllSchools(school* schools, int num_schools)
{
	printf("\nGlobal Ranking\tSchool Name\tGlobal Score\tInsertion Ranking\t"
		     "Enterprise Ranking\tResearch Ranking\tInternational Ranking\n");
	for(int i=0; i < num_schools; i++)
	{
		printSchool(&schools[i]);
	}
}

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

void sortSchools(school* schools, int num_schools, int attribute_index, char* order)
{
  switch (attribute_index)
  {
	case 1:
	  /* Global Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_globalRanking_asc : cmp_globalRanking_desc));
	  break;
	case 2:
	  /* School Name Attribute */	  
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_name_asc : cmp_name_desc));
	  break;
	case 3:
	  /* Global Score Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_globalScore_asc : cmp_globalScore_desc));
	  break;
	case 4:
	  /* Insertion Ranking Attribute */		
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_insertionRanking_asc : cmp_insertionRanking_desc));
	  break;
	case 5:
	  /* Enterprise Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_enterpriseRanking_asc : cmp_enterpriseRanking_desc));
	  break;
	case 6:
	  /* Research Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_researchRanking_asc : cmp_researchRanking_desc));
	  break;
	case 7:		
	  /* Research Ranking Attribute */
	  qsort(schools, num_schools, sizeof(school), (strcmp(order,"asc") ? cmp_internationalRanking_asc : cmp_internationalRanking_desc));
	  break;    
	default:
	  printf("\nReceived an invalid attribute index.\n");
	  break;
  }
}

int cmp_globalRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->global_ranking < ((school*)b)->global_ranking) - (((school*)a)->global_ranking > ((school*)b)->global_ranking) );
}

int cmp_globalRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->global_ranking > ((school*)b)->global_ranking) - (((school*)a)->global_ranking < ((school*)b)->global_ranking) );
}


int cmp_name_asc(const void * a, const void * b)
{
	return strcmp( ((school*)b)->name, ((school*)a)->name );
}

int cmp_name_desc(const void * a, const void * b)
{
  return strcmp( ((school*)a)->name, ((school*)b)->name );
}


int cmp_globalScore_asc(const void * a, const void * b)
{
  return ( (((school*)a)->global_score < ((school*)b)->global_score) -(((school*)a)->global_score > ((school*)b)->global_score) );
}

int cmp_globalScore_desc(const void * a, const void * b)
{
  return ( (((school*)a)->global_score > ((school*)b)->global_score) - (((school*)a)->global_score < ((school*)b)->global_score) );
}


int cmp_insertionRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->insertion_ranking < ((school*)b)->insertion_ranking) - (((school*)a)->insertion_ranking > ((school*)b)->insertion_ranking) );
}

int cmp_insertionRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->insertion_ranking > ((school*)b)->insertion_ranking) - (((school*)a)->insertion_ranking < ((school*)b)->insertion_ranking) );
}


int cmp_enterpriseRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->enterprise_ranking < ((school*)b)->enterprise_ranking) - (((school*)a)->enterprise_ranking > ((school*)b)->enterprise_ranking) );
}

int cmp_enterpriseRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->enterprise_ranking > ((school*)b)->enterprise_ranking) - (((school*)a)->enterprise_ranking < ((school*)b)->enterprise_ranking) );
}


int cmp_researchRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->research_ranking < ((school*)b)->research_ranking) - (((school*)a)->research_ranking > ((school*)b)->research_ranking) );
}

int cmp_researchRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->research_ranking > ((school*)b)->research_ranking) - (((school*)a)->research_ranking < ((school*)b)->research_ranking) );
}


int cmp_internationalRanking_asc(const void * a, const void * b)
{
  return ( (((school*)a)->international_ranking < ((school*)b)->international_ranking) - (((school*)a)->international_ranking > ((school*)b)->international_ranking) );
}

int cmp_internationalRanking_desc(const void * a, const void * b)
{
  return ( (((school*)a)->international_ranking > ((school*)b)->international_ranking) - (((school*)a)->international_ranking < ((school*)b)->international_ranking) );
}