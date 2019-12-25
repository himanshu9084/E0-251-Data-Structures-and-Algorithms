#include<stdio.h>
#include<stdlib.h>


void enq(int);
int deq();
int iconnect(int n);
void BFS(int vert,int n, int pt);
void listconnect(int n);
void merge(int low, int mid, int high);
void mergesort(int low, int high);
int search(int *A,int key,int n);

struct node
{
    int v;
    struct node *next;
};

typedef struct node Node;
typedef struct node *Nodeptr;

Nodeptr front = NULL;
Nodeptr rear = NULL;
char *visited;
int *cot;
char **gp;
int *A,*B;

int count = 0,k=0;
int main()
{
    int n,v1,v2;
    int i,j;
    n=100;

    gp = malloc(n*sizeof(char *));
    visited = malloc(n*sizeof(char));
    cot = malloc(n*sizeof(int));

    for(i = 0;i < n;++i)
    {
        gp[i] = malloc(n*sizeof(int));
        visited[i] = 'N';
        cot[i]=0;
        for(j = 0;j < n;++j)
            gp[i][j] = 0;
    }

    FILE *fptr=fopen("files/nc/100_nc_nodes.txt","r");
    if(fptr==NULL){
        printf("\nFile not available \n");
        exit(0);
    }

    while(fscanf(fptr,"%d%d",&v1,&v2)!=EOF){
        gp[v1][v2]=1;
        gp[v2][v1]=1;
    }
    fclose(fptr);


    /*//for(i = 0;i < n;++i){
    i=58;
      printf("\n");
      for(j=0 ; j<n ; j++){
        printf("%d ",gp[i][j]);
      }
    //}
    if(iconnect(gp,n))
        printf("graph is connected");
    else printf("graph is NOT connected\n");*/

    listconnect(n);
    if(count==1){
      printf("Graph is connected ");
    }
    else{

    int max=0,largest=0;
    for(j=0 ; j<n ; j++){
      visited[j]='N';
      if(max<cot[j]){
        max=cot[j];
        largest=j;
      }
    }

    //printf("\n\n%d %d",max,largest);
    fptr=fopen("files/nc/100_nc_nodes_red.txt","w+");
    if(fptr==NULL){
        printf("\nFile not created ");
        exit(0);
    }

    //fprintf(fptr,"%d %d\n",n,max);

    A=malloc(max*sizeof(int));
    B=malloc(max*sizeof(int));

    BFS(largest,n,1);
    mergesort(0,max);


      //printf("%d  ",A[0]);
        //printf("%d  ",A[1]);

    int sr;
    for(i=0 ; i<max ; i++){
      //printf("%d  ",A[i]);
      for(j=0 ; j<n ; j++){
        if(gp[A[i]][j]){
          gp[j][A[i]]=0;
          sr=search(A,j,n);
          fprintf(fptr,"%d %d\n",sr,i);
        }
      }
    }

    fclose(fptr);

    fptr=fopen("files/nc/100_nc_nodes_cinfo.txt","w+");

    if(fptr==NULL){
        printf("\nFile not created ");
        exit(0);
    }
    fprintf(fptr,"%d\n",n);
    fprintf(fptr,"%d\n",max);
    for(i=0 ; i<max ; i++){
      fprintf(fptr,"%d\n",A[i]);
    }
    fclose(fptr);
  }

    for(i = 0;i < n;++i){
        free(gp[i]);
    }
    free(A);
    free(B);
    free(visited);
    free(cot);
}


int search(int *A,int key,int n){
  int i;
  for(i=0 ; i<n ; i++){
    if(A[i]==key){
      return i;
    }
  }
  return -1;
}

void merge(int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(A[l1] <= A[l2])
         B[i] = A[l1++];
      else
         B[i] = A[l2++];
   }

   while(l1 <= mid)
      B[i++] = A[l1++];

   while(l2 <= high)
      B[i++] = A[l2++];

   for(i = low; i <= high; i++)
      A[i] = B[i];
}





void mergesort(int low, int high) {
   int mid;

   if(low < high) {
      mid = (low + high) / 2;
      mergesort(low, mid);
      mergesort(mid+1, high);
      merge(low, mid, high);
   } else {
      return;
   }
}




void enq(int vert)
{
    if(front == NULL)
    {
        front = malloc(sizeof(Node));
        front->v = vert;
        front->next = NULL;
        rear = front;
    }
    else
    {
        Nodeptr newNode = malloc(sizeof(Node));
        newNode->v = vert;
        newNode->next = NULL;
        rear->next = newNode;
        rear = newNode;
    }
}



int deq()
{
    if(front == NULL)
    {
        //printf("Q is empty \n");
        return -1;
    }
    else
    {
        int v = front->v;
        Nodeptr temp= front;
        if(front == rear)
        {
            front = front->next;
            rear = NULL;
        }
        else
            front = front->next;

        free(temp);
        return v;
    }
}



int iconnect(int n)
{
    int i;
    BFS(0,n,0);

    for(i = 0;i < n;++i)
        if(visited[i] == 'N')
         return 0;

    return 1;
}



void BFS(int v,int n,int pt)
{
    //printf("\nConnected component %d\n",++count);
    ++count;
    int i,vert,co=0;
    visited[v] = 'Y';
    enq(v);
    while((vert = deq()) != -1)
    {
        if(pt){
          //printf("%d k=%d  A[k]=%d ",vert,k,A[k]);
          A[k++]=vert;
        }

        for(i = 0;i < n;++i)
            if(gp[vert][i] == 1 && visited[i] == 'N' && i!=v)
            {
              /*if(pt){
                A[k++]=i;
                //printf("%d k=%d  \n",i,k);
                //k++;
              }*/
                enq(i);
                visited[i] = 'Y';
                co++;
            }
    }
    ++co;
    cot[v]=co;
    //printf("\nno of connects %d\n",co);
}

void listconnect(int n)
{
    int i;
    for(i = 0;i < n;i++)
    {
        if(visited[i] == 'N')
            BFS(i,n,0);
    }
}
