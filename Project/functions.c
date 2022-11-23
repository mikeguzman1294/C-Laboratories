#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    while ( current_token_number != 4 ) {
        // Get the next token. NULL shall be used to tokenize current string without resetting pointer.
        strToken = strtok( NULL, separators );
        // Increase read token number counter
        current_token_number++;
    }
    printf ( "Extracted attribute: %s\n", strToken );
    // Return last read token (4th token with attribute information)
    return strToken;
}