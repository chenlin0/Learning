#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"mpi.h"
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(id,p,n) (((p)*((index)+1)-1)/(n))
#define MIN(a,b) (((a)<(b))?(a):(b))
int main(int argc,char *argv[]){
    int count;//local prime count
    double elapsed_time;//Parallel execution time
    int first;//Index of first mutiple
    int global_count;//global prime count
    int high_value;//Highest value on this proc
    int i;
    int index;//Index of current prime
    int id;//Process ID number
    int low_value;//the lowest value of this proc
    char *marked;//Position of 2,...,n
    int size;//Elements in marked
    int n;//Sieving from 2,...,n
    int p;//number of processes
    int proc0_size;//Size of proc 0's subarray
    int prime;//Current prime
    MPI_Init(&argc,&argv);
    /*start the time*/
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time=MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    if(argc!=2){
        printf("Errors");
        MPI_Finalize();
        exit(1);
    }
    n=atoi(argv[1]);
    // 每一个进程处理的最小最大自然数,自然数个数
    low_value=2+BLOCK_LOW(id,p,n-1);
    high_value=2+BLOCK_HIGH(id,p,n-1);
    size=BLOCK_SIZE(id,p,n-1);
    proc0_size=(n-1)/p;
    if((2+proc0_size)<(int)sqrt((double)n)){
        if(!id){
            printf("(2+proc0_size)>(int)sqrt((double)n)\n");
            MPI_Finalize();
            exit(1);
        }
    }
    marked=(char*)malloc(size*sizeof(char));
    if(marked==NULL){
        printf("Can't allocate enough memory\n");
        MPI_Finalize();
        exit(1);
    }
    for(i=0;i<size;++i) marked[i]=0;
    if(!id) index=0;
    prime=2;
    do{
        if(prime*prime>low_value) first=prime*prime-low_value;
        else if(!(low_value%prime)) first=0;
        else first=prime-(low_value%prime);
        for(i=first;i<size;i+=prime) marked[i]=1;
        if(!id){
            while(marked[++index]);
            prime=index+2;//marked[0]对应自然数2
        }
        MPI_Bcast(&prime,1,MPI_INT,0,MPI_COMM_WORLD);
    }while(prime*prime<=n);
    count=0;
    for(i=0;i<size;++i){
        if(!marked[i]){
            count++;
            printf("%d ",i+low_value);
        }
    }
    MPI_Reduce(&count,&global_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    elapsed_time=MPI_Wtime()-elapsed_time;
    if(!id){
        printf("the number of prime: %d\n",global_count);
        printf("running time:%lf\n",elapsed_time);
    }
    MPI_Finalize();
    return 0;
}