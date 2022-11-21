#include <stdlib.h> //<-- Used for the standard functions
#include <stdio.h>  //<-- Used for the printf
#include <string.h>  //<-- To use string functions and strlen
#include <ctype.h>  //<-- To use toupper function
#include <unistd.h>
#include "functions.h"

/* --- Definition of constants --- */

#define TRUE               1                             /* Boolean Flags definition" */
#define FALSE               0
          

//void aide( char * nomComm );

////Function declaration for tp1///
void TP4__2__1( int arg_sort);
void help();


//Global debugg variables 
int debug_mode=FALSE; //flag to access debug mode

/* === Main Function ====================================================================== */

int main( int argc, char * argv[] )
{

   int numExo = 0; //selector of the Number of Exercise to execute
   int needHELP = FALSE; //Flag to display help
   int arg_sort;
   int i, j; //for variables
   debug_mode=FALSE; 

   putchar( '\n' );
   system( "clear" );


   /* --- Show the arguments introduced to the program --- */

   printf( "Received command line :\n\t" );
   for ( i = 0; i < argc; ++i ) 
      printf( "%s ", argv[i]);
      putchar( '\n' );
   
   
   for ( i = 1; (i < argc) && (! needHELP ); ++i )
   {

      needHELP = TRUE; //Activates the help in case no valid option is  found 

      if ( !strcmp(argv[i], "-h") ) {
            //sprintf( message, "\nTP1 EXERCISE 2.1 -\n" );
            needHELP=FALSE;
            help(argv[0]);
      }
      if ( !strcmp(argv[i], "-d") ) {
            //sprintf( message, "\nTP1 EXERCISE 2.1 -\n" );
            debug_mode=TRUE;
      }
      if ( !strcmp(argv[i], "EX2_1") ) {
            //sprintf( message, "\nTP1 EXERCISE 2.1 -\n" );
            needHELP = FALSE;
            numExo=21;
            arg_sort = atoi(argv[i+1]);
            //TP1_EXO2_1( );
         } 
   } /* end for */

/* --- Show Help if needed or typing an incorrect option --- */

   putchar( '\n' );
   if ( needHELP )
         help( argv[0] );
   putchar( '\n' );

/* ----If no help needed, then it executes the code acording to the required arguments ---*/

   switch(numExo){
      case 21:
         TP4__2__1(arg_sort);
         break;

      defaut:
         printf("NO VALID OPTION FOUND");
   }
   


   return EXIT_SUCCESS;

}


/* === Excercise 2.1 ======================================================================= */
void TP4__2__1( int arg_sort) //start of the main program
{ 
   char params[128];

   if(debug_mode==TRUE){
      system( "gcc -g TP4__2__1.c -o  TP4__2__1_debug.out"); //generates the debugging file
      snprintf(params, sizeof(params), "gdb TP4__2__1_debug.out %d",arg_sort); 
      system( params ); //Shows the debugger running the command line

      /*system( "gcc -c functions.c"); //Generates the executable file
      system( "gcc -o TP4__2__1.out TP4__2__1.c functions.o"); //Generates the executable file
      system( "./TP2_EX2_2.out" );  //this one has the arguments in command line
      printf("\n");   }
      */
   }
   else
   //if(debug_mode=FALSE)
   {
      /*
      system( "gcc -c functions.c"); //Generates the executable file
      system( "gcc -o TP4__2__1.out TP4__2__1.c functions.o"); //Generates the executable file
      snprintf(params, sizeof(params), "TP4__2__1.out %d",arg_sort);
      system( "./TP4__2__1.out" );  //this one has the arguments in command line
      printf("\n");*/
      
      system( "gcc TP4__2__1.c -o TP4__2__1.out"); 
      snprintf(params, sizeof(params), "TP4__2__1.out %d",arg_sort); 
      system( params);  //this one has the arguments in command line
      printf("\n");
      
   }
  
}

/* === Help Function Provided ======================================================================= */
 void help( char * nomComm )
 {
    printf("Welcome to the TP4 Help Menu\n\n");
    printf("Format of input TP4 [fctn] [args] \n");
    printf("Permited arguments: \n");
    printf("-d  debug mode (disabled by default)\n");
    printf("-h  help mode  (disabled by default)\n\n");
    printf("Functions permited in TP4:\n");
    printf("EX2_1 correspond to Excercise 2.1\n");
    printf("To run this exercise try the next commands:\n");
    printf("\n\n");
    printf("Type '1' to sort the results alphabetically by name \n");
    printf("Type '2' to sort the results by current market price\n");
    printf("Type '3' to sort the results by day change\n");
    printf("\n");
    printf("Example:\n");
    printf(">> TP4 EX2_1 1\n");

    printf("\n");
 }


