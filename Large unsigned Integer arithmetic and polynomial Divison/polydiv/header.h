#include <stdio.h>
#include <stdlib.h>

struct node{
    int deg;
    float co;
    struct node* next;
    struct node* prev;
};

extern struct node* head1;
extern struct node* head2;


struct node* create(int x, float y);
void clearit(struct node** head);
int insertsort(int deg, float co, struct node** head);
int insertpoly(int ch);
int divide(struct node** head1, struct node** head2);
int print(struct node* p);
