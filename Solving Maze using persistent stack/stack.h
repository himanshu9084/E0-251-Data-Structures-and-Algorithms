#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define allocate(x) (x*)malloc(sizeof(x))
#define print(x) printf(x);
int **mat;
int n;
unsigned long ch;

struct modt{
    struct modf* head;
};
typedef struct modt modt;

struct modf{
    int type;
    int no;
    struct modf* pr;
    struct modf* mc[4];
};
typedef struct modf modf;



//Matrix generation and print
void matgen(int n){
  mat=malloc(n*sizeof(int*));
  int i,j;

  for(i=0 ;i<n ;i++){
    mat[i]=malloc(n*sizeof(int));
    j=n;
    while(j--)
      mat[i][j]=0;
  }
}

void matprint(){
  int i,j;
  for(i=0 ; i<n ; i++){
    for(j=0 ; j<n ; j++){
      printf("%d ",mat[i][j]);
    }
    printf("\n");
  }
}

//Count digits
int digc(int x){
  int c=0;
  while(x!=0){
    x/=10;
    ++c;
  }
  return c;
}


//Maze generation algo
//Swapping or not two char pointers
void swap(char *a,char *b){
  char temp=*a;
  *a=*b;
  *b=temp;
}

_Bool toswap(char *str, int f, int l){
  int i;
  for(i=f ; i<l ; i++)
    if(str[i]==str[l])
      return 0;
  return 1;
}

//Permuting the single maze solving case
//string to number
void strtonum(char *str){
  int len=strlen(str);
  int i,num=0,k=0;
  for(i=len-1 ; i>=0 ; i--){
    if(str[i]=='R')
      num+=(1<<k);
    k++;
  }
  printf("\n%s %d",str,num);
  //printf(" %c",str[len-1]);
}

//Converting string to path of maze
void strtomat(char *str){
  //printf("\n%s\n",str);
  int len=strlen(str);
  int i,j;
  int ind=0;
  mat[ind/n][ind%n]=1;

  for(i=0 ; i<len ; i++){
    if(str[i]=='R')
      ind+=1;
    if(str[i]=='D')
      ind+=n;
    mat[ind/n][ind%n]=1;
  }
  //printf(" %c",str[len-1]);
}

//Permuting the string
unsigned long co;
void permut(char *str, int f, int l){
  int i,j;
  int n=strlen(str);
  //printf("\n%ld\n",strlen(str));

  int R=n/2;
  int D=n/2;
  int k=0;
  int x=0,y=0;

  for(i=0 ; i<n ; i++){
    mat[x][y]=1;
    if(D==0 || R==0)
      break;
    k=rand()%2;
    if(k==0){
      D--;
      x+=1;
    }
    else{
      R--;
      y+=1;
    }
  }

  while(R--){
    y+=1;
    mat[x][y]=1;
  }

  while(D--){
    x+=1;
    mat[x][y]=1;
  }
  /*if(f>=l){
    //printf("\n%s",str);
    co++;
    if(co==ch)
      strtomat(str);
    return;
  }
  else if(co==ch){
    return;
  }
  else{
    for(i=f ; i<l ; i++){
      if(toswap(str,f,i)){
        swap((str+f),(str+i));
        permut(str,f+1,l);
        swap((str+f),(str+i));
      }
    }
  }*/
}

//NO of total permutations
int totper(int tot){
  int n=tot;
  int n2=tot/2;
  long double i,j;
  j=1;
  long double num=1,den=1;
  while(j<=n2){
    den*=j;
    j++;
  }
  i=n;
  while(i>n2){
    num*=i;
    i--;
  }
  return num/den;
}

//Maze generator
void mazegen(){
  unsigned long tot=2*n-2;

  int i,j;
  char str[tot];

  for(i=0 ; i<tot/2 ; i++){
    str[i]='R';
    str[tot-i-1]='D';
  }
  str[tot]='\0';
  //str[tot]='\0';
  //printf("%s",str);
  //ch=0;
  matgen(n);

  srand(time(0));

  for(i=0 ; i<n ; i++)
    for(j=0 ; j<n ; j++){
      mat[i][j]=rand()%2;
    }

  //matprint();
  ch=rand()%7;

  //printf(" %d",ch);
  if(ch)
    permut(str,0,tot);
  else
    strtomat(str);

  if(n<20)
    matprint();

}




//MAze Solver algo
//fully persistent stack
void fsinit(modt* p){
    p->head=NULL;
}

void sfpoint4(modf* p){
    p->mc[0]=NULL;
    p->mc[1]=NULL;
    p->mc[2]=NULL;
    p->mc[3]=NULL;
    //printf("hi");
}

//push first (0,0)
void fsfirst(modt* p){
    modf* t=allocate(modf);
    if(p->head==NULL){
        p->head=t;
        t->type=mat[0][0];
        t->pr=NULL;
        t->no=0;
        sfpoint4(t);
    }
}


//Checking index and value in matrix
int isindex(int x){
  if(x>=n*n || x<0)
    return 0;
  return 1;
}

int indch(int ind){
  int x=ind/n;
  int y=ind%n;

  if(mat[x][y]==0 || mat[x][y]==-1)
    return 0;
  return 1;
}

//Checking R,D,U,L for a position
int rdul(modf* p){
  int ind=p->no;
  int R=ind+1;
    if(isindex(R) && indch(R))
      return R;

  int D=ind+n;
  if(isindex(D) && indch(D))
    return D;

  int U=ind-n;
  if(isindex(U) && indch(U))
    return U;

  int L=ind-1;
  if(isindex(L) && indch(L))
    return L;

  return ind*n;
}

//int k;
modf* fsroam(modf* p){
    if(p==NULL)
      return NULL;

    int ind=p->no;
    //printf("\nind= %d mat= %d",ind,mat[ind/n][ind%n]);

    /*k++;
    if(k==40)
      exit(0);*/

    if(ind==n*n-1)
      return p;

    int nxind=rdul(p);
    modf* t=NULL;

    if(p->pr)
      if(nxind==p->pr->no){
        mat[ind/n][ind%n]=-1;
        return fsroam(p->pr);
      }
    //print(" Hi");
    if(nxind==ind*n){
      //printf("found ind %d ",ind);
      mat[ind/n][ind%n]=-1;
      t=p->pr;
    }
    else{
      t=allocate(modf);
      t->type=1;
      t->no=nxind;
      t->pr=p;
      sfpoint4(t);

      if(p->mc[0]==NULL)
          p->mc[0]=t;
      else if(p->mc[1]==NULL)
          p->mc[1]=t;
      else if(p->mc[2]==NULL)
          p->mc[2]=t;
      else if(p->mc[3]==NULL)
          p->mc[3]=t;

      //printf("\nnxind= %d mat= %d\n",nxind,mat[nxind/n][nxind%n]);
    }
    return fsroam(t);
}

//Printing succesful path traversed
char pathdir(int d){
  if(d==0)
    return 0;
  if(d==-1)
    return 'R';
  if(d==-n)
    return 'D';
  if(d==1)
    return 'L';
  if(d==n)
    return 'U';

}

void printpath(modf* p){
  int d=0;
  if(p)
    if(p->pr){
      d=p->pr->no-p->no;
      printpath(p->pr);
    }
  //printf("\nind = %d %c",p->no,pathdir(d));
  printf("%c",pathdir(d));
}

//Maze solver function
void fspush(modt* p){
    modf* t=p->head;
    modf* x=fsroam(t);
    if(x->no==n*n-1){
      printf("\nSuccessful result = %d End reached",x->no);
      printf("\nPAth traversed : \n");
      printpath(x);

      //printf("\nWant to see matrix traversal\n");
    }
}


//For deallocating whole memory used
void dealloc(modf* p){
    if(p==NULL)
        return;
    dealloc(p->mc[0]);
    dealloc(p->mc[1]);
    dealloc(p->mc[2]);
    dealloc(p->mc[3]);
    free(p);
}

void sdealloc(modt* p){
  if(p!=NULL){
    modf* t=p->head;
    dealloc(t);
  }

  int i;
  for(i=0 ; i<n ; i++){
    free(mat[i]);
  }
  free(mat);
}











#endif
