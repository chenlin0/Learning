#include<stdio.h>
#include "cuda_runtime.h"
__global__ void helloFromGPU(){
    printf("Hello World");
}
__global__ void VecAdd(float *A,float *B,float *C){
    int i=threadIdx.x+blockIdx.x*blockDim.x;
    C[i]=A[i]+B[i];
}
int main(){
    
    helloFromGPU<<<1,10>>>();
    cudaDeviceReset();
    return 0;
}