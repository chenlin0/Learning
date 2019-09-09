#include<omp.h>
#include<stdio.h>
static long num_steps=100000;
double step;
#define NUM_THREADS 16
int main(){
    int i;
    double x,pi,result=0.0;
    step=1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for private(x) reduction(+:result)
    for(i=1;i<=num_steps;++i){
        x=(i-0.5)*step;
        result+=4.0/(1.0+x*x);
    }       
    pi=result*step;
    printf("pi:%lf\n",pi);
    return 0;
}