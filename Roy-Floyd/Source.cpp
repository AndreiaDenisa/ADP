#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 5

int main(int argc, char *argv[])
{
	int a[N][N] = {
		{0,2,100,10,100},
		{2,0,3,100,100}, 
		{100,3,0,1,8},
		{10  ,100, 1,0,100},
		{100, 100, 8 ,100, 0}
		
	};
	int b[N][N];
	int procid, proc;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	MPI_Comm_size(MPI_COMM_WORLD, &proc);
	
	for (int k = 0; k < N; k++)
	{
		for (int i = procid; i < N; i = i + proc)
		{
			for (int j = 0; j < N; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j])
					a[i][j] = a[i][k] + a[k][j];
			}
		}
			//minimul din a il punem in b
		MPI_Reduce(a, b, N*N, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
		
	}
	for (int i = 0; i < N; i ++)
		{
			for (int j = 0; j < N; j++)
			{
				cout<<a[i][j]<<" ";
				
			}
			cout<<endl;
			
		}


	MPI_Finalize();
	system("pause");
}
