#include "header.h"
#include <stdio.h>
#include <stdlib.h>


void clearit(struct node** head){
    struct node* p=*head;
    struct node* p1=*head;
    while(p1){
        p1=p1->next;
        free(p);
        p=p1;
    }
    p1=NULL;

    head=NULL;
}





void rev(struct node** head){
    struct node* r=NULL;
    struct node* p=*head;
    struct node* q=NULL;
    while(p!=NULL){
        r=p->next;
        p->next=q;
        q=p;
        p=r;
    }
    *head=q;
}




struct node* create(int x){
    struct node* newnode=(struct node*)malloc(sizeof(struct node));

    newnode->val=x;
    newnode->next=NULL;
    return newnode;
}




int count(struct node* head){
    int count=0;
    while(head){
        count++;
        head=head->next;
    }
    return count;
}




int insert(int val, struct node** head){
    struct node* newnode=create(val);
    if(*head==NULL)
        *head=newnode;
    else{
        newnode->next=*head;
        *head=newnode;
    }
}




int input(int mode){
    if(!mode){
        int dig=0;
        printf("Enter the no = ");
        char ch='A';
        int n;
        while(ch!='$'){
            scanf("%d",&n);
            if(n>9999 || n<0){
                printf("Wrong input");
                return 0;
            }
            insert(n,&head1);
            dig++;
            scanf("%c",&ch);
        }
	rev(&head1);
        print(head1);
        clearit(&head1);
    }
    else{
        int dig1=0;
        printf("Enter the first no = ");
        char ch='A';
        int n;
        while(ch!='$'){
            scanf("%d",&n);
            if(n>9999 || n<0){
                printf("Wrong input");
                return 0;
            }
            insert(n,&head1);
            dig1++;
            scanf("%c",&ch);
        }

        int dig2=0;
        printf("Enter the second no = ");
        ch='A';
        while(ch!='$'){
            scanf("%d",&n);
            if(n>9999 || n<0){
                printf("Wrong input");
                return 0;
            }
            insert(n,&head2);
            dig2++;
            scanf("%c",&ch);
        }


        if(mode==2){
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
            print(head1);
            clearit(&head1);
            clearit(&head2);
        }

        if(mode==3){
            multiply(head1,head2,dig1+dig2);
            print(p3);
            clearit(&head1);
            clearit(&head2);
            clearit(&p3);
        }

    }
}


int add(struct node* head1, struct node* head2){
    struct node* p1;
    struct node* p2;
    p1=head1;
    p2=head2;

    int sum=0;
    int cr=0;

    while(p1!=NULL && p2!=NULL){
        sum=p1->val+p2->val+cr;
        p1->val=sum%10000;
        cr=sum/10000;
        p1=p1->next;
        p2=p2->next;
    }
    struct node* p3;
    p3=p1;

    while(p3!=NULL){
        sum=p3->val+cr;
        p3->val=(sum%10000);
        cr=sum/10000;
        p3=p3->next;
    }
    return cr;

}




int multiply(struct node* head1, struct node* head2, int digt){

    p3=NULL;

    struct node* p1=head1;
    struct node* p2=head2;

    struct node* p4=NULL;

    //print(p1);
    //print(p2);
    //struct node* p4=NULL;


    int mul=0,count=0,i=0;
    int cr=0;

    while(p1!=NULL){
            mul=p1->val*p2->val+cr;
            insert(mul%10000,&p3);
            cr=mul/10000;
            p1=p1->next;
            i++;
    }
    insert(cr,&p3);
    i++;
    while(i<digt){
        insert(0,&p3);
        i++;
    }
    //print(p3);

    p2=p2->next;
    count++;

    cr=0;
    while(p2!=NULL){
        clearit(&p4);
        p4=NULL;
        i=0;
        while(i<count){
            insert(0,&p4);
            i++;
        }

        p1=head1;
	mul=0;
        while(p1!=NULL){
            mul=p1->val*p2->val+cr;
            //printf("\n%d",mul%10000);
            insert(mul%10000,&p4);
            cr=mul/10000;
            p1=p1->next;
            i++;
        }
        insert(cr,&p4);
        i++;
        cr=0;
        while(i<digt){
            insert(0,&p4);
            i++;
        }

	//print(p4);

        rev(&p3);
        rev(&p4);
        int ad=add(p3,p4);
        rev(&p3);


	//print(p3);

        p2=p2->next;
        count++;
    }
    //print(p3);
    //rev(&p3);
	return 0;
}




int print(struct node* p){
    printf("\n");
    while(p->next != NULL){
        printf("%d,",p->val);
        p=p->next;
    }
    printf("%d$",p->val);
}
