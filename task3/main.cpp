#include "omp.h"
#include <iostream>
#include <chrono>
#include "product.hh"
#include <ctime>
#include <fstream>

int main()
{
	std::ofstream row_outfile;
	row_outfile.open("out_row_product.txt");

	std::ofstream column_outfile;
	column_outfile.open("out_column_product.txt");

	std::ofstream block_outfile;
	block_outfile.open("out_block_product.txt");		
	 
	std::srand(unsigned(std::time(0)));
	
	int max_threads_number = 16;
	int max_dimention = 100000;

	for(int dim = 12; dim < max_dimention; dim*=10)
	{
		row_outfile << dim << " ";
		column_outfile << dim << " ";
		block_outfile << dim << " ";
	}
	row_outfile << std::endl;
	column_outfile << std::endl;
	block_outfile << std::endl;

	for(int threads_number = 1; threads_number < max_threads_number+1; threads_number*=2)
	{
		std::cout << "Threads number: " << threads_number << std::endl;
		for(int dimention = 12; dimention < max_dimention; dimention *= 10)
		{
			std::cout << "Dimention: " << dimention << std::endl;
			int m = dimention;
			int n = dimention;
			int** a = new int*[m];
			for(int i = 0; i < m; i++)
			{
				a[i] = new int[n];
				for(int j = 0; j < n; j++)
				{
					a[i][j] = std::rand() % 10;
					//std::cout << a[i][j] << " ";
				}
				//std::cout << std::endl;
			}
			//std::cout << std::endl;
			int* b = new int[n];
			for(int i = 0; i < n; i++)
			{
				b[i] = std::rand() % 10;
				//std::cout << b[i] << " ";
			}
			//std::cout << std::endl;
			
			auto start1 = std::chrono::system_clock::now();
			int* result1 = row_product(a, b, m, n, threads_number);
			auto end1 = std::chrono::system_clock::now();

			row_outfile << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " ";

			auto start2 = std::chrono::system_clock::now();
			int* result2 = column_product(a, b, m, n, threads_number);
			auto end2 = std::chrono::system_clock::now();

			column_outfile << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " ";

			auto start3 = std::chrono::system_clock::now();
			int* result3 = block_product(a, b, m, n, threads_number);
			auto end3 = std::chrono::system_clock::now();

			block_outfile << std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count() << " ";



			for(int i =0; i < m; i++)
			{
				delete[] a[i];
			}
			delete[] a;
			delete[] b;
			delete[] result1;
			delete[] result2;
			delete[] result3;
		}
		row_outfile << std::endl;	
		column_outfile << std::endl;
		block_outfile << std::endl;

	}
	row_outfile.close();	
	column_outfile.close();
	block_outfile.close();

	return 0;
}