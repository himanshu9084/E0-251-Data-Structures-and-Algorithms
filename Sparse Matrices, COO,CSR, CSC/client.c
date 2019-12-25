#include <stdio.h>
#include "header.h"




int main(){
	printf(" For CSC * CSR , press 1 otherwise 0..");
    int ch=0;
    scanf("%d",&ch);

    if(ch)
        generate2();
    else
        coogenerate();
	
	return 0;

}
