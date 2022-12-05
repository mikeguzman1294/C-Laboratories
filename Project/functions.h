/**
 * @file functions.h
 * @author Miguel Guzman (miguel.guzman@imt-atlantique.net)
 * @brief Header File for declaring school's ranking information
 * retrieval required data structures and auxiliary functions
 * @version 1.0
 * @date 2022-11-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Structure that represents an individual school.
 * 
 */
typedef struct school{
  int global_ranking;
  char name[40];
  float global_score;
  int insertion_ranking;
  int enterprise_ranking;
  int research_ranking;
  int international_ranking;
} school;

/* Function Declaration Section */

int validateSortingParameters(int attribute_index, char* order, int num_attributes);

int getTotalSchools(FILE * ranking_file, int max_chars);

char* getAttribute(char* file_line);

void fillSchoolInfo(int attribute_index, char* raw_attribute, school* current_school);

void printSchool(school* myschool);

void printAllSchools(school* schools, int num_schools);

void printSchoolToFile(school* myschool, FILE* ranking_file);

void printAllSchoolsToFile(school* schools, int num_schools);

void sortSchools(school* schools, int num_schools, int attribute_index, char* order);

/* Comparing Functions Section */

int cmp_globalRanking_asc(const void * a, const void * b);

int cmp_globalRanking_desc(const void * a, const void * b);


int cmp_name_asc(const void * a, const void * b);

int cmp_name_desc(const void * a, const void * b);


int cmp_globalScore_asc(const void * a, const void * b);

int cmp_globalScore_desc(const void * a, const void * b);


int cmp_insertionRanking_asc(const void * a, const void * b);

int cmp_insertionRanking_desc(const void * a, const void * b);


int cmp_enterpriseRanking_asc(const void * a, const void * b);

int cmp_enterpriseRanking_desc(const void * a, const void * b);


int cmp_researchRanking_asc(const void * a, const void * b);

int cmp_researchRanking_desc(const void * a, const void * b);


int cmp_internationalRanking_asc(const void * a, const void * b);

int cmp_internationalRanking_desc(const void * a, const void * b);