#include <stdio.h>
#include <stdlib.h>


struct node{
    int val;
    struct node* next;
};


extern struct node* head1;
extern struct node* head2;
extern struct node* p3;



void clearit(struct node** head);
void rev(struct node** head);
struct node* create(int x);
int count(struct node* head);
int insert(int val, struct node** head);
int input(int mode);
int add(struct node* head1, struct node* head2);
int multiply(struct node* head1, struct node* head2, int digt);
int print(struct node* p);
