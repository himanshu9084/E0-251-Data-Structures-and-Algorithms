#include<stdio.h>
#include "sqheader.h"

void pstack();
void fstack();
void pqueue();
void fqueue();
void pdq();
void fdq();

int main(){
    //pstack();
    fstack();
    //pqueue();
    //fqueue();
    //pdq();
    //fdq();
    return 0;
}

void pstack(){
    print("\nStack partial persistent");
    singleh st;
    psinit(&st);

    //Push pop allowed only for latest version
    //5 push operations
    pspush(&st,21);
    pspush(&st,27);
    pspush(&st,38);
    pspush(&st,45);
    pspush(&st,54);

    //Displaying stack
    printf("\nStack display");
    psdisp(&st);

    //2 pop operations
    pspop(&st);
    pspop(&st);
    pspush(&st,68);

    //Displaying stack
    printf("\n\nStack display");
    psdisp(&st);
    print("\n");
}

void fstack(){
    print("\nStack full persistent");
    modt st;
    fsinit(&st);

    //push into latest version
    fspush(&st,4);
    fspush(&st,14);
    fspush(&st,42);
    fspush(&st,44);

    //Display stack at version 4
    printf("\n");
    fsdisp(&st,4);

    //push at version
    fspushat(&st,25,2);
    fspushat(&st,34,5);
    fspushat(&st,39,1);
    fspushat(&st,33,7);

    //Display stack at version 8
    printf("\n");
    fsdisp(&st,8);

    //popping version 4 of stack
    fspop(&st,4);

    //Display stack at version 4
    printf("\n");
    fsdisp(&st,9);

    //push at version after deleting
    fspushat(&st,87,3);
    fspushat(&st,74,10);

    //Display stack after deleting version 4
    printf("\n");
    fsdisp(&st,11);
    print("\n");

}

void pdq(){
    print("\nDouble ended partial persistent");
    doubleh dq;
    pdqinit(&dq);

    //3 push front
    pdqinfront(&dq,12);
    pdqinfront(&dq,21);
    pdqinfront(&dq,23);

    //3 push at rear
    pdqatrear(&dq,74);
    pdqatrear(&dq,68);
    pdqatrear(&dq,45);

    //Displaying latest versions
    pdqdisp(&dq);

    //Delete at front
    pdqfrdel(&dq);

    //Delete at rear
    pdqredel(&dq);

    //Displaying latest versions
    printf("\n");
    pdqdisp(&dq);
    print("\n");

}

void fdq(){
    print("\nDouble ended full persistent");
    modt dq;
    fdqinit(&dq);

    //Insert in front for 1st version
    fdqinfr(&dq,13,0);
    fdqinfr(&dq,14,1);
    fdqinfr(&dq,4,2);
    //fdqinfr(&dq,6,3);

    //Printing in reverse order, rear->front
    //fdqdisp(&dq,1);

    //Insert in rear for 1st version
    fdqinre(&dq,18,1);
    fdqinre(&dq,22,1);
    fdqinre(&dq,20,4);

    //Inserting at both
    fdqinfr(&dq,6,3);
    fdqinre(&dq,19,2);

    //Printing in reverse order, rear->front
    fdqdisp(&dq,8);

    //Deleting one at rear, front of version
    fdqdelfr(&dq,5);
    fdqdelre(&dq,5);

    //Printing in reverse order, rear->front
    fdqdisp(&dq,6);

    //Printing in reverse order, rear->front
    fdqdisp(&dq,5);
    print("\n");
}

void pqueue(){
    print("\nQueue partial persistent");
    doubleh q;
    pdqinit(&q);

    //Insert at front
    pdqinfront(&q,4);
    pdqinfront(&q,15);
    pdqinfront(&q,60);
    pdqinfront(&q,70);
    pdqinfront(&q,80);

    //Delete at rear
    pdqredel(&q);
    pdqredel(&q);

    //Insert front
    pdqinfront(&q,90);

    //Display
    printf("\nfront");
    pdqdisp(&q);
    print("\n");
}

void fqueue(){
    print("\nQueue full persistent");
    modt q;
    fdqinit(&q);

    //Insert in front for 1st version
    fqinfr(&q,13,0);
    fqinfr(&q,14,1);
    fqinfr(&q,4,2);
    fqinfr(&q,6,3);
    fqinfr(&q,8,4);

    //Printing in reverse order, rear->front
    fdqdisp(&q,5);

    //Deleting one at rear
    fdqdelre(&q,5);

    //Printing in reverse order, rear->front
    fdqdisp(&q,5);

    print("\n");

}
