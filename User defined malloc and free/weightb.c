#include <stdio.h>
#include <stdlib.h>
#include "weigth.h"

void initialize();

int main(){
    printf("%d",ispow(24));
    initialize();
    print("\n");
}

void initialize(){
    mem=(void*)malloc(sizeof(msize));
    printf("%p  %ld",mem,sizeof(mem));
    //printf("\n%d",(int)mem*2);
    avail fd;
    init(&fd);

    //void* c=(void*)bmalloc(&fd,5);
    char* c=(char*)bmalloc(&fd,sizeof(char));
    printf("\nValue =  %p",c);
    printdat(&fd);

    //void* fin=(void*)bmalloc(&fd,3);
    //printf(" %d",reqsize(1));
    //printf(" %d",bsizearr(2));
    int* x=(int*)bmalloc(&fd,sizeof(int));
    printf("\nValue = %p  %ld",x,sizeof(int));
    printdat(&fd);
    //printf("\n%d",sizeof(char));
    bfree(&fd,c);
    printdat(&fd);
    bfree(&fd,x);
    printdat(&fd);

    char* d=(char*)bmalloc(&fd,sizeof(char));
    printdat(&fd);
    /*bmalloc(&fd,8);


    bmalloc(&fd,3);
    float* x1=(float*)bmalloc(&fd,sizeof(float));
    if(x1!=NULL)
        *x1=2.654;
    printf("\nValue = %f  ",*x1);
    bfree(&fd,x1);
    //printf("\n%d",ispow(3));
    //printf("%d",splitter(32,2));
    */
    free(mem);
}
