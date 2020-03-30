/*
********************************************************************************
*   Copyright(C) 2004-2011 Intel Corporation. All Rights Reserved.
*   
*   The source code, information  and  material ("Material") contained herein is
*   owned  by Intel Corporation or its suppliers or licensors, and title to such
*   Material remains  with Intel Corporation  or its suppliers or licensors. The
*   Material  contains proprietary information  of  Intel or  its  suppliers and
*   licensors. The  Material is protected by worldwide copyright laws and treaty
*   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
*   modified, published, uploaded, posted, transmitted, distributed or disclosed
*   in any way  without Intel's  prior  express written  permission. No  license
*   under  any patent, copyright  or  other intellectual property rights  in the
*   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
*   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
*   intellectual  property  rights must  be express  and  approved  by  Intel in
*   writing.
*   
*   *Third Party trademarks are the property of their respective owners.
*   
*   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
*   this  notice or  any other notice embedded  in Materials by Intel or Intel's
*   suppliers or licensors in any way.
*
********************************************************************************
*   Content : Simple MKL Matrix Multiply C example
*
********************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mkl.h"

void print_arr(int N, char * name, double* array);
void init_arr(int N, double* a);
void Dgemm_multiply(double* a,double*  b,double*  c, int N);


int main(int argc, char* argv[])
{
	clock_t start, stop;
	int i, j;
	int N;
	double* a;
	double* b;
	double* c;
	if(argc < 2)
	{
		printf("Enter matrix size N=");
		//please enter small number first to ensure that the 
		//multiplication is correct! and then you may enter 
		//a "reasonably" large number say like 500 or even 1000
		scanf("%d",&N);
	}
	else
	{
		N = atoi(argv[1]);
	}
	
	a=(double*) malloc( sizeof(double)*N*N );
	b=(double*) malloc( sizeof(double)*N*N );
	c=(double*) malloc( sizeof(double)*N*N );

	init_arr(N,a);
	init_arr(N,b);

	//DGEMM Multiply
	//reallocate to force cash to be flushed
	a=(double*) malloc( sizeof(double)*N*N );
	b=(double*) malloc( sizeof(double)*N*N );
	c=(double*) malloc( sizeof(double)*N*N );
	init_arr(N,a);
	init_arr(N,b);

	start = clock();
	//for(i=0;i<1000;i++)
	Dgemm_multiply(a,b,c,N);
	stop = clock();

	printf("Dgemm_multiply(). Elapsed time = %g seconds\n",
		((double)(stop - start)) / CLOCKS_PER_SEC);
	//print simple test case of data to be sure multiplication is correct
	if (N < 7) {
		print_arr(N,"a", a);
		print_arr(N,"b", b);
		print_arr(N,"c", c);
	}

	free(a);
	free(b);
	free(c);

	return 0;
}


//DGEMM way. The PREFERED way, especially for large matrices
void Dgemm_multiply(double* a,double*  b,double*  c, int N)
{	

	double alpha = 1.0, beta = 0.;
	int incx = 1;
	int incy = N;
	cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,N,N,N,alpha,b,N,a,N,beta,c,N);
}

//initialize array with random data
void init_arr(int N, double* a)
{	
	int i,j;
	for (i=0; i< N;i++) {
		for (j=0; j<N;j++) {
			a[i*N+j] = (i+j+1)%10; //keep all entries less than 10. pleasing to the eye!
		}
	}
}

//print array to std out
void print_arr(int N, char * name, double* array)
{	
	int i,j;	
	printf("\n%s\n",name);
	for (i=0;i<N;i++){
		for (j=0;j<N;j++) {
			printf("%g\t",array[N*i+j]);
		}
		printf("\n");
	}
}




