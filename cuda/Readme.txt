//Ubuntu 
nvcc -c test1.cu  
g++  -c test3.cpp  
g++  -o test test1.o test3.o -lcudart -L/usr/local/cuda/lib64 

nvcc -c test1.cu  
gcc  -c test2.c  
gcc  -o testc test1.o test2.o -lcudart -L/usr/local/cuda/lib64  

nvcc -lib test1.cu -o libtestcu.a  
gcc       test2.c -ltestcu -L. -lcudart -L/usr/local/cuda/lib64 -o testc  

all : c cpp    
c : libtestcu.so   
  gcc test2.c   -ltestcu -L. -lcudart -L/usr/local/cuda/lib64 -o testc    
cpp : libtestcu.so   
  g++ test3.cpp -ltestcu -L. -lcudart -L/usr/local/cuda/lib64 -o testcpp    
libtestcu.so : test.cu    
  nvcc -o libtestcu.so -shared -Xcompiler -fPIC test1.cu      
clean :   
  rm *.so testc testcpp  -f  
