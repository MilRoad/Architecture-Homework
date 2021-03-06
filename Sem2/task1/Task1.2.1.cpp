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
	int i = 0;

	for (i = 0; i < size - 1; i++)
	{
		if (rank == i && i < size)
		{
			cout << "Процесс " << i << " отправил " << i + 1 <<  endl;
			MPI_Send(&i, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
		}
		if (rank == i && i > 0)
		{
			MPI_Recv(&recvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			cout << "Процесс " << i <<  " принял от " << recvRank <<  endl;
		}
	}

	MPI_Finalize();

	return 0;
}
