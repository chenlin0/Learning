#include<stdio.h>
#include"mpi.h"
int main(int argc,char **argv){
    int rank,value,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    do{
        if(rank==0){//主进程
            printf("\nPlease give new value=");
            fflush ( stdout ) ;
            scanf("%d",&value);
            printf("%d read<-<- (%d)\n",rank,value);
            fflush ( stdout ) ;
            if(size>1){//向下一个进程传递该数据
                MPI_Send(&value,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
                printf("%d send (%d)->-> %d\n",rank,value,rank+1);
                fflush ( stdout ) ;
            }
        }
        else{//其他进程
            MPI_Recv(&value,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
            printf("%d receive (%d)<-<- %d\n",rank,value,rank-1);
            fflush ( stdout ) ;
            if(rank<size-1){
                MPI_Send(&value,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
                printf("%d send (%d)->-> %d\n",rank,value,rank+1);
                fflush ( stdout ) ;
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);//同步
    }while(value>=0);
    MPI_Finalize();
    return 0;
}