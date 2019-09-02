#define N 100000
#include "mpi.h"
#include<stdio.h>
#include<math.h>
int main(int argc,char*argv[]){
    double local=0.0,pi,w,temp=0.0;
    int i,rank,size;
    w=1.0/N;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    for(i=rank;i<N;i+=size){
        temp=(i+0.5)*w;
        local+=4.0/(1.0+temp*temp);
    }
    MPI_Reduce(&local,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("pi is %lf\n",pi*w);
    }
    MPI_Finalize();
    return 0;
}