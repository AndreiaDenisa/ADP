#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;


#define LIMIT     10      
#define ELEMENT   10
#define MAXSIZE   100



int main(int argc, char *argv[])
{

	int   ntasks, rank;
	int array[100];      
	int i;
	int position[LIMIT], positions[LIMIT];        
	int numOfPositionOfElem;
	int sendcount;    //number of elements sent to each process 
	int recvcount;    // number of elements in receive buffer
	int root;        // rank of sending process 
	int recvbuf[LIMIT];


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	printf("Insert the array : \n ");
	if (0 == rank) {
		for (i = 0; i < LIMIT; i++)
			//scanf("%d", array[i]);	
			cin >> array[i];
	}

	
	if (ntasks == LIMIT) {
		root = 1;
		sendcount = LIMIT;
		recvcount = LIMIT;

		//The root process sends equally sized data in the application buffer to all other processes in the communicator
		//Each process will be sent a different data segment.
		
		// Use scatter for sending the array. If the element is found many times, print all its positions.
		//MPI_Scatter sends chunks of array to different processes
		MPI_Scatter(array, sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, root, MPI_COMM_WORLD);
		
	}
	
	numOfPositionOfElem = 0;

	for (i = 0; i < LIMIT; i++) {
		if (array[i] == ELEMENT) 
			position[numOfPositionOfElem++] = i;
	}
	if (numOfPositionOfElem == 0) {
		printf("The element does not exist in the array\n");
	}
	else {
		//Use MPI_Gather for sending back the positions
		//MPI_Gather takes elements from many processes and gathers them to one single process

		//The root process gathers data from all other processes and places it into a receive buffer ordered by the sender's rank
		 /* Gather the array position from all proceses, place it in positions */
		MPI_Gather(&position, numOfPositionOfElem, MPI_INT, &positions, numOfPositionOfElem, MPI_INT, 0, MPI_COMM_WORLD);

		printf("The array of the positions of the element are : \n");
		for (i = 0; i < numOfPositionOfElem; i++)
			printf("%d  ", positions[i]);

	}

	system("PAUSE");
	MPI_Finalize();

}
