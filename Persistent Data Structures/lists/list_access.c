#include<stdio.h>
#include "lists.h"

void singlypar();
void singlyfull();
void circlepar();
void circlefull();
void doublypar();
void doublyfull();


int main(){
    //singlypar();
    singlyfull();
    //circlepar();
    //circlefull();
    //doublypar();
    //doublyfull();
    return 0;
}

void doublypar(){
    print("\n Doubly partial persistent");
    doubleh list;
    dpinit(&list);

    //Inserting 2,4,6,8,10
    dpinend(&list,2);
    dpinend(&list,4);
    dpinend(&list,6);
    dpinend(&list,8);
    dpinend(&list,10);



    //MOdifying node 2->9 , then node 2->12, then node 3->14, then node 5->23
    dpinmod(&list,2,9);
    dpinmod(&list,2,12);
    dpinmod(&list,5,23);
    dpinmod(&list,3,14);
    dpinmod(&list,4,34);
    dpinmod(&list,5,37);

    //Inserting between nodes, inserting before node 4 and 5
    dpinbtw(&list,4,17);

    //MOdifying newly inserted node 5
    dpinmod(&list,5,26);

    //Displaying list of latest version
    dpdispl(&list);

    //Version history for node 2, and node 3
    printf("\nVersion history for pos = %d",2);
    dpverh(&list,2);
    printf("\nVersion history for pos = %d",3);
    dpverh(&list,3);

    //Deleting node 5, and showing it's version history
    dpdel(&list,5);
    printf("\nVersion history for pos = %d",5);
    dpverh(&list,5);

    //Deleting node 4, and showing it's version history
    dpdel(&list,4);
    printf("\nVersion history for pos = %d",4);
    dpverh(&list,4);

    printf("\nComplete list at latest modification");
    dpdispl(&list);
    printf("\nCurrent version = %d",list.vn);

    printf("\nFull list display ");
    dpdispall(&list);

    //Searching for some value and upto given version
    dpsearch(&list,6,13);
    dpsearch(&list,26,14);
    dpsearch(&list,23,4);

    //Deallocating all nodes
    dpdealloc(&list);
}

void circlepar(){
    print("\n Circular partial persistent");
    singleh list;
    spinit(&list);

    //Inserting 2,4,6,8,10
    cpinend(&list,2);
    cpinend(&list,4);
    cpinend(&list,6);
    cpinend(&list,8);
    cpinend(&list,10);

    //MOdifying node 2->9 , then node 2->12, then node 3->14, then node 5->23
    cpinmod(&list,2,15);
    cpinmod(&list,2,17);
    cpinmod(&list,5,29);
    cpinmod(&list,3,12);

    //Inserting between nodes, inserting before node 4 and 5
    cpinbtw(&list,4,17);

    //MOdifying newly inserted node 5
    cpinmod(&list,5,26);

    //Displaying list of latest version
    cpdispl(&list);

    //Deleting node 5, and showing it's version history
    //cpdel(&list,5);
    printf("\nVersion history for pos = %d",5);
    cpverh(&list,5);


    //Version history for node 2, and node 3
    printf("\nVersion history for pos = %d",2);
    cpverh(&list,2);
    printf("\nVersion history for pos = %d",3);
    cpverh(&list,3);

    //Deleting node 5, and showing it's version history
    cpdel(&list,5);
    printf("\nVersion history for pos = %d",5);
    cpverh(&list,5);

    printf("\nFull list display ");
    cpdispall(&list);


    //Searching for some value and upto given version
    cpsearch(&list,6,13);
    cpsearch(&list,26,12);
    cpsearch(&list,23,4);

    //Deallocating all nodes
    cpdealloc(&list);
}

void singlypar(){
    print("\n Singly partial persistent");
    singleh list;
    spinit(&list);

    //Inserting 2,4,6,8,10
    spinend(&list,2);
    spinend(&list,4);
    spinend(&list,6);
    spinend(&list,8);
    spinend(&list,10);



    //MOdifying node 2->9 , then node 2->12, then node 3->14, then node 5->23
    spinmod(&list,2,9);
    spinmod(&list,2,12);
    spinmod(&list,5,23);
    spinmod(&list,3,14);

    //Inserting between nodes, inserting before node 4 and 5
    spinbtw(&list,4,17);
    //MOdifying newly inserted node 5
    spinmod(&list,5,26);

    //Displaying list of latest version
    spdispl(&list);

    //Version history for node 2, and node 3
    spverh(&list,2);
    printf("\nVersion history for pos = %d",3);
    spverh(&list,3);

    //Deleting node 5, and showing it's version history
    spdel(&list,5);
    printf("\nVersion history for pos = %d",5);
    spverh(&list,5);

    //Deleting node 4, and showing it's version history
    spdel(&list,4);
    printf("\nVersion history for pos = %d",4);
    spverh(&list,4);

    spdispl(&list);
    printf("\nCurrent version = %d",list.vn);

    printf("\nFull list display ");
    spdispall(&list);

    //Searching for some value and upto given version
    spsearch(&list,6,13);
    spsearch(&list,26,12);
    spsearch(&list,23,4);

    //Deallocating all nodes
    spdealloc(&list);
}

void singlyfull(){
    print("\n Singly Full persistent");
    singlehf list;
    sfinit(&list);


    //Inserting 2,4,6,8,10
    sfinend(&list,2);
    sfinend(&list,4);
    sfinend(&list,6);
    sfinend(&list,8);
    sfinend(&list,10);

    //Inserting in between,after node 4 , before 5
    sfinbtw(&list,4,17);

    //Modifying at version v at given node ver,pos,value
    sfinmod(&list,2,2,9);
    sfinmod(&list,2,2,12);
    sfinmod(&list,5,6,23);
    sfinmod(&list,6,5,26);
    sfinmod(&list,5,6,28);
    sfinmod(&list,9,6,16);
    sfinmod(&list,2,2,18);
    sfinmod(&list,8,2,20);
    sfinmod(&list,8,2,22);
    //sfinmod(&list,2,2,18);
    //sfinmod(&list,2,2,9);*/

    //Version history for nodes
    sfverh(&list,2);
    sfverh(&list,6);

    //Deleting nodes with version
    sfdel(&list,6,9);
    sfdel(&list,4,4);
    sfdel(&list,2,13);

    //Searching for value within version
    sfsearch(&list,8,4);
    sfsearch(&list,23,17);
    sfsearch(&list,18,17);

    sfverh(&list,6);
    //Displaying list of latest version
    //sfdispl(&list);

    printf("\nCurrent version = %d  ",list.vn);
    //Full list display
    printf("\n\n");
    sfdispall(&list);

    //Deallocating all nodes
    sfdealloc(&list);
}

void circlefull(){
    print("\n Circular Full persistent");
    singlehf list;
    sfinit(&list);


    //Inserting 2,4,6,8,10
    cfinend(&list,2);
    cfinend(&list,4);
    cfinend(&list,6);
    cfinend(&list,8);
    cfinend(&list,10);

    //Inserting in between,after node 4 , before 5
    sfinbtw(&list,4,17);

    //Modifying at version v at given node ver,pos,value
    sfinmod(&list,2,2,9);
    sfinmod(&list,2,2,12);
    sfinmod(&list,5,6,23);
    sfinmod(&list,6,5,26);
    sfinmod(&list,5,6,28);
    sfinmod(&list,9,6,16);
    sfinmod(&list,2,2,18);
    sfinmod(&list,8,2,20);
    sfinmod(&list,8,2,22);
    sfinmod(&list,2,2,18);
    sfinmod(&list,2,2,9);

    //Version history for nodes
    sfverh(&list,2);
    sfverh(&list,6);

    //Deleting nodes with version
    sfdel(&list,6,9);
    sfdel(&list,4,4);
    sfdel(&list,2,13);

    //Searching for value within version
    cfsearch(&list,8,4);
    cfsearch(&list,23,17);
    cfsearch(&list,18,12);

    sfverh(&list,6);

    printf("\nCurrent version = %d  ",list.vn);
    //Full list display
    printf("\n\n");
    cfdispall(&list);

    //Deallocating all nodes
    cfdealloc(&list);
}

void doublyfull(){
    print("\n Doubly Full persistent");
    doublehf list;
    dfinit(&list);


    //Inserting 2,4,6,8,10
    dfinend(&list,2);
    dfinend(&list,4);
    dfinend(&list,6);
    dfinend(&list,8);
    dfinend(&list,10);

    //Inserting in between,after node 4 , before 5
    dfinbtw(&list,4,17);

    //Modifying at version v at given node ver,pos,value
    dfinmod(&list,2,2,9);
    dfinmod(&list,2,2,12);
    dfinmod(&list,5,6,23);
    dfinmod(&list,6,5,26);
    dfinmod(&list,5,6,28);
    dfinmod(&list,9,6,16);
    dfinmod(&list,2,2,18);
    dfinmod(&list,8,2,20);
    dfinmod(&list,8,2,22);
    dfinmod(&list,7,2,27);
    dfinmod(&list,8,2,41);

    //Version history for nodes
    dfverh(&list,2);
    dfverh(&list,6);

    //Deleting nodes with version
    dfdel(&list,6,9);
    dfdel(&list,4,4);
    dfdel(&list,2,13);

    //Searching for value within version
    dfsearch(&list,8,4);
    dfsearch(&list,23,17);
    dfsearch(&list,41,16);

    dfverh(&list,6);


    printf("\nCurrent version = %d  ",list.vn);
    //Full list display
    printf("\n\n");
    dfdispall(&list);

    //Deallocating all nodes
    dfdealloc(&list);
}
