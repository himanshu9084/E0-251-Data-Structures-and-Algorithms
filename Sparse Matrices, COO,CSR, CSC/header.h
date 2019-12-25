#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct node{
        int pos;
        int data;
        struct node* next;
};


void push(struct node** start, int npos, int ndata);
int coogenerate();
int input(int m, int n,int rows[], int col[], int data[], int nzdennum,int negdennum );
int cootocsr(int m, int n, int rows[],int size, int rcsr[]);
int cootocsc(int m, int n, int row1[],int col1[], int data1[],int size, int ccsc[]);
int sort(int rows[], int len, int st, int data[]);
int generate2();
int multiply(int m1, int n1, int m2, int n2, int row1[], int ccsc1[], int data1[], int size1, int rcsr2[], int col2[], int data2[], int size2);
int csctrans(int m, int n, int row[], int ccsc[], int data[], int size);
int printmatrix(int m, int n, int rows[], int col[], int data[], int size, int type);
