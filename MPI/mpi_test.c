#include"mpi.h"
#include<stdio.h>
int main(int argc,char *argv[]){
  int numtasks,rank,rc;
  MPI_Comm new_comm;
  MPI_Group orig_group,new_group;
  rc=MPI_Init(&argc,&argv);
  if(rc!=MPI_SUCCESS){
    printf("Error starting MPI program.Terminating.\n");
    MPI_Abort(MPI_COMM_WORLD,rc);
  }
  MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_group(MPI_COMM_WORLD,&orig_group);
  int rank1[4]={0,1,2,3},rank2[4]={4,5,6,7};
  if(rank<numtasks/2) MPI_Group_incl(orig_group,numtasks/2,rank1,&new_group);
  else MPI_Group_incl(orig_group,numtasks/2,rank2,&new_group);
  MPI_Comm_create(MPI_COMM_WORLD,new_group,&new_comm);
  MPI_Barrier(new_comm);
  printf("Number of tasks=%d My rank=%d\n",numtasks,rank);
  MPI_Finalize();
  return 0;
}

