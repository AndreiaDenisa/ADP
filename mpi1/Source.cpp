#include "mpi.h"
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#define MAXSIZE 100
#define SNR 10

int main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, myresult = 0, result;
	

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);


if (0 == myid) {
	for (i = 0; i < MAXSIZE; i++) {
		data[i] = rand() %20 + 1;
		printf("%d   ", data[i]);
	}
}
printf("\n");
/* broadcast data */
//Broadcasts a message from the process with rank "root" to all other processes of the communicator
//Use MPI_Broadcast for sending the array
MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);

/* add portion of data */
x = MAXSIZE / numprocs; /* must be an integer *///impart in bucati vectorul, fiecare proces face o parte
low = myid * x;
high = low + x;
for (i = low; i<high; i++) {
	if (data[i] == SNR) {
		myresult = i;
	}
}
printf("I got %d from %d\n", myresult, myid);

//Combines the values sent by all processes using a predefined operator and places result in the receive buffer of the root process.
//For computing the maximum position, you need to use MPI_Reduce.
MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
if (0 == myid) {
	printf("The maximum position is %d.\n", result);
}
MPI_Finalize();
}
