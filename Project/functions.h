/*
Header File for defining school's ranking information retrieval
required data structures and auxiliary functions.
*/

// Definition of structure to hold each school's information
typedef struct school{
  int global_ranking;
  char* name;
  float global_score;
  int insertion_ranking;
  int enterprise_ranking;
  int research_ranking;
  int international_ranking;
} school;

/*
Function declaration
*/

char* getAttribute(char* file_line);

void printSchool(school myschool);

int getTotalSchools(FILE * ranking_file, int max_chars);