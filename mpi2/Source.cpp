#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;


#define LIMIT     5        
#define FOUND   10
#define MAXSIZE   100



int main(int argc, char *argv[])
{

	int   ntasks, rank;
	int array[100];       //array
	int i;
	int position;         //position of the element
	int x;
	int start, end;
	int maxPosition;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	printf("Insert the array : ");
	if (0 == rank) {
		//read the array
		for (i = 0; i < LIMIT; i++)
			//scanf("%d", array[i]);	
			cin >> array[i];
	}

	//Broadcasts a message from the process with rank "root" to all other processes of the communicator
	//Use MPI_Broadcast for sending the array
	MPI_Bcast(array, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);

	x = MAXSIZE / ntasks; //impart in bucati vectorul, fiecare proces face o parte
	start = rank * x; 
	end = start + x;
	for (i = LIMIT; i > 0; i--) {
		if (array[i] == FOUND) {
			position = i;
			break;
		}	
	}

	printf("I got %d position from %d\n", position, rank);

	//Combines the values sent by all processes using a predefined operator and places result in the receive buffer of the root process.
	//For computing the maximum position, you need to use MPI_Reduce.
	MPI_Reduce(&position, &maxPosition, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (0 == rank) {
		printf("The max position is %d \n", maxPosition);
	}
		
	system("PAUSE");
	MPI_Finalize();

}