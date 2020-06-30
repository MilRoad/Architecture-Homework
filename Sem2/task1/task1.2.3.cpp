#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int size, rank, recvRank;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		for (int i = 1; i < size; i++)
		{
			MPI_Recv(&recvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			cout << "0 Принял от " << recvRank << endl;
		}
	}
	else
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

	MPI_Finalize();

	return 0;
}
