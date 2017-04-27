#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define SIZE 5
#define INF 9999

int main(int argc, char *argv[]) {

	int numprocs, myid;
	int i, j, k;
	int receive[SIZE][SIZE];
	int a[SIZE][SIZE] = {
		(0,   2,   INF, 10,  INF),
		(2,   0,   3,   INF, INF),
		(INF, 3,   0,   1,   8),
		(10,  INF, 1,   0,   INF),
		(INF, INF, 8,   INF, 0)
	};

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	for (k = 0; k < SIZE; k++) {
		for (i = myid; i < SIZE; i=i+numprocs) {
			for (j = 0; j < SIZE; j++) {
				if (a[i][j] > a[i][k] + a[k][j])
					a[i][j] = a[i][k] + a[k][j];
			}
		}

		//Combines values from all processes and distributes the result back to all processes
		//MPI_Allreduce(a, receive, SIZE*SIZE, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
		//Blocks the current process until all other processes in the current communicator have reached this routine.
		//MPI_Barrier(MPI_COMM_WORLD);
		MPI_Reduce(a,receive,SIZE*SIZE,MPI_INT,MPI_MIN, 0, MPI_COMM_WORLD );
		if(myid == 0){
			for (i = 0; i < SIZE; i++) {
				for (j = 0; j < SIZE; j++) {
					a[i][j] = receive[i][j];
				}
			}
			MPI_Bcast(a, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}

	if(myid == 0){
			for (i = 0; i < SIZE; i++) {
				for (j = 0; j < SIZE; j++) {
					printf("%d  ", a[i][j]);
				}
			}
	}
	
	system("pause");
	MPI_Finalize();
}