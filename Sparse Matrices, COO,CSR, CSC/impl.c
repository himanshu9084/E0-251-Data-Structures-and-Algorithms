#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "header.h"





void push(struct node** start, int npos, int ndata){
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
    newnode->pos  = npos;
    newnode->data  = ndata;
    newnode->next = *start;
    *start    = newnode;
}




int coogenerate(){
    int m,n;
    printf("Enter matrix dimensions m rows and n columns ");
    scanf("%d %d",&m,&n);

    if(m==0 || n==0){
	printf("Wrong input\n");
	exit(0);
    }
    int tot=m*n,i;

    float nzden,negden;
    printf("\nEnter non zero density ");
    scanf("%f",&nzden);
    if(nzden>100)
        nzden=nzden/10;
    if(nzden==0){
	printf("Zero matrix \n");
	exit(0);
    }

    printf("\nEnter -ve numbers density ");
    scanf("%f",&negden);
    if(negden>100)
        negden=negden/10;

    int nzdennum,negdennum;
    nzdennum=(tot)*(nzden/100);
    negdennum=(nzdennum)*(negden/100);
    int rows[nzdennum],col[nzdennum], data[nzdennum];

    input(m,n,rows,col,data,nzdennum,negdennum);

    /*printf("\n COO Row sorted Format ");
    for(i=0 ; i<nzdennum ; i++){
        printf("\n%d %d  %d ",rows[i],col[i],data[i]);
    }*/

    int size=nzdennum;
    int rcsr[m+1];
    printf("\nConvert to CSR ");
    cootocsr(m,n,rows,size,rcsr);

    int row1[nzdennum], col1[nzdennum], data1[size];
    for(i=0 ; i<size ; i++)
        row1[i]=rows[i];

    for(i=0 ; i<size ; i++)
        col1[i]=col[i];

    for(i=0 ; i<size ; i++)
        data1[i]=data[i];
    int ccsc[n+1];
    printf("\nConvert to CSC ");
    cootocsc(m,n,row1,col1,data1,size,ccsc);

    printf("\n \nPrint options <20x20 COO-1, CSR-2, CSC-3 \nCSC transform-4 \n");
    int choice;
    scanf("%d",&choice);
    switch(choice){
        case 1:
            printmatrix(m,n,rows,col,data,size,1);
            break;
        case 2:
            printmatrix(m,n,rcsr,col,data,size,2);
            break;
        case 3:
            printmatrix(m,n,row1,ccsc,data1,size,3);
            break;
        case 4:
            csctrans(m,n,row1,ccsc,data1,size);
            break;
        default : printf("Wrong choice ");
            break;
    }
}






int input(int m, int n,int rows[], int col[], int data[], int nzdennum,int negdennum ){

    printf("\n%d  %d\n", nzdennum,negdennum );

    //int rows[nzdennum],col[nzdennum], data[nzdennum];
    int tot=m*n;
    int k=0,i,neglim=0;
    bool full[tot];
    for(i=0 ; i<tot ; i++){
        full[i]=0;
    }

    srand(time(0));
    while(k<nzdennum){
        int a=rand()%(tot);
        if(!full[a]){
            full[a]=1;
            data[k]=rand()%(10)+1;
            k++;
        }
    }
    //printf("\n");

    /*for(i=0 ; i<tot ; i++){
        printf("%d  ",full[i]);
        if(i%n == n-1 )
            printf("\n");
    }*/

    k=0;
    for(i=0 ; i<tot ; i++){
        if(full[i]!=0){
            rows[k]=i/n;
            col[k]=i%n;
            k++;
        }
    }

    while(neglim<negdennum){
        int b=rand()%nzdennum;
        if(data[b]>0){
            data[b]=(-1)*data[b];
            neglim++;
        }
    }

    /*for(i=0 ; i<nzdennum ; i++){
        printf("\n%d %d  %d ",rows[i],col[i],data[i]);
    }

    */
    k=0;
    printf("\n Input matrix\n");
    for(i=0 ; i<tot ; i++){
        if(i%n==0 && i!=0)
            printf("; ");
        if(rows[k]*n+col[k]== i ){
            printf("%d ", data[k]);
            k++;
        }
        else
            printf("0 ");

    }

    printf("\n");

    //cootocsr(m,n,rows,col,data,nzdennum);
    //cootocsc(m,n,rows,col,data,nzdennum);
    //printmatrix(m,n,rows,col,data,nzdennum,1);

}






int cootocsr(int m, int n, int rows[],int size, int rcsr[]){

    int i;

    for(i=0 ; i<=m ; i++){
        rcsr[i]=0;
    }

    for(i=0 ; i<size ; i++){
        rcsr[rows[i]+1]++;
    }

    /*printf("\n");
    for(i=0 ; i<=m ; i++){
        printf(" %d ", rcsr[i]);
    }*/

    rcsr[0]=0;
    for(i=1 ; i<=m ; i++){
        rcsr[i]=rcsr[i-1]+rcsr[i];
    }

    printf("\n CSR Format");
    for(i=0 ; i<=m ; i++){
        printf(" %d ", rcsr[i]);
    }

    //printmatrix(m,n,rcsr,col,data,size,2);
}






int cootocsc(int m, int n, int rows[],int col[], int data[],int size, int ccsc[]){

    int i,k=0,min,j,temp1,temp2,temp3;

    for(i=0 ; i<size-1  ; i++){
        min=i;
        for(j=i+1 ; j<size ; j++){
            if(col[j]<col[min])
                min=j;
        }
        temp1=col[i];
        temp2=rows[i];
        temp3=data[i];
        col[i]=col[min];
        rows[i]=rows[min];
        data[i]=data[min];
        col[min]=temp1;
        rows[min]=temp2;
        data[min]=temp3;
    }

    for(i=0 ; i<=n ; i++){
        ccsc[i]=0;
    }

    for(i=0 ; i<size ; i++){
        ccsc[col[i]+1]++;
    }

    ccsc[0]=0;
    for(i=1 ; i<=n ; i++){
        ccsc[i]=ccsc[i-1]+ccsc[i];
    }

    for(i=0 ; i<n ; i++){
        sort(rows,(ccsc[i+1]-ccsc[i]),ccsc[i],data);
    }

    printf("\n CSC Format");
    for(i=0 ; i<=n ; i++){
        printf(" %d ", ccsc[i]);
    }

    /*printf("\n COO Col sorted Format ");
    for(i=0 ; i<size ; i++){
        printf("\n%d %d  %d ",rows[i],col[i],data[i]);
    }*/

    //printmatrix(m,n,rows,ccsc,data,size,3);

}





int sort(int rows[], int len, int st, int data[]){
    int min,i,j;
    int temp3,temp2;

    for(i=st ; i<st+len-1  ; i++){
        min=i;
        for(j=i+1 ; j<st+len ; j++){
            if(rows[j]<rows[min])
                min=j;
        }
        temp2=rows[i];
        temp3=data[i];
        rows[i]=rows[min];
        data[i]=data[min];
        rows[min]=temp2;
        data[min]=temp3;
    }

}





int generate2(){
    int m1,n1;
    printf("\nInsert first matrix CSC dimensions m1 rows and n1 columns ");
    scanf("%d %d",&m1,&n1);
    float nzden1,negden1;
    printf("\nEnter non zero density ");
    scanf("%f",&nzden1);
    if(nzden1==0){
	printf("Zero matrix \n");
	exit(0);
    }
    printf("\nEnter -ve numbers density ");
    scanf("%f",&negden1);

    int tot1=m1*n1;
    int nzdennum1,negdennum1;
    nzdennum1=(tot1)*(nzden1/100);
    negdennum1=(nzdennum1)*(negden1/100);

    int row1[nzdennum1],col1[nzdennum1], data1[nzdennum1];
    input(m1,n1,row1,col1,data1,nzdennum1,negdennum1);
    int size1=nzdennum1;
    int ccsc1[n1+1];
    cootocsc(m1,n1,row1,col1,data1,size1,ccsc1);



    int m2,n2;
    printf("\nInsert second matrix CSR dimensions m2 rows and n2 columns ");
    scanf("%d %d",&m2,&n2);

    if(n1!=m2){
        printf("Dimensions mismatch, no multiply");
        exit(0);
    }
    float nzden2,negden2;
    printf("\nEnter non zero density ");
    scanf("%f",&nzden2);
    if(nzden2==0){
	printf("Zero matrix, Result is zero matrix\n");
	exit(0);
    }

    printf("\nEnter -ve numbers density ");
    scanf("%f",&negden2);

    int tot2=m2*n2;
    int nzdennum2,negdennum2;
    nzdennum2=(tot2)*(nzden2/100);
    negdennum2=(nzdennum2)*(negden2/100);

    int row2[nzdennum2],col2[nzdennum2], data2[nzdennum2];
    input(m2,n2,row2,col2,data2,nzdennum2,negdennum2);
    int size2=nzdennum2;
    int rcsr2[m2+1];
    cootocsr(m2,n2,row2,size2,rcsr2);

    multiply(m1,n1,m2,n2,row1,ccsc1,data1,size1,rcsr2,col2,data2,size2);

}






int multiply(int m1, int n1, int m2, int n2, int row1[], int ccsc1[], int data1[], int size1, int rcsr2[], int col2[], int data2[], int size2){
    int i,j,k=0;
    int col1[size1];
    int row2[size2];
    int tot3=m1*n2;


    for(i=0 ; i<n1 ; i++){
            ccsc1[i]=ccsc1[i+1]-ccsc1[i];
            //printf(" %d ", col[i]);
    }

    int l=0;
    for(i=0 ; i<n1 ; i++){
        while(ccsc1[i]--){
            col1[l++]=i;
        }
    }


    for(i=0 ; i<m2 ; i++){
        rcsr2[i]=rcsr2[i+1]-rcsr2[i];
    }

    l=0;
    for(i=0 ; i<m2 ; i++){
        while(rcsr2[i]--){
                row2[l++]=i;
        }
    }


    /*printf("\nCSC to COO Format \n");
    for(i=0 ; i<size1 ; i++){
            printf(" %d %d %d\n",row1[i],col1[i], data1[i]);
    }

    printf("\nCSR to COO Format \n");
    for(i=0 ; i<size2 ; i++){
        printf(" %d %d %d\n",row2[i],col2[i],data2[i]);
    }*/


    printf("\n");

    //for(i=0 ; i<tot3 ; i++)
        //full[i]=0;


    struct node* start=NULL;

    int len=0;
    for(i=0 ; i<size1 ; i++){
        for(j=0 ; j<size2 ; j++){
            if(col1[i]==row2[j]){
                push(&start,row1[i]*n2+col2[j],data1[i]*data2[j]);
                len++;
                //full[row1[i]*n2+col2[j]] += data1[i]*data2[j];
                //printf(" %d ",full[row1[i]*n2+col2[j]]);
            }
        }
    }

    int nrow[len],ndata[len];

    i=0;
    struct node *node=start;
    while(node != NULL){
        nrow[i]=node->pos;
        ndata[i]=node->data;
        //printf("%d  %d\n",nrow[i],ndata[i]);
        node = node->next;
        i++;
    }

    /*printf("\nBefore sorting\n");
    for(i=0 ; i<len ; i++){
        printf("%d  %d\n",nrow[i],ndata[i]);
    }*/

    sort(nrow,len,0,ndata);

    /*printf("\nAfter sorting\n");
    for(i=0 ; i<len ; i++){
        printf("%d  %d\n",nrow[i],ndata[i]);
    }*/

    int alen=0;
    for(i=0 ; i<len ; i++) {
        while (i < len - 1 && nrow[i]==nrow[i+1])
            i++;
        alen++;
    }

    //printf("\n%d\n", alen);

    int row3[alen],col3[alen],data3[alen];

    k=0;
    for(i=0 ; i<len-1 ; i++){
        if(nrow[i]!=nrow[i+1])
            row3[k++]=nrow[i];
    }
    row3[k++]=nrow[len-1];

    j=0;
    for(i=0 ; i<alen ; i++){
        col3[i]=row3[i]%n2;
        data3[i]=0;
        while(j<len && nrow[j]==row3[i]){
                data3[i]+=ndata[j];
                j++;
        }
        row3[i]=row3[i]/n2;
    }


    /*printf("\nRemoving duplicates\n");
    for(i=0 ; i<k ; i++){
        printf("%d  \n",row3[i],data3[i]);
    }*/

    printf("\nMultipy COO Row sorted Format ");
    for(i=0 ; i<alen ; i++){
        printf("\n%d %d  %d ",row3[i],col3[i],data3[i]);
    }

    int ch=0;
    printf("\nDo you want to print result in matrix structure, press 1\n");
    scanf("%d",&ch);
    if(ch)
        printmatrix(m1,n2,row3,col3,data3,alen,1);
    else
        exit(0);

}






int csctrans(int m, int n, int row[], int ccsc[], int data[], int size){
    int i,knz=0,size2=0,k=0;
    int col[size];

    for(i=0 ; i<n ; i++){
        ccsc[i]=ccsc[i+1]-ccsc[i];
    }

    int l=0;
    for(i=0 ; i<n ; i++){
        while(ccsc[i]--){
            col[l++]=i;
        }
    }

    int r1,k1,r2,k2;
    printf("\nEnter r1, k1, r2, k2\n");
    scanf("%d%d%d%d",&r1,&k1,&r2,&k2);

	r2=r2-1;
	r1=r1-1;

    if(r1 == r2 || r1>m || r2>m || r1==0 || r2==0){
    	printf("Wrong input \n");
	exit(0);
    }


    int prow[n];
    int nrow[n];

    for(i=0 ; i<n ; i++){
        prow[i]=0;
        nrow[i]=0;
    }


    for(i=0 ; i<size ; i++){
        if(row[i]==r2){
            nrow[col[i]]=k2*data[i];
            knz++;
        }
        if(row[i]==r1){
            prow[col[i]]=data[i];
        }
    }

    for(i=0 ; i<n ; i++){
        nrow[i]+=k1*prow[i];
    }

    printf("\n");
    for(i=0 ; i<n ; i++)
        printf(" %d ",nrow[i]);
    printf("\n");

    for(i=0 ; i<n ; i++){
        if(nrow[i]!=0)
            size2++;
    }

    int tr=0;
    if(size2>knz)
        tr=1;
    else
        tr=0;

    int size1=size;
    if(tr)
        size1+=(size2-knz);
    else
        size1-=(knz-size2);

    //printf("\n%d\n",size1);


    int j;
    k=0;
    int crow[size1],ccol[size1],cdata[size1];

    for(i=0 ; i<size ; i++){
        if(row[i]!=r2){
            ccol[k]=col[i]*n+row[i];
            cdata[k]=data[i];
            k++;
        }
    }

    for(i=0 ; i<n ; i++){
        if(nrow[i]!=0){
            ccol[k]=i*n+r2;
            cdata[k]=nrow[i];
            k++;
        }
    }

    sort(ccol,size1,0,cdata);

    printf("\nCOO CSC Format \n");
    for(i=0 ; i<size1 ; i++){
        crow[i]=ccol[i]%n;
        ccol[i]=ccol[i]/n;
        printf(" %d %d %d\n",crow[i],ccol[i],cdata[i]);
    }

    int cccsc[n+1];
    cootocsc(m,n,crow,ccol,cdata,size1,cccsc);
}






int printmatrix(int m, int n, int rows[], int col[], int data[], int size, int type){
    int tot=m*n,i,j;
    int row1[m];
    int col1[n];

    printf("\n");
    if(m<=20 && n<=20){
    if(type==2){
        for(i=0 ; i<m ; i++){
            rows[i]=rows[i+1]-rows[i];
            //printf(" %d ", rows[i]);
        }

        int l=0;
        for(i=0 ; i<m ; i++){
            while(rows[i]--){
                row1[l++]=i;
            }
        }

        /*printf("\nCSR to COO Format \n");
        for(i=0 ; i<size ; i++){
            printf(" %d ",row1[i]);
        }*/

        printf("\n CSR Format Full matrix \n");
        int k=0;
        for(i=0 ; i<tot ; i++){
            if(i%n == 0 && i!=0)
                printf("\n");

            if(i == row1[k]*n+col[k]){
                printf("%4d",data[k]);
                k++;
            }
            else
                printf("%4d",0);
        }
    }
    else if(type==3){
        printf("\n");
        for(i=0 ; i<n ; i++){
            col[i]=col[i+1]-col[i];
            //printf(" %d ", col[i]);
        }

        int l=0;
        for(i=0 ; i<n ; i++){
            while(col[i]--){
                col1[l++]=i;
            }
        }

        int k=0;

        for(i=0 ; i<size ; i++){
            rows[i]=rows[i]*n+col1[i];
        }

        sort(rows,size,0,data);

        for(i=0 ; i<size ; i++){
            col1[i]=rows[i]%n;
            rows[i]=rows[i]/n;
        }

        printf("\n COO Format Full matrix \n");
        k=0;
        for(i=0 ; i<tot ; i++){
            if(i%n == 0 && i!=0)
                printf("\n");

            if(i == rows[k]*n+col1[k]){
                printf("%4d",data[k]);
                k++;
            }
            else
                printf("%4d",0);
        }
    }
    else if(type==1){
    printf("\n COO Format Full matrix \n");
    int k=0;
    for(i=0 ; i<tot ; i++){
        if(i%n == 0 && i!=0)
            printf("\n");

        if(i == rows[k]*n+col[k]){
            printf("%4d",data[k]);
            k++;
        }
        else
            printf("%4d",0);
    }
    }
    }
    else
        printf("Wrong type");
}
