#include "header.h"
#include <stdio.h>
#include <time.h>

struct adjl* gp=NULL;
int** mat=NULL;
int** path=NULL;
float* bc=NULL;
FILE *fptr=NULL;

//int n;
int main(){
    int i;
	printf("Floyd -1 bfs -2  ");
	scanf("%d",&i);
    	n=328;

    	clock_t t;
	t=clock();
	if(i==1)
		initfloyd(n);
	else if(i==2)
    		initbfs(n);
	t=clock()-t;
	double tot = ((double)t)/CLOCKS_PER_SEC;
	//printf("%f",tot);

	fptr=fopen("plot_time.txt","a");

  	if(fptr==NULL){
        	printf("\nFile not created ");
        	exit(0);
  	}
	fprintf(fptr,"%d %f %d\n",i,tot,n);
	fclose(fptr);

    return 0;
}
