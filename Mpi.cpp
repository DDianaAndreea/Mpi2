
#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0



int main(int argc, char *argv[])
{
	int numprocs, rank;
	int max = 0;
	int random = 0;
	int v[4] = { 0 };
	int idproc=0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Status status;

	if (rank == MASTER)
	{
		
		for (int i = 1; i < numprocs; i++)
		{
			random = rand() % 100;
			MPI_Send(&random, 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}

		random = rand() % 100;
		v[0] = random;

	}
	else
	{
		for (int i = 1; i < numprocs; i++)
		{
			MPI_Recv(&random, 1, MPI_INT, MASTER, 1, MPI_COMM_WORLD, &status);
			v[i] = random;
			printf("rank %d : %d \n", rank, random);
		}

		for (int i = 0; i < numprocs; i++)
		{
			if (v[i] > max)
			{
				max = v[i];
				idproc = i;
			}

			if (v[i] == max)
			{
				idproc = i;
			}
			
		}
		printf("max number is :%d  with procces id:", max, idproc);
	}


	MPI_Finalize();
}