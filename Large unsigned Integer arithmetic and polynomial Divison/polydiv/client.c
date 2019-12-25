#include <stdio.h>
#include "header.h"

struct node* head1=NULL;
struct node* head2=NULL;


int main(){
    int ch;
    printf("Press 1 for poly div, else 0..");
    scanf("%d",&ch);
    if(!ch){
        insertpoly(0);
    }
    else{
        while(1){
        insertpoly(1);
        printf("\nRun polydiv again 1..0 for No");
        scanf("%d",&ch);
        if(!ch)
            break;
        }
    }
    //printf("Enter the polynomial\n");

    //check();
	return 0;
}
