#include<iostream>
#include<complex>
#include"mpi.h"
#include<fstream>
using namespace std;
const int data_tag = 0;
const int result_tag = 1;
const int terminate_tag = 2;
const int num_x = 640;
const int num_y = 480;
const float scale_x = 1.0 / 160;
const float scale_y = 1.0 / 160;
const complex<float> min_z = { -2.0,-1.5 };
struct Message {
	int id;
	int row;
	int color[num_x];
};
int main(int argc, char* argv[]) {
	int cal_pixel(complex<float> c);

	int id;//进程编号
	int num_proc;//进程数
	int count; // 正在进行的进程
	int row; // 用来发送的矩阵行号
	MPI_Status stat;
	Message result;//传递结果
	complex<float> c;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	MPI_Datatype Messagetype;
	MPI_Datatype oldtype[3] = { MPI_INT,MPI_INT,MPI_INT };
	int blockcount[3] = { 1,1,num_x };
	MPI_Aint a1, a2, a3;
	MPI_Get_address(&(result.id), &a1);
	MPI_Get_address(&(result.row), &a2);
	MPI_Get_address((void*)(result.color), &a3);
	MPI_Aint offset[3] = { 0,a2-a1,a3-a1 };
	MPI_Type_create_struct(3, blockcount, offset, oldtype, &Messagetype);
	MPI_Type_commit(&Messagetype);

	if (!id) {//主进程
		count = 0;
		row = 0;
		int** picture;
		picture = new int* [num_y];
		for (int i = 0; i < num_y; ++i) {
			picture[i] = new int[num_x];
		}
		for (int i = 1; i < num_proc; i++) { // 发送初始的行给各进程
			MPI_Send(&row, 1, MPI_INT, i, data_tag, MPI_COMM_WORLD);
			count++;
			row++;
		}

		do {
			MPI_Recv(&result, 1, Messagetype, MPI_ANY_SOURCE, result_tag, MPI_COMM_WORLD, &stat);//接受各进程的运算结果
		  //  cout<<"Recv row:"<<result.row<<" id: "<<result.id<<" Tag:"<<stat.MPI_TAG<<endl;
			--count;//在计算的进程数-1
			for (int i = 0; i < num_x; ++i) {//保存计算结果
				picture[result.row][i] = result.color[i];
			}
			if (row < num_y) {
				//如果所有行没分配完
				MPI_Send(&row, 1, MPI_INT, stat.MPI_SOURCE, data_tag, MPI_COMM_WORLD);//刚刚结束计算的进程stat.MPI_SOURCE分配新任务
				++count;//计算进程数+1
				++row;//分配下一个行
			}
			else {//所有的数据已经分配完
				MPI_Send(&row, 1, MPI_INT, stat.MPI_SOURCE, terminate_tag, MPI_COMM_WORLD);//发送终止信号
			}
		} while (count > 0);
		ofstream f1("Mandelbrot.txt", ios::out);//输出结果
		for (int i = 0; i < num_y; ++i) {
			for (int j = 0; j < num_x; ++j) {
				f1 << picture[i][j] << " ";
			}
			f1 << endl;
		}
		f1.close();
		for (int i = 0; i < num_y; ++i) {
			delete[] picture[i];
		}
	}
	else {
		MPI_Recv(&row, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);

		while (stat.MPI_TAG == data_tag) {
			c.imag(min_z.imag() + row * scale_y);
			for (int i = 0; i < num_x; ++i) {
				c.real(min_z.real() + i * scale_x);
				result.color[i] = cal_pixel(c);
			}
			//cout<<id<<":"<<endl;
			result.id = id;
			result.row = row;
			MPI_Send(&result, 1, Messagetype, 0, result_tag, MPI_COMM_WORLD);
			MPI_Recv(&row, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
		}
	}
	MPI_Type_free(&Messagetype);
	MPI_Finalize();//结束MPI环境　　
	return 0;
}
int cal_pixel(complex<float> c) {
	int count = 0; // number of iterations
	int max = 256; // maximum iteration is 256
	complex<float> z{ 0,0 }; // initialize complex number z
	do {
		z = z * z + c;
		count++; // update iteration counter
	} while ((norm(z) < 4.0) && (count < max));
	return count;
}