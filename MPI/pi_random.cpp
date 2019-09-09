#include<iostream>
#include <mpi.h>
#include<random>
using std::cout;
using std::endl;
using std::cin;
int main(int argc, char *argv[])
//      int argc;  
//      char *argv[];  
{
	const long N = 10000000;
	std::default_random_engine e;
	std::uniform_real_distribution<double> u(0.0, 1.0);
	int id, size, i, count;
	double pi,local_pi, x, y;
	MPI_Init(&argc, &argv);        /* starts MPI */
	MPI_Comm_rank(MPI_COMM_WORLD, &id);  /* get current process id */
	MPI_Comm_size(MPI_COMM_WORLD, &size);      /* get number of processes */
	for (i = 0, count = 0; i < N; ++i) {
		x = u(e);
		y = u(e);
		if (x*x + y*y < 1) {
			++count;
		}
	}
	local_pi = 4.0*count / N;
	MPI_Reduce(&local_pi, &pi, 1, MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (id == 0) {
		cout << "pi:" << pi / size << endl;
	}
	MPI_Finalize();
	return 0;
}