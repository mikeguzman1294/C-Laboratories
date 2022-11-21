#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 200
struct stockInformation
{
	char stock_name[MAX_NAME_LENGTH];
	float currentPrice;
	float dayChange;
};


typedef struct stockInformation stockInformationStructure;

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
