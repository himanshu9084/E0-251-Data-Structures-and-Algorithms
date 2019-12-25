#include <stdlib.h>
#include <stdio.h>

struct node{
    int v;
    struct node* next;
};

struct list{
    struct node* head;
};

struct adjl{
    int vadd;
    struct list* varr;
};


struct q{
    int front;
    int rear;
};

extern struct adjl* gp;
extern int** mat;
extern int** path;
extern float* bc;
extern FILE *fptr;
int* que;
int* vd;
int n;

struct node* crnode(int);
struct adjl* create(int);
void addv(struct adjl* gp,int v1, int v2);
void printlist(struct adjl* gp);
void deladj(struct adjl** gph);
void matrixgen(int n,int type);
void matprint(int** p,int n);
void matdel(int n);
void initfloyd(int n);
void floyd(int n);
void initbfs(int n);
void initb();
struct q* createq();
int empty(struct q* q);
void enq(struct q* q, int val);
int deq(struct q* q);
void bfs(int vert);
