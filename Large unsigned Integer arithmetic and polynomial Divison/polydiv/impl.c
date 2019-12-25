#include "header.h"


struct node* create(int x, float y){
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->deg=x;
    newnode->co=y;
    newnode->prev=NULL;
    newnode->next=NULL;
    return newnode;
}

void clearit(struct node** head){
    struct node* p=*head;

    while(*head){
        *head=(*head)->next;
        free(p);
        p=*head;
    }
    *head=NULL;
}


int insertsort(int deg, float co, struct node** head){
    struct node* newnode=create(deg,co);
    if(*head==NULL)
        *head=newnode;
    else if((*head)->deg <= deg){
        if((*head)->deg==deg)
            (*head)->co=co;
        else{
            newnode->next=*head;
            newnode->next->prev=newnode;
            *head=newnode;
        }
    }
    else{
    struct node* p=*head;
    while(p->next!=NULL && p->next->deg > deg)
        p=p->next;

    if(p->next!=NULL && p->next->deg == deg)
        p->next->co=co;
    else{
        newnode->next=p->next;
        newnode->prev=p;
        if(p->next!=NULL)
            (p->next)->prev=newnode;
        p->next=newnode;
    }
    }
}




int insertpoly(int ch){
    int deg;
    float co;
    int i;
    if(!ch){
        int n,hpow;
        printf("\nEnter degree, non zero terms = ");
        scanf("%d %d",&hpow,&n);
	if(n>hpow+1){
		printf("\nWrong input");
		exit(0);
	}
	int hp1=hpow;
        hpow=hpow+1;
        i=hpow-1;
        while(hpow--)
            insertsort(i--,0,&head1);
        for(i=0 ; i<n ; i++){
            scanf("%d %f",&deg,&co);
		if(i==0){
			if(deg!=hp1){
				printf("\nWrong input");
				return 0;
			}
		}
            insertsort(deg,co,&head1);
        }
        print(head1);
    }
    else{
        int n1,n2,hpow1,hpow2;
        printf("\nEnter degree, non zero terms of dividend = ");
        scanf("%d %d",&hpow1,&n1);
	if(n1>hpow1+1){
		printf("\nWrong input");
		return 0;
	}
        int hp=hpow1;
        hpow1=hpow1+1;
        i=hpow1-1;
        while(hpow1--)
            insertsort(i--,0,&head1);
        for(i=0 ; i<n1 ; i++){
            scanf("%d %f",&deg,&co);
		if(i==0){
			if(deg!=hp){
				printf("\nWrong input");
				return 0;
			}
		}
            insertsort(deg,co,&head1);
        }
        print(head1);

        printf("\nEnter degree, non zero terms of divisor = ");
        scanf("%d %d",&hpow2,&n2);
	if(n2>hpow2+1){
		printf("\nWrong input");
		return 0;
	}

        if(hpow2>hp){
            printf("\nWrong input");
            return 0;
        }
	int hp2=hpow2;
        hpow2=hpow2+1;
        i=hpow2-1;
        while(hpow2--)
            insertsort(i--,0,&head2);
        for(i=0 ; i<n2 ; i++){
            scanf("%d %f",&deg,&co);
		if(i==0){
			if(deg!=hp2){
				printf("\nWrong input");
				return 0;
			}
		}
            insertsort(deg,co,&head2);
        }
        print(head2);
        divide(&head1,&head2);
	clearit(&head1);
	clearit(&head2);
    }
}





int divide(struct node** head1, struct node** head2){
    struct node* qx=NULL;
    struct node* rx=NULL;
    struct node* p1=*head1;
    struct node* x1=*head1;
    struct node* p2=*head2;

    int diff=0;
    float div=1;

    while(x1!=NULL){
        p2=*head2;
        p1=x1;

        if(p1->deg < p2->deg)
            break;
        if(p1->co && p1->deg>=p2->deg){
            diff=p1->deg-p2->deg;
            div=p1->co/p2->co;
            //printf("\n %d %f",diff,div);
            insertsort(diff,div,&qx);
            while(p2!=NULL){
                if(p1->deg == p2->deg+diff){
                    p1->co = p1->co - (p2->co)*div;
                }
                p1=p1->next;
                p2=p2->next;
            }
        }

        x1=x1->next;
    }

    while(x1 != NULL){
        insertsort(x1->deg,x1->co,&rx);
        x1=x1->next;
    }

    //print(*head1);
    printf("\nQuotient = ");
    print(qx);
    printf("\nRemainder = ");
    print(rx);
	clearit(&qx);
	clearit(&rx);

}





int print(struct node* p){
    printf("\n");
    while(p!=NULL){
        printf("(%d,%f)  ",p->deg,p->co);
        p=p->next;
    }
}
