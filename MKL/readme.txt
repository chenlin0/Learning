gcc -I/opt/intel/mkl/include dgemm_example.c -lmkl_core -lmkl_intel_lp64 -lmkl_intel_thread 
-liomp5 -lpthread -lm -L/opt/intel/mkl/lib/intel64 -L/opt/intel/lib/intel64
或者gcc -I/opt/intel/mkl/include dgemm_example.c -lmkl_rt -L/opt/intel/mkl/lib/intel64 -L/opt/intel/lib/intel64
再或者$ . /opt/intel/bin/compilervars.sh intel64
$ gcc dgemm_example.c -lmkl_rt
（此方法可行是因为前一个命令设置了环境变量 CPATH，LD_LIBRARY_PATH，LIBRARY_PATH，
致使编译器可以找到所需的头文件和库文件。编译C时头文件查找 C_INCLUDE_PATH 中包含目录，C++ 查找 CPLUS_INCLUDE_PATH，C和C++都查找 CPATH）
Intel的MPI库的安装方法与MKL相同，执行 compilervars.sh 之后即可编译使用了MPI库的文件。
gmres_test.c
$ . /opt/intel/bin/compilervars.sh intel64
$ mpicc gmres_test.c -o gmres_test -lmkl_rt

// win10 mkl
   > ..\compilers_and_libraries_2019\windows\mkl\bin\mklvars.bat" intel64   
    >  cl.exe mkl_lab_solution.c  mkl_intel_c.lib mkl_core.lib mkl_intel_thread.lib libiomp5md.lib
//ubuntu gsl
gcc -Wall -I/usr/local/include -c example.c
gcc -L/usr/local/lib example.o -lgsl -lgslcblas -lm
// win10 gsl
g++ -c example.cpp -I"D:\mingw64\include" -Wall
g++ -static example.o -L"D:\mingw64\lib" -lgsl -lgslcblas -lm