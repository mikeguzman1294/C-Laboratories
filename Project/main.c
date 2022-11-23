#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_LINE 2048
#define NUM_ATTRIBUTES 7

// Website URL https://www.usinenouvelle.com/comparatif-des-ecoles-d-ingenieurs-2022

// Main Function
int main(int argc, char** argv)
{    
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

    char temp[MAX_LINE];
    int line_num = 1;
	int total_schools = getTotalSchools(myfile, MAX_LINE);
    printf("\nNumber of Schools: %d\n", total_schools);

    int count = 0;

    while(fgets(temp, MAX_LINE, myfile) != NULL) 
    {
		if((strstr(temp, "data-url=\"/article/")) != NULL) 
        {
			printf("Ocurrence found on line: %d\n", line_num);

            while(count < NUM_ATTRIBUTES)
            {
                fgets(temp, MAX_LINE, myfile);
                if( (strstr(temp, "<td ><a href=")) != NULL || (strstr(temp, "<td class=")) != NULL)
                {
                    //printf("\n%s\n", temp);
                    getAttribute(temp);
                    count++;
                }
            }
            count = 0; 
		}
		line_num++;
	}

    /* Closing the file */
    fclose(myfile);


    printf("\nNumber of Schools: %d\n", total_schools);

    return 0;
}// End of main function