#include <stdio.h>
#include <stdlib.h>
#include "header.h"


struct node* head1=NULL;
struct node* head2=NULL;
struct node* p3=NULL;


int main(){
    //check();
    int ch;
    printf("0 - Input & Output\nFor 2 poly add-2 multiply-3\nInfix Expressions-4\n");
    scanf("%d",&ch);
    
    switch(ch){
        case 0:
            input(0);
            break;
        case 2:
            input(2);
            break;
        case 3:
            input(3);
            break;
        case 4:
            break;
        default :
            printf("Wrong option");
            exit(0);
    }

    if(ch!=4)
        exit(0);
    else{
        int cho=1;
        while(cho){
            printf("\nEnter Expression : \n");

            clearit(&head1);
            clearit(&head2);
            clearit(&p3);
            head1=NULL;
            head2=NULL;
            p3=NULL;

            char ch;
            char op='A';
            int n,dig1,dig2;
            int res=1;
            dig1=0;
            ch='A';
            while(ch!='$'){
                scanf("%d",&n);
                if(n>9999 || n<0){
                    printf("Wrong input");
                    exit(0);
                }
                insert(n,&head1);
                dig1++;
                scanf("%c",&ch);
                if(!(ch==',' || ch=='$')){
                    printf("\nWrong input");
                    exit(0);
                }
            }

            

            while(op!='='){

                scanf("%c",&op);
                if(op=='=')
                    break;
                else if(!(op=='+' || op=='*' )){
                    printf("\nWrong input");
                    res=0;
                    break;
                }

                clearit(&head2);
                head2=NULL;
                dig2=0;
                ch='A';
                while(ch!='$'){

                    scanf("%d",&n);
                    if(n>9999 || n<0){
                        printf("Wrong input");
                        exit(0);
                    }
                    insert(n,&head2);
                    dig2++;
                    scanf("%c",&ch);
                    if(!(ch==',' || ch=='$')){
                        printf("\nWrong input");
                        exit(0);
                    }
                }

                
                if(op=='+'){
                    dig1=count(head1);
                    struct node* temp=NULL;
                    
                    if(dig1<dig2){
                        temp=head2;
                        head2=head1;
                        head1=temp;
                    }
                    int cr=add(head1,head2);
                    rev(&head1);
                    if(cr)
                        insert(cr,&head1);
                    rev(&head1);
                }
                else if(op=='*'){
                    dig1=count(head1);                    
                    
		    p3=NULL;
                    int mul=multiply(head1,head2,dig1+dig2);
		    
                    clearit(&head1);
                    head1=NULL;
		     		    
                    rev(&p3);		              
		    
		    head1=p3;
		    
		    p3=NULL;
                    
                }
            }
            if(res){
                rev(&head1);
                print(head1);
            }

            printf("\nCompute again yes-1 no-0 ");
            scanf("%d",&cho);
        }
    }
}


