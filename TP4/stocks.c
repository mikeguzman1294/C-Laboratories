#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME_LENGTH 200


//Stock Information Structure 
struct stockInformation
{
	char stock_name[MAX_NAME_LENGTH];
	float currentPrice;
	float dayChange;
};

typedef struct stockInformation stockInformationStructure;


/***** Functions Declarations ***********************************/

//Sorts the information by Stock Name
int stockNameSort(const void *a, const void *b);

//Sorts the information by Stock Price
int stockPriceSort(const void *a, const void *b);

//Sorts the information by Stock Price
int stockDaySort(const void *a, const void *b);




/*************************  Functions ***************************/

void main(int argc, char *argv[])
{
	if(argc==1)
	{
		printf("Please choose the sort selection of the stocks\n");
		printf("Type '1' to sort alphabetically \n");
		printf("Type '2' to sort by current market price\n");
		printf("Type '3' to sort by day change\n");
		
	}
	else
	{
	
		FILE *stockFile; 
		FILE *stock_analysis;
		char *stockFile_content;
		
		
		int file_size;
		int i;
		int stockNo=0;
		
		size_t structs_len = stockNo;
		float price;
		
		char *temp_keyFound;
		char *foundKeyCopy=NULL;
		char *stockName;
		stockInformationStructure stockInfo[200];
		char *begin;
		char *end;
		char *tok;

		const char *name_bpattern = "View equity details for ";
	    	const char *name_epattern = "\"";
	    	
	    	char *price_Id="ls-mid-";
	    	const char *price_bpattern = "\">";
	    	const char *price_epattern = "</span>";
	    	
	    	char *day_Id="ls-change-";
		const char *day_bpattern = "\">";
	    	const char *day_epattern = "</span>";
	    	
		
		//Retrieve information from www.hl.co.uk webpage and save it in Stocks_Information.txt file to use it later
		system("wget --quiet --output-document=Stocks_Information.txt \"https://www.hl.co.uk/shares/stock-market-summary/ftse-100\"");
		//system("wget");
		stockFile= fopen("Stocks_Information.txt", "r");
		
		//Verify the file is not empty to start processing the information
		if(stockFile != NULL)
		{	
		
			//Receive the full arguments and save them in memory 
			fseek(stockFile, 0, SEEK_END);
			file_size = ftell(stockFile);
			fseek(stockFile,0, SEEK_SET);
			
			stockFile_content=(char*)malloc(sizeof(char)*file_size); //reserve the size of the file in memory 
			fread(stockFile_content, sizeof(char), file_size, stockFile); //take the content of the html to the memory space
			
			fclose(stockFile);
			
			while(1)
						{
			
				//Search for the Stock Name by looking for the bpattern(begin) and epattern(end) 
				if ( begin = strstr( stockFile_content, name_bpattern ) )
				{
					begin += strlen( name_bpattern );
					if ( end = strstr( begin, name_epattern ) )
					{
					    foundKeyCopy = (char *)malloc( end - begin + 1 );
					    memcpy( foundKeyCopy, begin, end - begin );
					    foundKeyCopy[end - begin] = '\0';
					}
				}
				else
				{
					break; //Quit the loop if already found the n
				}
			
				strcpy(stockInfo[stockNo].stock_name,foundKeyCopy); 

		    		free( foundKeyCopy );
		    		
		    		//Save the unread text as the new stockFile_content
		    		stockFile_content=NULL;
		    		stockFile_content=end;
		    		
		    		begin=NULL;
		    		end=NULL;
		    		temp_keyFound=NULL;
		    		
		    		temp_keyFound=strstr(stockFile_content,price_Id);
				
				//Look for the Stock price by looking for the bpattern(begin) and epattern(end) and save it in stockInfo[stockN] structure. Break the while loop in case no name is found
				if ( begin = strstr( temp_keyFound, price_bpattern ) )
				{
					begin += strlen( price_bpattern );
					if ( end = strstr( begin, price_epattern ) )
					{
					    foundKeyCopy = ( char * )malloc( end - begin + 1 );
					    memcpy( foundKeyCopy, begin, end - begin );
					    foundKeyCopy[end - begin] = '\0';
					}
				}
				
				// Convert the price string to a float number separating the numbers before ',' and adding them with the numbers after that character
				if(strchr(foundKeyCopy, ',') != NULL)
				{
					tok=strtok(foundKeyCopy, ",");
		  			price = atof(tok)*1000;
		  		
		  			tok=strtok(NULL, ",");
		  			price = price + atof(tok);
				}
				else
				{
					price=atof(foundKeyCopy);
				}
				
				stockInfo[stockNo].currentPrice=price;
		    

		    		free( foundKeyCopy );
		    		
		    		stockFile_content=NULL;
		    		stockFile_content=end;
		    		
		    		
		    		
		    		begin=NULL;
		    		end=NULL;
		    		temp_keyFound=NULL;
		    		
		    		//Look for the Stock Day by looking for the bpattern(begin) and epattern(end) and save it in stockInfo[stockN] structure. Break the while loop in case no name is found
		    		temp_keyFound=strstr(stockFile_content,day_Id);
				
				if ( begin = strstr( temp_keyFound, day_bpattern ) )
				{
					begin += strlen( day_bpattern );
					if ( end = strstr( begin, day_epattern ) )
					{
					    foundKeyCopy = ( char * )malloc( end - begin + 1 );
					    memcpy( foundKeyCopy, begin, end - begin );
					    foundKeyCopy[end - begin] = '\0';
					}
				}
				
				stockInfo[stockNo].dayChange=atof(foundKeyCopy);

		    		free( foundKeyCopy );  
		    		
		    		stockFile_content=NULL;
		    		stockFile_content=end;  
		    		stockNo=stockNo+1;		
			}

			//Using comparison function sort the information by Stock name (1)
			if(strcmp(argv[1], "1") == 0){  
			 	qsort(stockInfo, structs_len, sizeof(stockInformationStructure), stockNameSort); 
			 	stock_analysis=fopen("NameOrderedStock.txt", "w");
			}
			
			//Using comparison function sort the information by Stock Price (2)
			else if(strcmp(argv[1], "2") == 0){
				qsort(stockInfo, structs_len, sizeof(stockInformationStructure), stockPriceSort);
				stock_analysis=fopen("PriceOrderedStock.txt", "w");
			}
			
			//Using comparison function sort the information by Stock Day (3)
			else if(strcmp(argv[1], "3") == 0){
				qsort(stockInfo, structs_len, sizeof(stockInformationStructure), stockDaySort);
				stock_analysis=fopen("DayOrderedStock.txt", "w");
			}
			else
			{
				//Do nothing
			}
			
			fprintf(stock_analysis,"_____________________________________________________________________\n\nStocks Information\n\n_____________________________________________________________________\n\n");
			fprintf(stock_analysis, "We retrieve %i. results \n\n", stockNo);
			
			for(int i=0; i< stockNo; i++)
			{
				fprintf(stock_analysis,"stock ID: #%i\n", i+1);
				fprintf(stock_analysis,"Stock Name: %s\n", stockInfo[i].stock_name);
				fprintf(stock_analysis,"Stock Current Price: %.2f\n",stockInfo[i].currentPrice);
				fprintf(stock_analysis,"Stock Day Change: %.2f\n\n", stockInfo[i].dayChange);
			}
		}
	}
}


//Using comparison function sort the information by Stock name (1)

int stockNameSort(const void *a, const void *b) 
{ 
    stockInformationStructure *ia = (stockInformationStructure *)a;
    stockInformationStructure *ib = (stockInformationStructure *)b;
    return strcmp(ia->stock_name, ib->stock_name);
    
} 


//Using comparison function sort the information by Stock Price (2)
int stockPriceSort(const void *a, const void *b) 
{ 
    stockInformationStructure *ia = (stockInformationStructure *)a;
    stockInformationStructure *ib = (stockInformationStructure *)b;
    return (int)(ia->currentPrice - ib->currentPrice);

}

//Using comparison function sort the information by Stock Day (3)
int stockDaySort(const void *a, const void *b) 
{ 
    stockInformationStructure *ia = (stockInformationStructure *)a;
    stockInformationStructure *ib = (stockInformationStructure *)b;
    return (int)(ia->dayChange - ib->dayChange);

}
