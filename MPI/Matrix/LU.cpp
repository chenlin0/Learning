#include<iostream>
#include<complex>
using namespace std;
template<typename T,typename Int>
int pivot(complex<T> *a,Int n_row,Int n_col,Int n,Int k){
    Int MaxIndex=k;
    complex<T> Max=a[k*n_row+k];
    for(Int i=k+1;i<n;++i){
        if(norm(a[i*n_row+k])>norm(Max)){
            Max=a[i*n_row+k];
            MaxIndex=i;
        }
    }
    for(Int i=k;i<n;++i){
        swap(a[MaxIndex*n_row+i],a[k*n_row+i]);
    }
    return 0;
}
template<typename T,typename Int>
int LU(complex<T> *a,Int n_row,Int n_col){
    for(Int k=0;k<n_row-1;++k){
        for(Int i=k+1;i<n_row;++i){
            a[i*n_row+k]/=a[k*n_row+k];
        }
        for(Int j=k+1;k<n_row;++k){
            for(Int i=k+1;i<n_col;++i){
                a[i*n_row+j]-=a[i*n_row+k]*a[k*n_row+j];
            }
        }
    }
    return 0;
}

template<typename T,typename Int>
int LU_Solve(complex<T> *a,Int n,complex<T> *b,complex<T> *x){
    complex<T> *y=new complex<T>[n];
    Int i,j;
    complex<T> tem;
    for(i=0;i<n;++i){
        tem=0;
        for(j=0;j<i;++j){
            tem+=a[i*n+j]*y[j];
        }
        y[i]=b[i]-tem;
    }
    for(i=n-1;i>0;--i){
        tem=0;
        for(j=i+1;j<n;++j){
            tem+=a[i*n+j]*x[j];
        }
        x[i]=(y[i]-tem)/a[i*n+i];
    }
    delete[] y;
    return 0;
}
int main(){
    complex<double> *a,*b,*x;
    int n=2;
    a=new complex<double>[n*n];
    a[0]=1.0;
    a[1]=1.0;
    a[2]=1.0;
    a[3]=2.0;
    b=new complex<double>[n];
    b[0]=1.0;
    b[1]=0.0;
    x=new complex<double>[n];
    LU(a,n,n);
    LU_Solve(a,n,b,x);    
    for(int i=0;i<n;++i){
        cout<<x[i]<<" ";
    }
    cout<<endl;
    delete[] a;
    delete[] b;
    delete[] x;
    return 0;
}