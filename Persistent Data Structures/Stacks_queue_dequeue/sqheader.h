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
    struct doubly* fr;
    struct doubly* re;
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
struct mods* next;
int ver;
};
typedef struct mods mods;

struct modt{
    struct modf* head;
    int vn;
};
typedef struct modt modt;

struct modf{
    int type;
    int val;
    struct modf* pr;
    struct modf* mc[4];
    int ver;
};
typedef struct modf modf;


//Stack
//For initializing partially persistent stack
void psinit(singleh* p){
    p->head=NULL;
    p->vn=1;
}

//For pushing into stacks, partial
void pspush(singleh* p,int x){
    single* t=allocate(single);

    if(p->head==NULL)
        t->valn=1;
    else
        t->valn=(p->head->valn)+1;
    t->next=p->head;
    t->modp=allocate(mods);
    t->modp->type=0;
    t->modp->val=x;
    t->modp->next=NULL;
    t->modp->ver=(p->vn)++;
    p->head=t;
}

//For poping into stacks, partial
void pspop(singleh* p){
    single* t=p->head;
    mods* t2=allocate(mods);
    t2->type=3;
    t2->ver=(p->vn)++;
    while(t){
        if(t->modp->type!=3)
            break;
        t=t->next;
    }

    if(t->valn==1)
        printf("\nStack empty");
    else{
    t2->val=t->modp->val;
    t2->next=t->modp;
    t->modp=t2;
    }
}

//For stack disp only latest version
void psdisp(singleh* p){
    single* t=p->head;
    if(t==NULL)
        printf("Stack empty");
    else
    while(t){
        printf("\n%d->%d ver=%d",t->valn,t->modp->val,t->modp->ver);
        if(t->modp->type==3)
            printf(" Deleted");
        t=t->next;
    }
}


//Dequeue
//partial initialization
void pdqinit(doubleh* p){
    p->fr=NULL;
    p->re=NULL;
    p->vn=1;
}

//pushing at front
void pdqinfront(doubleh* p, int x){
    doubly* t=allocate(doubly);
    mods* ml=allocate(mods);
    ml->type=0;
    ml->val=x;
    ml->next=NULL;
    ml->ver=(p->vn)++;

    if(p->fr==NULL){
        p->fr=t;
        p->re=t;
        t->valn=1;
        t->modp=ml;
        t->prev=NULL;
        t->next=NULL;
    }
    else{
        t->next=p->fr;
        p->fr->prev=t;
        p->fr=t;
        t->valn=t->next->valn+1;
        t->prev=NULL;
        t->modp=ml;
    }
}

//Insert at rear,dq partial
void pdqatrear(doubleh* p, int x){
    doubly* t=allocate(doubly);
    mods* ml=allocate(mods);
    ml->type=0;
    ml->val=x;
    ml->next=NULL;
    ml->ver=(p->vn)++;

    if(p->re==NULL){
        p->fr=NULL;
        p->re=NULL;
        t->valn=1;
        t->prev=NULL;
        t->next=NULL;
    }
    else{
        t->prev=p->re;
        p->re->next=t;
        p->re=t;
        t->next=NULL;
        t->valn=t->prev->valn+1;
    }
    t->modp=ml;
}

//Delete at front
void pdqfrdel(doubleh* p){
    doubly* t=p->fr;
    mods* ml=allocate(mods);
    ml->type=3;
    ml->val=t->modp->val;
    ml->next=t->modp;
    t->modp=ml;
    ml->ver=(p->vn)++;
}

//Delete at rear
void pdqredel(doubleh* p){
    doubly* t=p->re;
    mods* ml=allocate(mods);
    ml->type=3;
    ml->val=t->modp->val;
    ml->next=t->modp;
    t->modp=ml;
    ml->ver=(p->vn)++;
}

//For display of whole dq
void pdqdisp(doubleh* p){
    doubly* t=p->fr;
    while(t){
        printf("\n%d ver=%d",t->modp->val,t->modp->ver);
        if(t->modp->type==3)
            printf(" Deleted");
        t=t->next;
    }
}




//Initializing fully modf mc array
void sfpoint4(modf* p){
    p->mc[0]=NULL;
    p->mc[1]=NULL;
    p->mc[2]=NULL;
    p->mc[3]=NULL;
    //printf("hi");
}

modf* inslat(modf* p){
    if(p==NULL)
        return NULL;
    else if(p->mc[0]==NULL)
        return p;
    else
        return inslat(p->mc[0]);
}

modf* sertr(modf* p,int ver){
    modf* ml=NULL;
    if(p==NULL)
        return NULL;
    if(p->ver==ver)
        return p;
    else{
        ml=sertr(p->mc[0],ver);
        if(ml==NULL)
            ml=sertr(p->mc[1],ver);
        if(ml==NULL)
            ml=sertr(p->mc[2],ver);
        if(ml==NULL)
            ml=sertr(p->mc[3],ver);
        return ml;
    }
}

//fully persistent stack
void fsinit(modt* p){
    p->head=NULL;
    p->vn=1;
}

//push into latest version, stack full
void fspush(modt* p, int x){
    modf* t=allocate(modf);
    if(p->head==NULL){
        p->head=t;
        t->type=0;
        t->pr=NULL;
        t->val=x;
        t->ver=(p->vn)++;
        sfpoint4(t);
    }
    else{
        modf* t2=p->head;
        t2=inslat(t2);
        //printf("%u ",t2);
        t2->mc[0]=t;
        t->type=0;
        t->val=x;
        t->pr=t2;
        t->ver=(p->vn)++;
        sfpoint4(t);
    }
}

//push into stack at version
void fspushat(modt* p, int x, int ver){
    modf* t=p->head;

    //printf("%d ",t->val);
    modf* t2=allocate(modf);
    t2->val=x;
    t2->type=0;
    sfpoint4(t2);
    t2->ver=(p->vn)++;
    t=sertr(t,ver);
    if(t->mc[0]==NULL)
        t->mc[0]=t2;
    else if(t->mc[1]==NULL)
        t->mc[1]=t2;
    else if(t->mc[2]==NULL)
        t->mc[2]=t2;
    else if(t->mc[3]==NULL)
        t->mc[3]=t2;
    t2->pr=t;

    /*printf("%d ",t2->pr->val);
    printf("%d ",t->mc[1]->val);*/
}

//Popping from a stack
void fspop(modt* p, int ver){
    modf* t=p->head;
    t=sertr(t,ver);
    modf* t2=allocate(modf);
    t2->type=3;
    t2->ver=(p->vn)++;
    t2->val=t->val;
    sfpoint4(t2);

    if(t->mc[0]==NULL)
        t->mc[0]=t2;
    else if(t->mc[1]==NULL)
        t->mc[1]=t2;
    else if(t->mc[2]==NULL)
        t->mc[2]=t2;
    else if(t->mc[3]==NULL)
        t->mc[3]=t2;
    t2->pr=t->pr;

}

//Display Stack at version
void fsdisp(modt* p, int ver){
    modf* t=p->head;
    t=sertr(t,ver);
    //printf("%d ",t->val);
    while(t){
        printf("\n%d ver=%d",t->val,t->ver);
        if(t->type==3)
            printf(" Deleted");
        t=t->pr;
    }
}



//Fully persistent dequeue
void fdqinit(modt* p){
    p->head=NULL;
    p->vn=1;
}

//Insert at front dq
void fdqinfr(modt* p,int x, int ver){
    modf* t=allocate(modf);
    t->type=0;
    t->val=x;
    sfpoint4(t);
    t->ver=(p->vn)++;

    if(ver==0){
        p->head=t;
        t->pr=NULL;
    }
    else{
        modf* t2=sertr(p->head,ver);
        t->mc[0]=t2;
        p->head=t;
        t->pr=NULL;
        t2->pr=t;
    }
}

//Insert at front queue
void fqinfr(modt* p,int x, int ver){
    modf* t=allocate(modf);
    t->type=0;
    t->val=x;
    sfpoint4(t);
    t->ver=(p->vn)++;

    if(ver==0){
        p->head=t;
        t->pr=NULL;
    }
    else{
        modf* t2=sertr(p->head,ver);
        t->pr=t2;
        t2->mc[0]=t;
    }
}


//Insert at rear of ver
void fdqinre(modt* p,int x, int ver){
    modf* t=p->head;
    t=sertr(t,ver);
    //printf("%d ", t->val);
    modf* t2=allocate(modf);
    t2->type=0;
    t2->val=x;
    sfpoint4(t2);
    t2->ver=(p->vn)++;

    if(t->mc[0]==NULL)
        t->mc[0]=t2;
    else if(t->mc[1]==NULL)
        t->mc[1]=t2;
    else if(t->mc[2]==NULL)
        t->mc[2]=t2;
    else if(t->mc[3]==NULL)
        t->mc[3]=t2;
    t2->pr=t;
}

int delch(modf* t){
    if(t==NULL)
        return 0;
    if(t->mc[0]!=NULL)
    if(t->mc[0]->type==3)
        return 1;

    if(t->mc[1]!=NULL)
    if(t->mc[1]->type==3)
        return 1;

    if(t->mc[2]!=NULL)
    if(t->mc[2]->type==3)
        return 1;

    if(t->mc[3]!=NULL)
    if(t->mc[3]->type==3)
        return 1;
    return 0;
}

//Delete at front
void fdqdelfr(modt* p, int ver){
    modf* t=p->head;
    t=sertr(t,ver);
    while(t->pr){
        t=t->pr;
    }
    //printf("%d ",t->val);
    modf* t2=allocate(modf);
    sfpoint4(t2);
    t2->ver=(p->vn)++;
    t2->type=3;
    t2->pr=t;
    t2->val=t->val;

    if(t->mc[0]==NULL)
        t->mc[0]=t2;
    else if(t->mc[1]==NULL)
        t->mc[1]=t2;
    else if(t->mc[2]==NULL)
        t->mc[2]=t2;
    else if(t->mc[3]==NULL)
        t->mc[3]=t2;
}

//Deleting at rear, fqd
void fdqdelre(modt* p, int ver){
    modf* t=p->head;
    t=sertr(t,ver);

    modf* t2=allocate(modf);
    sfpoint4(t2);
    t2->ver=(p->vn)++;
    t2->type=3;
    t2->pr=t;
    t2->val=t->val;

    if(t->mc[0]==NULL)
        t->mc[0]=t2;
    else if(t->mc[1]==NULL)
        t->mc[1]=t2;
    else if(t->mc[2]==NULL)
        t->mc[2]=t2;
    else if(t->mc[3]==NULL)
        t->mc[3]=t2;
}


//Display dq at version
void fdqdisp(modt* p, int ver){
    modf* t=p->head;
    t=sertr(t,ver);
    //printf("%d ",t->val);
    printf("\nrear");
    while(t){
        printf("\n%d ver=%d",t->val,t->ver);
        if(delch(t))
            printf(" Deleted");
        t=t->pr;
    }
    printf("\nfront");
}





#endif
