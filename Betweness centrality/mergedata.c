#include<stdio.h>
#include<stdlib.h>

int main(){
  int n;
  int tot;
  FILE *fptr=fopen("files/nc/10000_nc_nodes_cinfo.txt","r");
  if(fptr==NULL){
      printf("\nFile not available \n");
      exit(0);
  }
  fscanf(fptr,"%d%d",&tot,&n);

  FILE *fp=fopen("files/nc/10000_nc_nodes_red_bfs.txt","r");
  if(fptr==NULL){
      printf("\nFile not available \n");
      exit(0);
  }

  float A[n];
  int i=0;
  float v2;
  int v1,v3;
  while(fscanf(fp,"%d %f",&v1,&v2)!=EOF){
    A[i]=v2;
    i++;
  }
  fclose(fp);

  fp=fopen("files/nc/10000_nc_nodes_red_floyd.txt","w+");
  if(fptr==NULL){
      printf("\nFile not available \n");
      exit(0);
  }

  /*for(i=0 ;i<n ; i++){
    printf("%f ",A[i]);
  }*/

  i=0;
  while(fscanf(fptr,"%d",&v1)!=EOF){
    fprintf(fp,"%d %f\n",v1,A[i]);
    i++;
  }

  fclose(fp);
  fclose(fptr);
  return 0;
}
