#include<iostream>
#include"mpi.h"
#include<unistd.h>
using namespace std;
int main(int argc,char** argv){
    int err=0;
    double t1,t2,tick;
    int i;
    MPI_Init(&argc,&argv);
    t1=MPI_Wtime();
    t2=MPI_Wtime();
    if(t2-t1>0.1||t2-t1<0.0){
        err++;
        cout<<"error"<<endl;
    }
    for(i=0;i<10;i++){
        t1=MPI_Wtime();
        sleep(1);
        t2=MPI_Wtime();
        if(t2-t1>=(1.0-0.01)&& t2-t1<=5.0){
            break;
        }
        if(t2-t1>5.0){
            i=9;
        }
    }
    if(i==10){
        cerr<<"sleep(1) !=1 s"<<endl;
        err++;
    }
    tick=MPI_Wtick();
    if(tick>1.0||tick<0.0){
        err++;
        cerr<<"MPI_Wtick !=1s"<<endl;
    }
    MPI_Finalize();
    return 0;
}
