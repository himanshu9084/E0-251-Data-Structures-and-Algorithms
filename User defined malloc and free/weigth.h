#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define allocate(x) (x*)malloc(sizeof(x))
#define print(x) printf(x);


struct avail{
  struct asl* head;
  struct data* idata;
  struct single* root;
};
typedef struct avail avail;


struct asl{
    struct block* start;
    struct block* last;
};
typedef struct asl asl;

struct block{
  int addr;
  int kval;
  int tag;
  int type;
  struct single* tn;
  struct block* next;
  struct block* prev;
};
typedef struct block block;

struct data{
    int allocreq;
    int allocfil;
    int dealloc;
    int split;
    int rcomb;
    int iarea;
    int exarea;
};
typedef struct data data;

struct single{
    int bsize;
    int tag;
    //int addr;
    struct block* bpr;
    struct single* pr;
    struct single* lc;
    struct single* rc;
};
typedef struct single single;


//Full memory block
void* mem=NULL;
int msize=1<<5; //256B
int asize;
int req;
asl* arr;
unsigned long* lv;

//Returns k for 2^k=n
int ispow(int n){
    int c=0;
    if(n%3==0)
        n=n/3;
    while(n!=1){
        c++;
        n=n>>1;
    }
    return c;
}

//initializing everything
void init(avail* p){
    asize=2*ispow(msize);
    asl* t=p->head;
    p->head=NULL;
    p->idata=NULL;
    p->root=NULL;

    arr=(asl*)malloc(asize*sizeof(asl));
    p->head=&arr[0];

    //printf("\n%d %d",p->head,arr);
    int i=0;
    while(i<asize){
        (p->head+i)->start=NULL;
        (p->head+i)->last=NULL;
        i++;
    }
    //printf(" %d %d ",p->head,(p->head+2)->start);

    block* lead=allocate(block);
    lead->addr=(unsigned long)mem;
    lead->tag=1;
    lead->type=1;
    lead->kval=ispow(msize);
    lead->next=NULL;
    lead->prev=NULL;
    lead->tn=p->root;

    i=asize-1;
    (p->head+i)->start=lead;
    (p->head+i)->last=lead;

    data* dt=allocate(data);
    dt->allocreq=0;
    dt->allocfil=0;
    dt->dealloc=0;
    dt->split=0;
    dt->rcomb=0;
    dt->iarea=0;
    dt->exarea=msize;
    p->idata=dt;

    single* node=allocate(single);
    node->bsize=msize;
    node->tag=1;
    node->pr=NULL;
    node->lc=NULL;
    node->rc=NULL;
    node->bpr=NULL;
    p->root=node;

}

//required size of block
int reqsize(int req){
    if(req==1 || req==2 || req==3)
        return req;
    int k=1,i=0;
    while(k<req){
        k=k<<1;
        i++;
    }
    //printf("%d",k);
    int bel=1<<(i-2);
    bel*=3;
    if(req<bel)
        return bel;
    else
        return k;
}

void spinit(single* p,single* k1,single* k2){
    p->lc=k1;
    p->rc=k2;
    k1->pr=p;
    k2->pr=p;
    k1->tag=1;
    k2->tag=1;
    k2->lc=NULL;
    k1->lc=NULL;
    k1->rc=NULL;
    k2->rc=NULL;
    p->bpr=NULL;
    k1->bpr=NULL;
    k2->bpr=NULL;
}

//First split
single* fsplit(single* p){
    if(p==NULL)
        return NULL;

    if(p->bsize==req){
        //p->type=0;
        return p;
    }

    int k;
    k=ispow(p->bsize);
    single* k1=allocate(single);
    single* k2=allocate(single);

    if(p->bsize%3==0){    //3.2^k
        k1->bsize=(1<<(k+1));
        k2->bsize=(1<<k);
        //printf("\n%d %d",k1,k2);
    }
    else{           //2^k
        k1->bsize=3*(1<<(k-2));
        k2->bsize=1<<(k-2);
    }
    //printf("\n%d %d",k1->bsize,k2->bsize);
    spinit(p,k1,k2);


    if(req>k2->bsize)
        return fsplit(k1);
    else if(k2->bsize==2)
        return fsplit(k1);
    else
        return fsplit(k2);
}

//mapping bsize to array arr
int bsizearr(int bsize){
    if(bsize==1) return 0;
    int k=ispow(bsize);
    if(bsize%3==0){
        k*=2;
        k+=3;
    }
    else
        k*=2;
    return k-1;
}

//Determining type
int retype(single* p){
    int k=ispow(p->pr->bsize);
    if(p->pr->bsize%3==0){
        if(p->bsize==(1<<(k+1)))
           return 01;
        else
            return 10;
    }
    else
        return 11;
}


//Insert into asl array
void insarr(single* p,avail* fd){
    //printf("ins %d",p->bsize);
    asl* ar=(fd->head+bsizearr(p->bsize));

    block* ml=allocate(block);
    ml->addr=p->bsize;
    ml->tag=1;
    if(p->bsize==msize){
        ml->kval=ispow(p->bsize);
        ml->type=0;
    }
    else{
        ml->kval=ispow(p->pr->bsize);
        ml->type=retype(p);
    }
    p->bpr=ml;
    ml->tn=p;
    //print(" hi 1");

    if(ar->start==NULL){
        //print(" hi 2");
        ar->start=ml;
        ar->last=ml;
        ml->next=NULL;
        ml->prev=NULL;
    }
    else{
        //print(" hi 3");
        ar->last->next=ml;
        ml->prev=ar->last;
        ar->last=ml;
        ml->next=NULL;
    }
}

//Tree traversal tree
void traverse(single* p,avail* fd){
    if(p==NULL)
        return;

    if(p->lc==NULL && p->rc==NULL){
        //printf("\n%d",p->bsize);
        if(!p->bpr && p->tag==1)
            insarr(p,fd);
        return;
    }

    //printf("\n%d %d",p->lc->bsize,p->rc->bsize);
    if(p->lc)
        traverse(p->lc,fd);
    if(p->rc)
        traverse(p->rc,fd);
}

//Printing alloation tree
void treepr(single* p){
    if(p==NULL)
        return;
    //printf("\n%d %d",p->bsize,p->tag);
    treepr(p->lc);
    treepr(p->rc);
}

//Searching the asl array for the block to split
single* aslser(avail* p){
    asl* ar=p->head;
    block*b=NULL;
    int i=0;
    while(i<asize){
        ar=p->head+i;
        b=ar->start;
        while(b){
            if(b->tn->bsize>=req && b->tn->tag==1)
                return b->tn;
            b=b->next;
        }
        i++;
    }
    return NULL;
}


//Allocating address
void retaddr(single* p, int lvs){
    int n=lvs;
    int i=0;
    int uaddr=(unsigned long)mem;
    single* t=(single*)(unsigned long)lv[i];
    if(t->bpr)
        t->bpr->addr=uaddr;

    for(i=1 ; i<n ; i++){
        uaddr+=t->bsize;
        t=(single*)(unsigned long)lv[i];
        if(t->bpr)
            t->bpr->addr=uaddr;
    }
}

int ind=0;
void asladdr(single* p){    //Making linear ordered leaves
    if(p==NULL)
        return;

    if(p->lc==NULL && p->rc==NULL){
        lv[ind++]=(unsigned long)p;
    }

    //printf("\n%d %d",p->lc->bsize,p->rc->bsize);
    if(p->lc)
        asladdr(p->lc);
    if(p->rc)
        asladdr(p->rc);
}




//Traversing asl array
void traasl(avail* p){
    asl* ar=p->head;
    block* b=NULL;
    int i=0;
    while(i<asize){
        ar=p->head+i;
        b=ar->start;
        while(b){
            //printf("\n%d %d",i,b->addr);
            b=b->next;
        }
        //printf(" %d %d ",i,(p->head+i)->start);
        i++;
    }
}

//Deleting from asl
void delasl(avail* p,single* node){
    asl* ar=p->head;
    block* b=NULL;
    int i=0;
    while(i<asize){
        ar=p->head+i;
        b=ar->start;
        while(b){
            if(b->tn==node)
                break;
            b=b->next;
        }
        if(b)
        if(b->tn==node)
            break;
        i++;
    }
    //printf(" %d ",i);
    if(i==asize-1)
        return;
    node->bpr=NULL;
    if(ar->start == ar->last){
        //printf(" %d",b->addr);
        free(b);
        ar->start=NULL;
        ar->last=NULL;
    }
    else{
        ar->start=b->next;
        b->next->prev=NULL;
        free(b);
    }
}



//Finding block for free
single* findblock(int faddr,int lvs){
    int n=lvs;
    int i=0;
    int uaddr=(unsigned long)mem;
    single* t=((single*)(unsigned long)lv[i]);


    for(i=1 ; i<n ; i++){
        uaddr+=(int)t->bsize;
        t=((single*)(unsigned long)lv[i]);
        if(uaddr==faddr)
            break;
    }
    //printf("\nfree %d ",t->bsize);
    return t;
}


//Counting splits
int totsplit(single* p){
    if(p==NULL)
        return 0;
    if(!p->lc && !p->rc)
        return 0;
    else
        return 1+totsplit(p->lc)+totsplit(p->rc);
}


//Recombining buddies
void uptag(single* p){
    if(p==NULL)
        return;

    uptag(p->lc);
    uptag(p->rc);

    if(p->lc && p->rc){
        if(p->lc->tag==0 || p->rc->tag==0)
            p->tag=0;
    }
}

void unuptag(single* p){
    if(p==NULL)
        return;

    unuptag(p->lc);
    unuptag(p->rc);

    if(p->lc && p->rc){
        p->tag=1;
    }
}

void recombine(single* tn,avail* p){
    if(tn==NULL)
        return;

    if(tn->lc==NULL && tn->rc==NULL)
        return;

    if(tn->lc)
        recombine(tn->lc,p);
    if(tn->rc)
        recombine(tn->rc,p);

    if(tn->lc && tn->rc){
        if(tn->lc->tag==1 && tn->rc->tag==1){
            delasl(p,tn->lc);
            delasl(p,tn->rc);
            free(tn->lc);
            free(tn->rc);
            tn->lc=NULL;
            tn->rc=NULL;
            tn->tag=1;
            p->idata->rcomb+=1;
        }
    }
}

//Printing alloc data
void printdat(avail* p){
    data* dt=p->idata;
    print("\n--------------------------------------------------------------");
    printf("\nAllocation requests = %d",dt->allocreq);
    printf("\nAllocation requests fulfilled = %d",dt->allocfil);
    printf("\nDEallocation requests = %d",dt->dealloc);
    printf("\nTotal splits = %d",dt->split);
    printf("\nTotal recombines(of buddy) = %d",dt->rcomb);
    printf("\nInternal fragmentation = %d",dt->iarea);
    printf("\nMemory allocated(in %%) = %f",((msize-dt->exarea)*1.0)/(msize));
    print("\n--------------------------------------------------------------\n");
}

//user implemented malloc function
void* bmalloc(avail* p,int preq){
    req=reqsize(preq);
    void* addr=NULL;
    if(req>p->idata->exarea){
        printf("\nBlock can't be allocated");
        //printdat(p);
        return NULL;
    }

    if(p->idata->allocreq==0){//First request
        p->idata->allocreq+=1;
        if(req==msize){
            int i=asize-1;
            p->root->tag=0;
            p->root->bpr=(p->head+i)->start;
            p->root->bpr->tag=0;
            addr=(void*)mem;
        }
        else{
            single* bl=fsplit(p->root);
            treepr(p->root);
            traverse(p->root,p);
            bl->tag=0;

            p->idata->split=totsplit(p->root);
            int lvs=p->idata->split+1;
            lv=(unsigned long*)malloc(lvs*sizeof(unsigned long));
            ind=0;
            asladdr(p->root);
            retaddr(p->root,lvs);
            free(lv);


            addr=(void*)(unsigned long)bl->bpr->addr;
            delasl(p,bl);
            traasl(p);
            //bl->bpr->tag=0;
        }
        p->idata->allocfil+=1;
        p->idata->iarea+=req-preq;
        p->idata->exarea-=req;

        printf("\nBlock allocated of size = %d",req);
        //printdat(p);
        return (void*)addr;

    }
    else{ //Not the first request
        p->idata->allocreq+=1;
        single* node=aslser(p);
        if(node==NULL){
            printf("\nBlock can't be allocated");
            //return;
        }
        else{
            delasl(p,node);
            node=fsplit(node);
            treepr(p->root);
            traverse(p->root,p);
            node->tag=0;

            p->idata->split+=(totsplit(p->root)-p->idata->split);
            int lvs=p->idata->split+1;
            lv=(unsigned long*)malloc(lvs*sizeof(unsigned long));
            ind=0;
            asladdr(p->root);
            retaddr(p->root,lvs);
            free(lv);

            addr=(void*)(unsigned long)node->bpr->addr;
            delasl(p,node);
            traasl(p);

            printf("\nBlock allocated  of size = %d",req);
            p->idata->allocfil+=1;
            p->idata->iarea+=req-preq;
            p->idata->exarea-=req;

        }
        //printdat(p);
        return (void*)addr;
        //p->idata->iarea+=req-preq;
    }
}



//user implemented free function
void bfree(avail* p,void* tf){
    //printf("\n%d %d",tf,sizeof(tf));

    p->idata->dealloc+=1;
    /*if(!((unsigned long)tf<((unsigned long)(mem+msize)) && (unsigned long)tf>=((unsigned long)mem))){
        printf("\n%p  %p\n",tf,mem);
        printf("\n\nAddress not allocated through user defined malloc");
        return;
    }
    else{*/
        int lvs=p->idata->split+1;
        lv=(unsigned long*)malloc(lvs*sizeof(unsigned long));
        ind=0;
        asladdr(p->root);

        single* t=findblock((unsigned long)tf,lvs);
        t->tag=1;
        int wf=reqsize(t->bsize);
        if(p->idata->iarea)
            p->idata->iarea-=wf;
        p->idata->exarea+=wf;

        traverse(p->root,p);
        //retaddr(p->root,lvs);
        free(lv);

        treepr(p->root);
        traasl(p);

        uptag(p->root);
        recombine(p->root,p);
        unuptag(p->root);

        treepr(p->root);

        //print("\nAfter combine");
        //printf("\n%d",p->root->bpr);
        traverse(p->root,p);
        //print("\nAfter traverse");
        if(p->root->lc && p->root->rc){
            lvs=p->idata->split+1;
            lv=(unsigned long*)malloc(lvs*sizeof(unsigned long));
            ind=0;
            asladdr(p->root);
            //retaddr(p->root,lvs);
        }

        traasl(p);
        //printf("\n%d",t->bsize);
        treepr(p->root);
        free(lv);
    //}
    print("\nBlock deallocated");
    //printdat(p);
}
