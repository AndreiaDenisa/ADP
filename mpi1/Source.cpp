#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define N 15//dimenisunea vectorului
#define NUMAR 7//numarul cautat


int main(int argc, char *argv[])
{
	int proc, procid, gasit=0;
	int a[N]={9,8,7,6,5,4,3,2,1,0,7,2,3,7,3};           //vectorul in care caut
	int b[N];                                 //vectorul in care stochez indicii unde gasesc elementul cautat in vectroul a;

	MPI_Init(&argc, &argv);                   //initializez mpi
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);   //id-ul unic al procesului curent
	MPI_Comm_size(MPI_COMM_WORLD, &proc);     //nr total de procese
	


	for (int i  =(N/proc)*procid; i <= (N/proc)*(procid+1)-1; i++) {     //dimensiunea fiecarui segment..in functie de procese
		if (a[i] == NUMAR) {                                             //daca gasesc numarul,retin indicele
			b[gasit] = i ;
			gasit++;                                                     //de cate ori am gasit numarul-1

		}
		
	}	
	printf("Am gasit elementul de %d ori\n ",gasit);

	if (gasit==0){

		printf("Nu am gasit\n");
	}
	else {

		printf("Elementul %d se afla pe pozitiile: ", NUMAR);
		for (int j = 0; j < gasit; j++){
			printf("%d  ", b[j]);
		}
		printf("\n");
	
		
	}
	system("pause") ;
	MPI_Finalize();//se termina programul

}