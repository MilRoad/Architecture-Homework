#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int size, rank, recvRank;
	MPI_Request request;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int i = 0;

	for (i = 0; i < size - 1; i++)
	{
		if (i < size)
		{
			cout << "Процесс " << i << " отправил " << i + 1 <<  endl;
			MPI_Send(&rank, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
		}
		if (i > 0)
		{
			MPI_Irecv(&recvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
			cout << "Процесс " << i <<  " принял от " << recvRank <<  endl;
		}
	}

	MPI_Finalize();

	return 0;
}
