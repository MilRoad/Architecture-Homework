#include "omp.h"
#include <iostream>
#include "product.hh"
#include <cstdlib>
#include <chrono>

int main()
{
	int m = 100;
	int n = 1000;
        int k = 100;

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
			b[i][j] = std::rand() % 10;
		}
	}
	
	auto start1 = std::chrono::system_clock::now();
	int** result1 = product(a, b, m, n, k,false);
	auto end1 = std::chrono::system_clock::now();

	auto start2 = std::chrono::system_clock::now();
	int** result2 = product(a, b, m, n, k, true);
	auto end2 = std::chrono::system_clock::now();

	std::cout << "result1: " << std::endl;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < k; j++)
			std::cout << result1[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << "Single thread algorithm: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " microseconds" << std::endl;

	std::cout << "result2: " << std::endl;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < k; j++)
			std::cout << result2[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << "Multy thread algorithm: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " microseconds" << std::endl;
	
	return 0;
}	