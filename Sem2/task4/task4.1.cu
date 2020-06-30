#include "cuda.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace std;

__global__ void SumMatrCuda(int *res, int *mas1, int *mas2, int N, int M)
{
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	int tx = i * N + j;
	res[tx] = mas1[tx] + mas2[tx];
}

void SumMatr(int *res, int *mas1, int *mas2, int N, int M)
{
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++)
			res[i*N + j] = mas1[i*N + j] + mas2[i*N + j];
	}
}

void PrintMas(int *mas, int N, int M)
{
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++)
			cout << mas[i*N + j] << " ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	const int N = 4, M = 4;
	int dimN = 2, dimM = 2;

	int mas1[N * M] = {1,2,3,4,
					5,6,7,8,
					9,10,11,12,
					13,14,15,16};
	int mas2[N * M] = {16,15,14,13,
						12,11,10,9,
						8,7,6,5,
						4,3,2,1};
	int *res = new int[N * M];

	int *cudaMas1;
	int *cudaMas2;
	int *cudaRes;

	float time = 0;

	cudaMalloc((void**)&cudaMas1, sizeof(int) * N * M);
	cudaMalloc((void**)&cudaMas2, sizeof(int) * N * M);
	cudaMalloc((void**)&cudaRes,  sizeof(int) * N * M);

	cudaMemcpy(cudaMas1, mas1, sizeof(int) * N * M, cudaMemcpyHostToDevice);
	cudaMemcpy(cudaMas2, mas2, sizeof(int) * N * M, cudaMemcpyHostToDevice);
	cudaMemcpy(cudaRes,  res,  sizeof(int) * N * M, cudaMemcpyHostToDevice);

	cudaEvent_t start, end;
	cudaEventCreate(&start);
	cudaEventCreate(&end);

	PrintMas(mas1, N, M);
	PrintMas(mas2, N, M);

	cudaEventRecord(start);
	SumMatr(res, mas1, mas2, N, M);
	cudaEventRecord(end);
	cudaEventSynchronize(end);	

	cout << "Cумма "<< endl;
	PrintMas(res, N, M);

	cudaEventElapsedTime(&time, start, end);
	cout << "Время работы в обычном режиме " << time << endl;

	dim3 blocks(N / dimN, M / dimM);
	dim3 threads(dimN, dimM);

	cudaEventRecord(start);
	SumMatrCuda<<< blocks, threads >>>(cudaRes, cudaMas1, cudaMas2, N, M);
	cudaDeviceSynchronize();
	cudaEventRecord(end);

	cudaMemcpy(res, cudaRes, sizeof(int) * N * M, cudaMemcpyDeviceToHost);

	cout << "Сумма" << endl;
	PrintMas(res, N, M);
 	cudaEventElapsedTime(&time, start, end);
   	cout << "Время работы в параллельном режиме " << time << endl;

	cudaFree(cudaMas1);
	cudaFree(cudaMas2);
	cudaFree(cudaRes);

	return 0;
}
