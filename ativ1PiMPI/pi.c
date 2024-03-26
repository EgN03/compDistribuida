#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double sum = 0;  /* sequence sum */
int n;  /* size of sequence */
void calcula(int rank, double *sum, int size);

int main(int argc, char **argv)
{
	int j, i;
	int comm_sz, my_rank;
	double pi = 0;
	int totalp = 0, totalc = 0;
	if (argc != 2) {
		n = 5000;
	} else {
		n = atoi(argv[1]);
	}
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	
	if(my_rank != 0){
		double my_sum =0;
		calcula(my_rank, &my_sum,comm_sz);
		MPI_Send(&my_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}else{
		int i;
		double local_sum;
		calcula(my_rank, &sum,comm_sz);
		for(i=1; i< comm_sz; i++){
			MPI_Recv(&local_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum+= local_sum;
		}
		
		printf("n: %d, nthr: %d\n", n, comm_sz);
		pi = 4.0*sum;
		printf("Valor de pi:\%f\n",pi);
	}
	MPI_Finalize();

	return 0;
}


void calcula (int my_rank, double *my_sum,int size) {

    double factor;
    long long i;
    long long my_n = n/size;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    
    if (my_first_i % 2 == 0) /* my_first_i is even */
        factor = 1.0;
    else /* my_first_i is odd */
        factor = -1.0;
    
    for (i = my_first_i; i < my_last_i; i++, factor = -factor){
        *my_sum += factor/(2*i + 1);
    }
  return;
}

