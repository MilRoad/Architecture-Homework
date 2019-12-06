#include "omp.h"
#include <iostream>
#include "max_search.hh"
#include <cstdlib>
#include <chrono>

int main()
{
	int n = 10000;
	int m = 10000;
	int** array = new int*[n];
	for(int i = 0; i < n; i++)
	{
		array[i] = new int[m];
		for(int j = 0; j < m; j++)
		{
			array[i][j] = std::rand() % 100000; 
		}
	}
	
	auto start1 = std::chrono::system_clock::now();
	double result1 = max_search(array, n, m, false);
	auto end1 = std::chrono::system_clock::now();

	auto start2 = std::chrono::system_clock::now();
	double result2 = max_search(array, n, m, true);
	auto end2 = std::chrono::system_clock::now();

	std::cout << "result1: " << result1 << std::endl;
	std::cout << "Single thread algorithm: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " microseconds" << std::endl;

	std::cout << "result2: " << result2 << std::endl;
	std::cout << "Multy thread algorithm: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " microseconds" << std::endl;
	return 0;
}