#include "omp.h"
#include <iostream>
#include <chrono>
#include "product.hh"
#include <ctime>
#include <fstream>

int main()
{

	std::ofstream block_outfile;
	block_outfile.open("out_block_product.txt");		
	 
	std::srand(unsigned(std::time(0)));
	
	int max_threads_number = 16;
	int max_dimention = 10000;

	for(int dim = 12; dim < max_dimention; dim*=10)
	{
		block_outfile << dim << " ";
	}
	block_outfile << std::endl;

	for(int threads_number = 1; threads_number < max_threads_number+1; threads_number*=2)
	{
		std::cout << "Threads number: " << threads_number << std::endl;
		for(int dimention = 12; dimention < max_dimention; dimention *= 10)
		{
			std::cout << "Dimention: " << dimention << std::endl;
			int m = dimention;
			int n = dimention;
			int k = dimention;
			int** a = new int*[m];
			for(int i = 0; i < m; i++)
			{
				a[i] = new int[n];
				for(int j = 0; j < n; j++)
				{
					a[i][j] = std::rand() % 10;
				}
			}
			int** b = new int*[n];
			for(int i = 0; i < n; i++)
			{
				b[i] = new int[k];
				for(int j = 0; j < k; j++)
				{
					b[i][j] = std::rand() % 5;
				}
			}

			auto start3 = std::chrono::system_clock::now();
			int** result3 = block_product(a, b, m, n, k, threads_number);
			auto end3 = std::chrono::system_clock::now();

			block_outfile << std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count() << " ";

			for(int i =0; i < m; i++)
			{
				delete[] a[i];
			}
			for(int i =0; i < n; i++)
			{
				delete[] b[i];
			}
			delete[] a;
			delete[] b;
			delete[] result3;
		}
		block_outfile << std::endl;
	}
	block_outfile.close();

	return 0;
}