#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstdlib>
std::vector<int> Prime(int n){
    if(n<=0){
        std::cout<<"n<=0"<<std::endl;
        exit(-1);
    }
    bool isPrime[n];
    std::fill(&isPrime[0],&isPrime[0]+n,true);
    int n1=sqrt(n);
    isPrime[0]=isPrime[1]=false;
    for(int k=2;k<=n1;k++){
        for(int j=k*k;j<=n;j+=k){
            isPrime[j]=false;
        }
    }
    std::vector<int> v;
    for(int k=2;k<n;++k){
        if(isPrime[k]){
            v.push_back(k);
        }
    }
    return v;
}
int main(int argc,char *argv[]){
    std::vector<int> Prime(int n);
    int n;
    if (argc==1){
        n=100;
    }
    else{
        n=atoi(argv[1]);
    }
    std::vector<int> v=Prime(n);
    for(auto e:v){
        std::cout<<e<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"the number of prime:"<<v.size()<<std::endl;
    return 0;
}