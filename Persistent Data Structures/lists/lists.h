#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define allocate(x) (x*)malloc(sizeof(x))
#define print(x) printf(x);

struct singleh{
    struct single* head;
    int vn;
};
typedef struct singleh singleh;

struct single{
int valn;
struct single* next;
struct mods* modp;
};
typedef struct single single;

struct doubleh{
    struct doubly* head;
    int vn;
};
typedef struct doubleh doubleh;

struct doubly{
    int valn;
    struct doubly* prev;
    struct doubly* next;
    struct mods* modp;
};
typedef struct doubly doubly;

struct mods{
int type;
int val;
struct mods* lt;
struct mods* rt;
struct mods* next;
int ver;
};
typedef struct mods mods;




struct singlehf{
    struct singlef* head;
    int vn;
};
typedef struct singlehf singlehf;

struct doublehf{
    struct doublef* head;
    int vn;
};
typedef struct doublehf doublehf;

struct singlef{
int valn;
struct singlef* next;
struct modf* modp;
};
typedef struct singlef singlef;

struct doublef{
    int valn;
    struct doublef* prev;
    struct doublef* next;
    struct modf* modp;
};
typedef struct doublef doublef;


struct modf{
    int type;
    int val;
    struct modf* mc[4];
    int ver;
};
typedef struct modf modf;



//Singly list partial
//For initializing partially persistent singly list head
void spinit(singleh* p){
    p->head=NULL;
    p->vn=1;
}

//For inserting at end of singly list, so creating new mods
void spinend(singleh* p,int x){

    single* t=p->head;
    if(t==NULL){
        t=allocate(single);
        t->valn=1;
        t->next=NULL;
        t->modp=allocate(mods);
        t->modp->type=0;
        t->modp->val=x;
        t->modp->lt=NULL;
        t->modp->rt=NULL;
        t->modp->next=NULL;
        t->modp->ver=(p->vn)++;
        //printf(",inserted");
        p->head=t;
    }
    else{
        int k=2;
        while(t->next){
            t=t->next;
            k++;
        }
        //printf("%d",k);
        single *t2=allocate(single);
        t2->valn=k;
        t2->next=NULL;
        t2->modp=allocate(mods);
        t2->modp->type=0;
        t2->modp->val=x;
        t2->modp->lt=t->modp;
        t->modp->rt=t2->modp;

        t2->modp->rt=NULL;

        t2->modp->next=NULL;
        t2->modp->ver=(p->vn)++;
        t->next=t2;
    }
}

//For displaying through latest modifications only
void spdispl(singleh* p){
    single* t=p->head;

    while(t){
        if(t->modp->type!=3)
        printf("\n%d->%d ver=%d",t->valn,t->modp->val,t->modp->ver);
        t=t->next;
    }

    /*mods* t2=(p->head)->modp;
    while(t2){
        printf(" %d ",t2->val);
        t2=t2->rt;
    }*/
    free(t);
}

//For modifying at pos,value at it's latest version
void spinmod(singleh* p,int pos, int x){
    single* t=p->head;
    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    mods* ml=allocate(mods);
    ml->val=x;
    ml->type=0;
    ml->ver=(p->vn)++;

    ml->next=(t->next)->modp;
    (t->next)->modp=ml;

    ml->lt=ml->next->lt;
    ml->rt=ml->next->rt;

    if(ml->next->rt!=NULL)
            ml->next->rt->lt=ml;

    if(ml->next->lt!=NULL)
            ml->next->lt->rt=ml;

    ml->next->rt=NULL;
    ml->next->lt=NULL;
}

//For Version history at pos
void spverh(singleh* p,int pos){
    single* t=p->head;
    while((t->next)->valn!=pos)
            t=t->next;
    mods* ml=(t->next)->modp;
    while(ml){
        printf("\n%d ver=%d",ml->val,ml->ver);
        ml=ml->next;
    }
}

//For inserting new node in between positions, after pos
void spinbtw(singleh* p, int pos,int x){
    single* t=p->head;
    while(t->valn!=pos)
            t=t->next;
    //printf("%d", t->valn);
    mods* ml=allocate(mods);
    ml->val=x;
    ml->type=0;
    ml->ver=(p->vn)++;

    single* t2=allocate(single);
    t2->next=t->next;
    t->next=t2;
    t2->valn=t->valn+1;
    t2->modp=ml;
    t2->modp->next=NULL;

    t2->modp->rt=t2->next->modp;
    t2->next->modp->lt=ml;
    t2->modp->lt=t->modp;
    t->modp->rt=ml;

    t=t2->next;
    while(t){
        t->valn+=1;
        t=t->next;
    }
}

//For deleting node with given pos
void spdel(singleh* p, int pos){
    single* t=p->head;
    mods* ml=allocate(mods);

    ml->type=3;
    ml->ver=(p->vn)++;

    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    single* t2=t->next;
    //Starting node
    if(t->valn==1 && t->modp->type!=3){
        ml->next=t->modp;
        t->modp=ml;
        ml->val=ml->next->val;
        ml->lt=NULL;
        ml->rt=NULL;
        ml->next->rt=NULL;
        ml->next->lt=NULL;
        t2->modp->lt=NULL;
    }
    else if(t2->modp->type!=3){
        ml->next=t2->modp;
        t2->modp=ml;
        ml->val=ml->next->val;
        ml->lt=NULL;
        ml->rt=NULL;
        if(ml->next->rt!=NULL)
            ml->next->rt->lt=ml->next->lt;
        ml->next->lt->rt=ml->next->rt;
        ml->next->rt=NULL;
        ml->next->lt=NULL;
    }
}

//For Searching for values <=version
void spsearch(singleh* p, int x, int ver){
    single* t=p->head;
    mods* ml=NULL;
    int res=-1;
    int isdel=0;
    while(t){
        isdel=t->modp->type;
        ml=t->modp;
        while(ml){
            if(ml->ver<=ver)
            if(ml->val==x){
                res=ml->ver;
                break;
            }
            ml=ml->next;
        }
        if(res!=-1)
            break;
        t=t->next;
    }
    if(res==-1)
        printf("\nValue not found");
    else
        printf("\nValue found at node %d ver=%d",t->valn,res);
    if(isdel==3)
        printf(" Deleted node");
}

//For full display of list starting from version 1 to current version
void spdispall(singleh* p){
    single* t=p->head;
    mods* ml=NULL;

    while(t){
        mods* ml=t->modp;
        printf("\nNode %d",t->valn);
        if(t->modp->type==3)
            printf("\nDeleted node %d",t->valn);
        while(ml){
            printf("\n%d ver=%d",ml->val,ml->ver);
            ml=ml->next;
        }
        t=t->next;
    }
}

//For deallocating Memory used by sp
void spdealloc(singleh* p){
    single* t=p->head;
    single* t2=t;
    mods* ml=t->modp;
    mods* ml1=ml;
    while(t){
        ml=t->modp;
        ml1=ml;
        while(ml){
            ml1=ml;
            ml=ml->next;
            free(ml1);
        }
        t2=t;
        t=t->next;
    }
}


//Doubly list partial
//For initializing partially persistent doubly list head
void dpinit(doubleh* p){
    p->head=NULL;
    p->vn=1;
}

//For inserting at end of doubly list, so creating new mods
void dpinend(doubleh* p,int x){
    doubly* t=p->head;
    if(t==NULL){
        t=allocate(doubly);
        t->valn=1;
        t->next=NULL;
        t->prev=NULL;
        t->modp=allocate(mods);
        t->modp->type=0;
        t->modp->val=x;
        t->modp->lt=NULL;
        t->modp->rt=NULL;
        t->modp->next=NULL;
        t->modp->ver=(p->vn)++;
        //printf(",inserted");
        p->head=t;
    }
    else{
        int k=2;
        while(t->next){
            t=t->next;
            k++;
        }
        //printf("%d",k);
        doubly *t2=allocate(doubly);
        t2->valn=k;
        t2->prev=t;
        t2->next=NULL;
        t2->modp=allocate(mods);
        t2->modp->type=0;
        t2->modp->val=x;
        t2->modp->lt=t->modp;
        t->modp->rt=t2->modp;

        t2->modp->rt=NULL;

        t2->modp->next=NULL;
        t2->modp->ver=(p->vn)++;
        t->next=t2;
    }
}

//For displaying through latest modifications only,doubly list
void dpdispl(doubleh* p){
    doubly* t=p->head;

    while(t){
        if(t->modp->type!=3)
        printf("\n%d->%d ver=%d",t->valn,t->modp->val,t->modp->ver);
        t=t->next;
    }

    /*mods* t2=(p->head)->modp;
    while(t2){
        printf(" %d ",t2->val);
        t2=t2->rt;
    }*/
    free(t);
}

//For modifying at pos,value at it's latest version,doubly list
void dpinmod(doubleh* p,int pos, int x){
    doubly* t=p->head;
    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    mods* ml=allocate(mods);
    ml->val=x;
    ml->type=0;
    ml->ver=(p->vn)++;

    ml->next=(t->next)->modp;
    (t->next)->modp=ml;

    ml->lt=ml->next->lt;
    ml->rt=ml->next->rt;

    if(ml->next->rt!=NULL)
            ml->next->rt->lt=ml;

    if(ml->next->lt!=NULL)
            ml->next->lt->rt=ml;

    ml->next->rt=NULL;
    ml->next->lt=NULL;
}

//For inserting new node in between positions, after pos,doubly list
void dpinbtw(doubleh* p, int pos,int x){
    doubly* t=p->head;
    while(t->valn!=pos)
            t=t->next;
    //printf("%d", t->valn);
    mods* ml=allocate(mods);
    ml->val=x;
    ml->type=0;
    ml->ver=(p->vn)++;

    doubly* t2=allocate(doubly);
    t2->next=t->next;
    t2->prev=t;
    t->next=t2;
    t2->next->prev=t2;

    t2->valn=t->valn+1;
    t2->modp=ml;
    t2->modp->next=NULL;

    t2->modp->rt=t2->next->modp;
    t2->next->modp->lt=ml;
    t2->modp->lt=t->modp;
    t->modp->rt=ml;

    t=t2->next;
    while(t){
        t->valn+=1;
        t=t->next;
    }
}

//For Version history at pos,doubly list
void dpverh(doubleh* p,int pos){
    doubly* t=p->head;
    while((t->next)->valn!=pos)
            t=t->next;
    mods* ml=(t->next)->modp;
    while(ml){
        printf("\n%d ver=%d",ml->val,ml->ver);
        ml=ml->next;
    }
}

//For deleting node with given pos,doubly list
void dpdel(doubleh* p, int pos){
    doubly* t=p->head;
    mods* ml=allocate(mods);

    ml->type=3;
    ml->ver=(p->vn)++;

    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    doubly* t2=t->next;
    //Starting node
    if(t->valn==1 && t->modp->type!=3){
        ml->next=t->modp;
        t->modp=ml;
        ml->val=ml->next->val;
        ml->lt=NULL;
        ml->rt=NULL;
        ml->next->rt=NULL;
        ml->next->lt=NULL;
        t2->modp->lt=NULL;
    }
    else if(t2->modp->type!=3){
        ml->next=t2->modp;
        t2->modp=ml;
        ml->val=ml->next->val;
        ml->lt=NULL;
        ml->rt=NULL;
        if(ml->next->rt!=NULL)
            ml->next->rt->lt=ml->next->lt;
        ml->next->lt->rt=ml->next->rt;
        ml->next->rt=NULL;
        ml->next->lt=NULL;
    }
}

//For full display of list starting from version 1 to current version,doubly list
void dpdispall(doubleh* p){
    doubly* t=p->head;
    mods* ml=NULL;

    while(t){
        mods* ml=t->modp;
        printf("\nNode %d",t->valn);
        if(t->modp->type==3)
            printf("\nDeleted node %d",t->valn);
        while(ml){
            printf("\n%d ver=%d",ml->val,ml->ver);
            ml=ml->next;
        }
        t=t->next;
    }
}

//For Searching for values <=version,doubly list
void dpsearch(doubleh* p, int x, int ver){
    doubly* t=p->head;
    mods* ml=NULL;
    int res=-1;
    int isdel=0;
    while(t){
        isdel=t->modp->type;
        ml=t->modp;
        while(ml){
            if(ml->ver<=ver)
            if(ml->val==x){
                res=ml->ver;
                break;
            }
            ml=ml->next;
        }
        if(res!=-1)
            break;
        t=t->next;
    }
    if(res==-1)
        printf("\nValue not found");
    else
        printf("\nValue found at node %d ver=%d",t->valn,res);
    if(isdel==3)
        printf(" Deleted node");
}

//For deallocating Memory used by sp,doubly list
void dpdealloc(doubleh* p){
    doubly* t=p->head;
    doubly* t2=t;
    mods* ml=t->modp;
    mods* ml1=ml;
    while(t){
        ml=t->modp;
        ml1=ml;
        while(ml){
            ml1=ml;
            ml=ml->next;
            free(ml1);
        }
        t2=t;
        t=t->next;
    }
}


//Circular List partial
//For inserting at end of circular list, so creating new mods
void cpinend(singleh* p,int x){
    single* te=p->head;
    single* t=p->head;
    if(t==NULL){
        t=allocate(single);
        t->valn=1;
        t->next=t;
        t->modp=allocate(mods);
        t->modp->type=0;
        t->modp->val=x;
        t->modp->lt=NULL;
        t->modp->rt=NULL;
        t->modp->next=NULL;
        t->modp->ver=(p->vn)++;
        //printf(",inserted");
        p->head=t;
    }
    else{
        int k=2;
        while(t->next!=te){
            t=t->next;
            k++;
        }
        //printf("%d",k);
        single *t2=allocate(single);
        t2->valn=k;
        t2->next=te;

        t2->modp=allocate(mods);
        t2->modp->type=0;
        t2->modp->val=x;
        t2->modp->lt=t->modp;
        t->modp->rt=t2->modp;

        t2->modp->rt=NULL;

        t2->modp->next=NULL;
        t2->modp->ver=(p->vn)++;
        t->next=t2;
    }
}

//For displaying through latest modifications only,circular list
void cpdispl(singleh* p){
    single* te=p->head;
    single* t=te;

    while(1){
        if(t->modp->type!=3)
        printf("\n%d->%d ver=%d",t->valn,t->modp->val,t->modp->ver);
        t=t->next;
        if(t==te)
            break;
    }

    /*mods* t2=(p->head)->modp;
    while(t2){
        printf(" %d ",t2->val);
        t2=t2->rt;
    }*/
}

//For modifying at pos,value at it's latest version, circular list
void cpinmod(singleh* p,int pos, int x){
    single* te=p->head;
    single* t=p->head;
    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    mods* ml=allocate(mods);
    ml->val=x;
    ml->type=0;
    ml->ver=(p->vn)++;

    ml->next=(t->next)->modp;
    (t->next)->modp=ml;

    ml->lt=ml->next->lt;
    ml->rt=ml->next->rt;

    if(ml->next->rt!=NULL)
            ml->next->rt->lt=ml;

    if(ml->next->lt!=NULL)
            ml->next->lt->rt=ml;

    ml->next->rt=NULL;
    ml->next->lt=NULL;
}

//For inserting new node in between positions, after pos,circular list
void cpinbtw(singleh* p, int pos,int x){
    single* te=p->head;
    single* t=p->head;
    while(t->valn!=pos)
            t=t->next;
    //printf("%d", t->valn);
    mods* ml=allocate(mods);
    ml->val=x;
    ml->type=0;
    ml->ver=(p->vn)++;

    single* t2=allocate(single);
    t2->next=t->next;
    t->next=t2;
    t2->valn=t->valn+1;
    t2->modp=ml;
    t2->modp->next=NULL;

    t2->modp->rt=t2->next->modp;
    t2->next->modp->lt=ml;
    t2->modp->lt=t->modp;
    t->modp->rt=ml;

    t=t2->next;
    while(t){
        t->valn+=1;
        t=t->next;
        if(t==te)
            break;
    }
}

//For deleting node with given pos
void cpdel(singleh* p, int pos){
    single* t=p->head;
    single* te=p->head;
    mods* ml=allocate(mods);

    ml->type=3;
    ml->ver=(p->vn)++;

    if(pos!=1)
    while((t->next)->valn!=pos){
        t=t->next;
        if(t==te)
            break;
    }


    single* t2=t->next;
    //Starting node
    if(t->valn==1 && t->modp->type!=3){
        ml->next=t->modp;
        t->modp=ml;
        ml->val=ml->next->val;
        ml->lt=NULL;
        ml->rt=NULL;
        ml->next->rt=NULL;
        ml->next->lt=NULL;
        t2->modp->lt=NULL;
    }
    else if(t2->modp->type!=3){
        ml->next=t2->modp;
        t2->modp=ml;
        ml->val=ml->next->val;
        ml->lt=NULL;
        ml->rt=NULL;
        if(ml->next->rt!=NULL)
            ml->next->rt->lt=ml->next->lt;
        ml->next->lt->rt=ml->next->rt;
        ml->next->rt=NULL;
        ml->next->lt=NULL;
    }
}

//For Version history at pos, circular list
void cpverh(singleh* p,int pos){
    single* t=p->head;
    single* te=p->head;

    while((t->next)->valn!=pos){
        t=t->next;
        if(t==te)
            break;
    }

    mods* ml=(t->next)->modp;

    while(ml){
        printf("\n%d ver=%d",ml->val,ml->ver);
        ml=ml->next;
    }
}

//For Searching for values <=version, circular list
void cpsearch(singleh* p, int x, int ver){
    single* t=p->head;
    single* te=p->head;
    mods* ml=NULL;
    int res=-1;
    int isdel=0;
    while(t){
        isdel=t->modp->type;
        ml=t->modp;
        while(ml){
            if(ml->ver<=ver)
            if(ml->val==x){
                res=ml->ver;
                break;
            }
            ml=ml->next;
        }
        if(res!=-1)
            break;
        t=t->next;
        if(t==te)
            break;
    }
    if(res==-1)
        printf("\nValue not found");
    else
        printf("\nValue found at node %d ver=%d",t->valn,res);
    if(isdel==3)
        printf(" Deleted node");
}

//For full display of list starting from version 1 to current version, circular list
void cpdispall(singleh* p){
    single* te=p->head;
    single* t=p->head;
    mods* ml=NULL;

    while(t->next!=te){
        mods* ml=t->modp;
        printf("\nNode %d",t->valn);
        if(t->modp->type==3)
            printf("\nDeleted node %d",t->valn);
        while(ml){
            printf("\n%d ver=%d",ml->val,ml->ver);
            ml=ml->next;
        }
        t=t->next;
    }
}

//For deallocating Memory used by sp,circular list
void cpdealloc(singleh* p){
    single* t=p->head;
    single* te=p->head;
    single* t2=t;
    mods* ml=t->modp;
    mods* ml1=ml;
    while(t){

        while(ml){
            ml1=ml;
            ml=ml->next;
            free(ml1);
        }
        t2=t;
        t=t->next;
        free(t2);
        if(t==te)
            break;
    }
    free(t);
    free(t2);
    free(ml);
    free(ml1);
}







//Circular, double, singly fully persistent list
//For initializing fully persistent singly linked list
void sfinit(singlehf* p){
    p->head=NULL;
    p->vn=1;
}

//For initializing fully persistent singly linked list
void dfinit(doublehf* p){
    p->head=NULL;
    p->vn=1;
}

//Initializing fully modf mc array
void sfpoint4(modf* p){
    p->mc[0]=NULL;
    p->mc[1]=NULL;
    p->mc[2]=NULL;
    p->mc[3]=NULL;
    //printf("hi");
}


//For inserted in fully, singly linked list at end
void sfinend(singlehf* p,int x){
    singlef* t=p->head;
    if(t==NULL){
        t=allocate(singlef);
        t->valn=1;
        t->next=NULL;
        t->modp=allocate(modf);
        t->modp->type=0;
        t->modp->val=x;
        t->modp->ver=(p->vn)++;
        sfpoint4(t->modp);
        p->head=t;
    }
    else{
        int k=2;
        while(t->next){
            t=t->next;
            k++;
        }

        singlef* t2=allocate(singlef);
        t2->valn=k;
        t2->next=NULL;

        t2->modp=allocate(modf);
        t2->modp->type=0;
        t2->modp->val=x;
        t2->modp->ver=(p->vn)++;

        //t->modp->rt=t2->modp;
        sfpoint4(t2->modp);
        t->next=t2;
    }
}

//For inserted in fully, circular linked list at end
void cfinend(singlehf* p,int x){
    singlef* t=p->head;
    singlef* te=p->head;

    if(t==NULL){
        t=allocate(singlef);
        t->valn=1;
        t->next=t;
        t->modp=allocate(modf);
        t->modp->type=0;
        t->modp->val=x;
        t->modp->ver=(p->vn)++;
        sfpoint4(t->modp);
        p->head=t;
    }
    else{
        int k=2;
        while(t->next!=te){
            t=t->next;
            k++;
        }

        singlef* t2=allocate(singlef);
        t2->valn=k;
        t2->next=te;

        t2->modp=allocate(modf);
        t2->modp->type=0;
        t2->modp->val=x;
        t2->modp->ver=(p->vn)++;

        //t->modp->rt=t2->modp;
        sfpoint4(t2->modp);
        t->next=t2;
    }
}

//For inserted in fully, doubly linked list at end
void dfinend(doublehf* p,int x){
    doublef* t=p->head;
    if(t==NULL){
        t=allocate(doublef);
        t->valn=1;
        t->next=NULL;
        t->prev=NULL;
        t->modp=allocate(modf);
        t->modp->type=0;
        t->modp->val=x;
        t->modp->ver=(p->vn)++;
        sfpoint4(t->modp);
        p->head=t;
    }
    else{
        int k=2;
        while(t->next){
            t=t->next;
            k++;
        }

        doublef* t2=allocate(doublef);
        t2->valn=k;
        t2->next=NULL;
        t2->prev=t;

        t2->modp=allocate(modf);
        t2->modp->type=0;
        t2->modp->val=x;
        t2->modp->ver=(p->vn)++;

        //t->modp->rt=t2->modp;
        sfpoint4(t2->modp);
        t->next=t2;
    }
}



//For displaying fully singly latest modifications only
void sfdispl(singlehf* p){
    singlef* t=p->head;

    while(t){
        if(t->modp->type!=3)
        printf("\n%d->%d ver=%d",t->valn,t->modp->val,t->modp->ver);
        t=t->next;
    }

    /*mods* t2=(p->head)->modp;
    while(t2){
        printf(" %d ",t2->val);
        t2=t2->rt;
    }*/
    free(t);
}


//For modifying given version, singly fully
int sfrecin(modf* p,int ver,modf* ml){
    //printf(" %d",p->ver);
    if(p==NULL)
        return 0;
    if(p->ver==ver){
        if(p->mc[0]==NULL)
            p->mc[0]=ml;
        else if(p->mc[1]==NULL)
            p->mc[1]=ml;
        else if(p->mc[2]==NULL)
            p->mc[2]=ml;
        else if(p->mc[3]==NULL)
            p->mc[3]=ml;
        return 1;
    }
    else if(sfrecin(p->mc[0],ver,ml))
            return 1;
    else if(sfrecin(p->mc[1],ver,ml))
                return 1;
    else if(sfrecin(p->mc[2],ver,ml))
                return 1;
    else if(sfrecin(p->mc[3],ver,ml))
                return 1;
    else
        return 0;
}

void sfinmod(singlehf* p, int ver,int pos, int x){
    singlef* t=p->head;
    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    modf* ml=t->next->modp;
    //printf("%d",ml->ver);

    modf* ml2=allocate(modf);
    ml2->val=x;
    ml2->type=0;
    ml2->ver=(p->vn)++;
    sfpoint4(ml2);
    //printf("\n%d\n",ver);
    int k=sfrecin(ml,ver,ml2);
}

void dfinmod(doublehf* p, int ver,int pos, int x){
    doublef* t=p->head;
    if(pos!=1)
    while((t->next)->valn!=pos)
        t=t->next;

    modf* ml=t->next->modp;
    //printf("%d",ml->ver);

    modf* ml2=allocate(modf);
    ml2->val=x;
    ml2->type=0;
    ml2->ver=(p->vn)++;
    sfpoint4(ml2);
    //printf("\n%d\n",ver);
    int k=sfrecin(ml,ver,ml2);
}


//Version history for node in preorder, fully singly
void sfpre(modf* p){
    if(p==NULL)
        return;
    printf("\n%d ver=%d",p->val,p->ver);
    if(p->mc[0]!=NULL)
        printf("(");
    sfpre(p->mc[0]);
    sfpre(p->mc[1]);
    sfpre(p->mc[2]);
    sfpre(p->mc[3]);
    if(p->mc[0]!=NULL)
        printf(")");

}

void sfverh(singlehf* p, int pos){
    singlef* t=p->head;
    while(t->valn!=pos)
        t=t->next;
    modf* ml=t->modp;
    printf("\nVersion history for pos=%d",pos);
    sfpre(ml);
}

void dfverh(doublehf* p, int pos){
    doublef* t=p->head;
    while(t->valn!=pos)
        t=t->next;
    modf* ml=t->modp;
    printf("\nVersion history for pos=%d",pos);
    sfpre(ml);
}


//For inserting in between fully singly list
void sfinbtw(singlehf* p,int pos, int x){
    singlef* t=p->head;
    if(pos!=1)
    while(t->valn!=pos)
        t=t->next;

    singlef* t2=allocate(singlef);
    t2->valn=t->next->valn;
    t->next->valn=t2->valn+1;
    t2->next=t->next;
    t->next=t2;

    t2->modp=allocate(modf);
    t2->modp->type=0;
    t2->modp->val=x;
    sfpoint4(t2->modp);
    t2->modp->ver=(p->vn)++;
}

//Inserting in between doubly linked list
void dfinbtw(doublehf* p,int pos, int x){
    doublef* t=p->head;
    if(pos!=1)
    while(t->valn!=pos)
        t=t->next;

    doublef* t2=allocate(doublef);
    t2->valn=t->next->valn;
    t->next->valn=t2->valn+1;

    t2->next=t->next;
    t2->prev=t;
    t->next=t2;
    t2->next->prev=t2;

    t2->modp=allocate(modf);
    t2->modp->type=0;
    t2->modp->val=x;
    sfpoint4(t2->modp);
    t2->modp->ver=(p->vn)++;
}



//For deleting a node with version in fully singly
modf* sfrecdl(modf* p,int ver){
    modf* ml=NULL;
    if(p==NULL)
        return NULL;
    if(p->ver==ver){
        return p;
    }
    else{
    ml= sfrecdl(p->mc[0],ver);
    if(ml==NULL)
        ml=sfrecdl(p->mc[1],ver);
    if(ml==NULL)
        ml=sfrecdl(p->mc[2],ver);
    if(ml==NULL)
        ml=sfrecdl(p->mc[3],ver);
    return ml;
    }
}

void sfdel(singlehf* p, int pos, int ver){
    singlef* t=p->head;
    if(pos!=1)
    while(t->valn!=pos)
        t=t->next;
    modf* ml=allocate(modf);
    ml->type=3;
    ml->ver=(p->vn)++;
    sfpoint4(ml);

    modf* ml2=sfrecdl(t->modp,ver);
    ml->val=ml2->val;
    int k=sfrecin(ml2,ver,ml);
}

void dfdel(doublehf* p, int pos, int ver){
    doublef* t=p->head;
    if(pos!=1)
    while(t->valn!=pos)
        t=t->next;
    modf* ml=allocate(modf);
    ml->type=3;
    ml->ver=(p->vn)++;
    sfpoint4(ml);

    modf* ml2=sfrecdl(t->modp,ver);
    ml->val=ml2->val;
    int k=sfrecin(ml2,ver,ml);
}



//For Searching for a node
modf* sfreser(modf* p,int val,int ver){
    //printf(" %d",p->ver);
    modf* ml=NULL;
    if(p==NULL)
        return NULL;
    if(p->val==val && p->ver<=ver){
        return p;
    }
    else{
    ml= sfreser(p->mc[0],val,ver);
    if(ml==NULL)
        ml=sfreser(p->mc[1],val,ver);
    if(ml==NULL)
        ml=sfreser(p->mc[2],val,ver);
    if(ml==NULL)
        ml=sfreser(p->mc[3],val,ver);
    return ml;
    }
}

void sfsearch(singlehf* p,int x,int ver){
    singlef* t=p->head;
    modf* ml=NULL;
    while(t){
        ml=sfreser(t->modp,x,ver);
        if(ml==NULL)
            t=t->next;
        else
            break;
    }
    if(ml!=NULL)
        printf("\nValue find at %d ver=%d",t->valn,ml->ver);
    else
        printf("\nValue not found");
}

void cfsearch(singlehf* p,int x,int ver){
    singlef* t=p->head;
    singlef* te=p->head;
    modf* ml=NULL;
    while(t){
        ml=sfreser(t->modp,x,ver);
        if(ml==NULL)
            t=t->next;
        else
            break;
        if(t==te)
            break;
    }
    if(ml!=NULL)
        printf("\nValue find at %d ver=%d",t->valn,ml->ver);
    else
        printf("\nValue not found");
}

void dfsearch(doublehf* p,int x,int ver){
    doublef* t=p->head;
    modf* ml=NULL;
    while(t){
        ml=sfreser(t->modp,x,ver);
        if(ml==NULL)
            t=t->next;
        else
            break;
    }
    if(ml!=NULL)
        printf("\nValue find at %d ver=%d",t->valn,ml->ver);
    else
        printf("\nValue not found");
}


//For displaying full list
void sfdispall(singlehf* p){
    printf("\nFull singly list display");
    singlef* t=p->head;
    while(t){
        sfverh(p,t->valn);
        t=t->next;
    }
}

void cfdispall(singlehf* p){
    printf("\nFull circular list display");
    singlef* t=p->head;
    singlef* te=p->head;
    while(t){
        sfverh(p,t->valn);
        t=t->next;
        if(t==te)
            break;
    }
}

void dfdispall(doublehf* p){
    printf("\nFull doubly list display");
    doublef* t=p->head;
    while(t){
        dfverh(p,t->valn);
        t=t->next;
    }
}



//For deallocating Memory used by sp
void dealloc(modf* p){
    if(p==NULL)
        return;
    dealloc(p->mc[0]);
    dealloc(p->mc[1]);
    dealloc(p->mc[2]);
    dealloc(p->mc[3]);
    free(p);
}

void sfdealloc(singlehf* p){
    singlef* t=p->head;
    singlef* t2=t;

    while(t){
        dealloc(t->modp);
        t2=t;
        t=t->next;
        free(t2);
    }
    free(t);
    free(t2);

}

void cfdealloc(singlehf* p){
    singlef* t=p->head;
    singlef* te=p->head;
    singlef* t2=t;

    while(t){
        dealloc(t->modp);
        t2=t;
        t=t->next;
        if(t==te)
            break;
        free(t2);
    }
    free(t);
    free(t2);

}

void dfdealloc(doublehf* p){
    doublef* t=p->head;
    doublef* t2=t;

    while(t){
        dealloc(t->modp);
        t2=t;
        t=t->next;
        free(t2);
    }
    free(t);
    free(t2);

}

#endif
