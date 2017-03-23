#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 62                 /* number of rows in matrix A */
#define M 15                 /* number of columns in matrix A */
#define P 7                  /* number of columns in matrix B */

int main (int argc, char *argv[])
{
int	tid, nthreads, i, j, k, chunk;
double	a[N][M],           /* matrix A to be multiplied */
	b[M][P],           /* matrix B to be multiplied */
	c[N][P];           /* result matrix C */

chunk = 10;                    /* set loop iteration chunk size */


#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  tid = omp_get_thread_num(); //Returns the ID (0 to n-1) for the thread calling it
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();  //Returns the number of threads in team
    printf("Starting matrix with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }

  /*** Initialize matrices ***/
  #pragma omp for schedule (static, chunk)
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<M; i++)
    for (j=0; j<P; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<N; i++)
    for (j=0; j<P; j++)
      c[i][j]= 0;

  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<N; i++)
    {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<P; j++)
      for (k=0; k<M; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   /*** End of parallel region ***/

/*** Print results ***/
printf("Result Matrix:\n");
for (i=0; i<N; i++)
  {
  for (j=0; j<P; j++)
    printf("%6.2f   ", c[i][j]);
  printf("\n");
  }
printf ("Done.\n");

}
