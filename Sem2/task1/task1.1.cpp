#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int size, rank, recvRank;
	//size = 10;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	//comm = 8;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		cout << "Number of process" << size << endl;
		cout << "Hello from process" << rank << endl;
		for (int i = 1; i < size; i++)
		{
			MPI_Recv(&recvRank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			cout << "Hello from process" << recvRank << endl;
		}
	}
	else
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	//cout << "The number of process" << size << "my number is" << rank << endl;
	MPI_Finalize();

	return 0;
}
