#include "header.h"

struct node* crnode(int v){
    struct node* newnode = (struct node*)malloc(sizeof(struct node*));
    newnode->v=v;
    newnode->next=NULL;
    return newnode;
}

struct adjl* create(int vert){
    struct adjl* gp =  (struct adjl*)malloc(sizeof(struct adjl));
    gp->vadd = vert;
    gp->varr = (struct list*)malloc(vert*sizeof(struct list));

    int i;
    for(i=0 ; i<vert ; i++){
        gp->varr[i].head=NULL;
    }
    return gp;
}

void addv(struct adjl* gp,int v1, int v2){
    struct node* newnode = crnode(v2);
    newnode->next = gp->varr[v1].head;
    gp->varr[v1].head=newnode;

    newnode=crnode(v1);
    newnode->next=gp->varr[v2].head;
    gp->varr[v2].head=newnode;
}




void printlist(struct adjl* gp){
    int i;
    struct node* p;
    printf("\nAdjacency list : \n");
    for(i=0 ; i<gp->vadd ; i++){
        p=gp->varr[i].head;
        printf("\n%d :",i);
        while(p){
            printf(" -> %d",p->v);
            p=p->next;
        }
    }
}




void deladj(struct adjl** gph){
    int i;
    struct adjl* gp=*gph;
    struct node* p;
    struct node* temp;
    //printf("\nDeleting whole list");
    for(i=0 ; i<gp->vadd ; i++){
        p=gp->varr[i].head;

        while(p){
            temp=p->next;
            free(p);
            p=temp;
        }
        gp->varr[i].head=NULL;
    }
    free(gp);
    gp=NULL;
}




void matrixgen(int n,int type){
    mat=malloc(n*sizeof(int*));
    path=malloc(n*sizeof(int*));
    int i,j;
    int k=(n*(n-1))/2+1;
    if(type==1)
    for(i=0 ; i<n ; i++){
        j=n;
        mat[i]=malloc(n*sizeof(int));
        path[i]=malloc(n*sizeof(int));

        while(j--){
            if(i==j)
                mat[i][j]=0;
            else
                mat[i][j]=k;
            path[i][j]=0;
        }
    }
    else if(type==2){
        for(i=0 ; i<n ; i++){
        j=n;
        mat[i]=malloc(n*sizeof(int));
        path[i]=malloc(n*sizeof(int));

        while(j--){
            //if(i==j)
                mat[i][j]=k;

            path[i][j]=0;
        }
    }
    }
}



void matprint(int** p,int n){
    int i,j;

    printf("\n  ");

    //printf("\nMAtrix print");
    for(i=0 ; i<n ; i++){
        j=0;
        printf("\n");
        while(j<n){
            printf("%d ",p[i][j]);
            j++;
        }
    }
}



void matdel(int n){
    int i;
    for(i=0 ; i<n ; i++){
        free(mat[i]);
        free(path[i]);
    }
    free(mat);
    free(path);
}



void initfloyd(int n){
    int i;


    fptr=fopen("files/327_nodes.txt","r");
    if(fptr==NULL){
        printf("\nFile not available ");
        exit(0);
    }

    matrixgen(n,1);
    gp=create(n);
    int v1,v2,v3;
    while(fscanf(fptr,"%d%d%d",&v1,&v2,&v3)!=EOF){
        addv(gp,v2,v1);
        mat[v1][v2]=1;
        mat[v2][v1]=1;
        path[v1][v2]=1;
        path[v2][v1]=1;
    }
    fclose(fptr);

    //matprint(mat,n);
    bc=malloc(n*sizeof(float*));
    for(i=0 ; i<n ; i++)
        bc[i]=0;


    //printlist(gp);

    fptr=fopen("files/327_nodes_floyd.txt","w+");

    if(fptr==NULL){
        printf("\nFile not created ");
        matdel(n);
        deladj(&gp);
        exit(0);
    }

    floyd(n);


    for(i=0 ; i<n ; i++){
        fprintf(fptr,"%d %f\n",i,bc[i]);
    }

    fclose(fptr);
    free(bc);
    matdel(n);
    deladj(&gp);
}


void initbfs(int n){
    int i,j,k;
    FILE *fptr=fopen("files/327_nodes.txt","r");
    if(fptr==NULL){
        printf("\nFile not available ");
        exit(0);
    }

    matrixgen(n,2);
    gp=create(n);
    int v1,v2,v3;
    while(fscanf(fptr,"%d%d%d",&v1,&v2,&v3)!=EOF){
        addv(gp,v2,v1);
        mat[v1][v2]=1;
        mat[v2][v1]=1;
        path[v1][v2]=1;
        path[v2][v1]=1;
    }
    fclose(fptr);




    bc=malloc(n*sizeof(float*));
    vd=malloc(n*sizeof(int*));
    que=malloc(n*sizeof(int*));

    for(i=0 ; i<n ; i++){
        bc[i]=0;
        bfs(i);
        initb();
    }

    //matprint(mat,n);
    //matprint(path,n);

    for(i=0 ; i<n ; i++){
        for(j=0 ; j<i ; j++){
            path[j][i]=path[i][j];
        }
    }

    for(k=0 ; k<n ; k++){
        for(i=0 ; i<n ; i++){
            for(j=0 ; j<i ; j++){
                if(mat[i][j]==mat[i][k]+mat[k][j] && i!=k && k!=j )
                    bc[k]+=(path[i][k]*path[k][j])/(float)path[i][j];
            }
        }
    }

    fptr=fopen("files/327_nodes_bfs.txt","w+");

    if(fptr==NULL){
        printf("\nFile not created ");
        matdel(n);
        deladj(&gp);
        exit(0);
    }


    for(i=0 ; i<n ; i++){
        fprintf(fptr,"%d %f\n",i,(bc[i]));
    }

    fclose(fptr);

    free(bc);
    free(que);
    free(vd);

    matdel(n);
    deladj(&gp);
}

//Computing betweness centrality using floyd warshall algo
void floyd(int n){
    int i,j,k;

    for(k=0 ; k<n ; k++){
        for(i=0 ; i<n ; i++){
            for(j=0 ; j<n ; j++){
                if(mat[i][j]==mat[i][k]+mat[k][j] && i!=k && k!=j  ){

                    path[i][j]+=path[i][k]*path[k][j];

                }
                else if(mat[i][j]>mat[i][k]+mat[k][j]){
                    mat[i][j]=mat[i][k]+mat[k][j];

                    path[i][j]=path[i][k]*path[k][j];

                }
            }
        }
        //matprint(mat,n);
    }


    for(k=0 ; k<n ; k++){

        for(i=0 ; i<n ; i++){
            for(j=0 ; j<i ; j++){

                if(mat[i][j]==mat[i][k]+mat[k][j] && i!=k && k!=j ){
                    bc[k]+=(float)((path[i][k]*path[k][j])/(float)path[i][j]);

                }
            }
        }
    }
}


void initb(){

    int i;
    for(i=0 ; i<n ; i++){
        que[i]=0;
        vd[i]=0;
    }
}



struct q* createq() {
    struct q* q = malloc(sizeof(struct q));
    q->front = -1;
    q->rear = -1;
    return q;
}



int empty(struct q* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}




void enq(struct q* q, int val){
    if(q->rear == n-1)
        printf("\nQ full");
    else{
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        que[q->rear]=val;
    }
}




int deq(struct q* q){
    int sta;
    if(empty(q)){
        //printf("q empty");
        sta = -1;
    }
    else{
        sta = que[q->front];
        q->front++;
        if(q->front > q->rear){
            //printf("Reset q");
            q->front = q->rear = -1;
        }
    }
    return sta;
}



//Computing betweness centrality using bfs algo
void bfs(int vert){

    int i,j,k;
    struct q* q=createq();
    vd[vert]=1;
    enq(q,vert);

    while(!empty(q)){
        int cv=deq(q);
        struct node* p=gp->varr[cv].head;

        while(p){

            if(p->v==vert ){
                p=p->next;
                continue;
            }

            if(vd[p->v]==0){
                vd[p->v]=1;
                enq(q,p->v);
            }
            if(mat[vert][p->v]>mat[vert][cv]+1){
                mat[vert][p->v]=mat[vert][cv]+1;
                path[vert][p->v]=path[vert][cv];
                mat[p->v][vert]=mat[vert][p->v];
            }
            else if(mat[vert][p->v]==mat[vert][cv]+1)
                path[vert][p->v]+=path[vert][cv];

            p=p->next;
        }
    }

}
