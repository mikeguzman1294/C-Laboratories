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