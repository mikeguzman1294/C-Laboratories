#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	system("wget --quiet --output-document=Stocks_Information.txt \"https://www.hl.co.uk/shares/stock-market-summary/ftse-100\"");
    return 0;
}