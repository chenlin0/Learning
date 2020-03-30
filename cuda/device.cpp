#include "cuda_runtime.h"

#include "device_launch_parameters.h"

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main()

{

    int deviceCount;

    cudaGetDeviceCount(&deviceCount);

    int dev;

    for (dev = 0; dev < deviceCount; dev++)

    {

        cudaDeviceProp deviceProp;

        cudaGetDeviceProperties(&deviceProp, dev);

        if (dev == 0)

        {

            if (/*deviceProp.major==9999 && */deviceProp.minor = 9999&&deviceProp.major==9999)

                printf("\n");

 

        }

        printf("\nDevice%d:\"%s\"\n", dev, deviceProp.name);

        printf("Total amount of global memory                   %u bytes\n", deviceProp.totalGlobalMem);

        printf("Number of mltiprocessors                        %d\n", deviceProp.multiProcessorCount);

        printf("Total amount of constant memory:                %u bytes\n", deviceProp.totalConstMem);

        printf("Total amount of shared memory per block         %u bytes\n", deviceProp.sharedMemPerBlock);

        printf("Total number of registers available per block:  %d\n", deviceProp.regsPerBlock);

        printf("Warp size                                       %d\n", deviceProp.warpSize);

        printf("Maximum number of threada per block:            %d\n", deviceProp.maxThreadsPerBlock);

        printf("Maximum sizes of each dimension of a block:     %d x %d x %d\n", deviceProp.maxThreadsDim[0],

            deviceProp.maxThreadsDim[1],

            deviceProp.maxThreadsDim[2]);

        printf("Maximum size of each dimension of a grid:       %d x %d x %d\n", deviceProp.maxGridSize[0], deviceProp.maxGridSize[1], deviceProp.maxGridSize[2]);

        printf("Maximum memory pitch :                          %u bytes\n", deviceProp.memPitch);

        printf("Texture alignmemt                               %u bytes\n", deviceProp.texturePitchAlignment);

        printf("Clock rate                                      %.2f GHz\n", deviceProp.clockRate*1e-6f);

    }

    printf("\nTest PASSED\n");

    getchar();

}
/*
deviceProp.name为GPU名字，如果没有GPU则会输出 Device Emulation 
deviceProp.totalGlobalMem返回的是全局储存器的大小，对大数据或一些大模型计算时显存大小必须大于数据大小，如图返回的是2GB的存储大小， 
deviceProp.multiProcessorCount返回的是设备中流多处理器(SM)
的个数，流处理器（SP）的个数SM数×每个SM包含的SP数，其中帕斯卡为每个SM，64个SP，麦克斯韦为128个，开普勒为192个，费米为32个， 
deviceProp.totalConstMem返回的是常数储存器的大小，如同为64kB 
deviceProp.sharedMemPerBlock返回共享储存器的大小，共享存储器速度比全局储存器快， 
deviceProp.regsPerBlock返回寄存器的数目； 
deviceProp.warpSize返回线程束中线程多少； 
deviceProp.maxThreadsPerBlock返回一个block中最多可以有的线程数； 
deviceProp.maxThreadsDim[]返回block内3维度中各维度的最大值 
deviceProp.maxGridSize[]返回Grid内三维度中各维度的最大值； 
deviceProp.memPitch返回对显存访问时对齐时的pitch的最大值； 
deviceProp.texturePitchAlignment返回对纹理单元访问时对其参数的最大值； 
deviceProp.clockRate返回显存的频率；
*/
