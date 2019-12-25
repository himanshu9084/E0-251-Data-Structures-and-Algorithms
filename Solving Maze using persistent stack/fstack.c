#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void matsolve();
void maze();

FILE *fptr;

int main(){
  int c;
  print("MAze generate : 0\nMAze Solve : 2\n");
  scanf("%d",&c);

  if(c==0)
    maze();
  else
    matsolve();
  printf("\n");
  return 0;
}

void maze(){
  printf("\nMAze generation nxn : Enter n ");
  scanf("%d",&n);
  int dig=digc(n);

  mazegen();

  char buf[16];
  sprintf(buf,"maze/gm%dx",n);
  int len=strlen(buf);
  sprintf(buf+len,"%d",n);
  sprintf(buf+len+dig,"%s",".txt");
  buf[len+dig+4]='\0';

  printf("\n%s",buf);

  fptr=fopen(buf,"w");
  if(fptr==NULL){
    printf("File not created");
    exit(0);
  }
  fprintf(fptr,"%d\n",n);

  int i,j;

  for(i=0 ; i<n ; i++)
    for(j=0 ; j<n ; j++){
      if(mat[i][j])
        fprintf(fptr,"%d %d\n",i,j);
    }
  fclose(fptr);
  sdealloc(NULL);
}


void matsolve(){
  fptr=NULL;
  char fname[30];
  print("\nEnter filename as maze/\n");
  scanf("%s",fname);

  fptr=fopen(fname,"r");
  if(fptr==NULL){
    printf("File not found");
    exit(0);
  }

  fscanf(fptr,"%d",&n);
  //printf("\nMAze of %dx%d\n",n,n);

  matgen(n);

  int v1,v2;
  while(fscanf(fptr,"%d%d",&v1,&v2)!=EOF){
        mat[v1][v2]=1;
  }
  fclose(fptr);

  if(n<=20)
    matprint();
  

  modt st;
  fsinit(&st);
  fsfirst(&st);

  //matprint();
  fspush(&st);
  printf("\n");
  sdealloc(&st);
}
