/* "matrix diagonalization using scalapack" */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* PDSYEVD prototype */
extern void pdsyevd_(char *jobz,char *uplo,int *n,double *a,int *ia,int *ja,int *desca,double *w,double *z,int *iz,int *jz,int *descz,double *work,int *lwork,double *iwork,int *liwork,int *info);
#define n 4
int main(int argc, char *argv[])
{
  int numprocs,myid,i,j,k,index,info,lwork,liwork,N;
  int ia,ja,desca[n];
  int iz,jz,descz[n];
  double A[n][n],w[n];
  double *a,*z,*work,*iwork;

  /* set up  MPI stuff */
  MPI_Init(&argc,&argv);                    // initialize MPI
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);  // find out size of world
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);      // determine current mpi proc id

  /* initialize matrices */
  for(i=0;i<n;i++) { for(j=0;j<n;j++) A[i][j] = (i+j); }

  /* determine submatrices */

  /* let's use square blocks, of equal size:
     there number of processors (mp^2) should be
      - square (mp^2 = 1,2,4,9,16,..)
      - with mp being a divisor of n

     In case we have 4 procs and a 4x4 matrix for example

         (A11  A12  A13  A14)
         (A21  A22  A23  A24)
     A = (A31  A32  A33  A34)
         (A41  A42  A43  A44)

         ( a1  a2 )
       = ( a3  a3 )

     where      (A11  A12)
           a1 = (A21  A22)

     is the submatrix sent to process 1 for example 

    in this case :
      n=4
      nprocs=4 --> mp=2
      len = 2
    */

  int mp = sqrt(numprocs);
  if(numprocs!=mp*mp) {printf("ERROR: numprocs (%d) should be square.\n",numprocs); return 1; }
  if(n%mp!=0) {printf("ERROR: mp (%d) should be divisor of n (%d).\n",mp,n); return 1; }
  int len = n/mp;
  a = malloc((n*n+1)*sizeof(double));
  z = malloc((n*n+1)*sizeof(double));
  //a = malloc((len*len+1)*sizeof(double));
  //z = malloc((len*len+1)*sizeof(double));

  ia=(myid*len)%n; // from 0 to n in steps of len
  ja=(int)(myid/mp)*len;
  printf("proc %d has a submatrix of size %d, with starting indices (%d,%d)\n",myid,len,ia,ja);

  iz=ia;
  jz=ja;

  for(i=ia;i<ia+len;i++) { for(j=ja,k=0;j<ja+len;j++,k++) a[k]=A[i][j]; }
  for(i=iz;i<iz+len;i++) { for(j=jz,k=0;j<jz+len;j++,k++) z[k]=A[i][j]; }

  /* diagonalize */
  N=n;  lwork=n*n;  liwork=n*n;  info=0;
  work = malloc(lwork*sizeof(double));
  iwork = malloc(liwork*sizeof(double));

  for(i=0;i<n;i++) { for(j=0;j<n;j++) a[i+j*n]=A[i][j]; }
  pdsyevd_("V","U",&len,a,&ia,&ja,desca,w,z,&iz,&jz,descz,work,&lwork,iwork,&liwork,&info);
  if(!myid)printf("info = %d\n",info);

  /* gather & print results */
  double wf[n];
  MPI_Reduce(w,wf,n,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  if(myid==0) {
    for(i=0;i<n;i++) {
      printf("wf[%d] = %8.4f  | v[%d] = [ ",i,wf[i],i);
      for(j=0;j<n;j++) printf("%6.2f ",a[j+i*n]);
      printf("]\n");
    }
  }

  free(a); free(z); free(work); free(iwork);

  /* clean up */
  MPI_Finalize(); /* MPI Programs end with MPI Finalize; this is a weak synchronization point */
  return 0;
}