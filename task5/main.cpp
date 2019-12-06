#include "omp.h"
#include <string.h>
#include <iostream>
#include "search.hh"
#include <chrono>

int main()
{
	
	auto string = "Hello, world";
	auto substring = "ld";

	auto start1 = std::chrono::system_clock::now();
	int result1 = brute_force_search(string, substring, false);
	auto end1 = std::chrono::system_clock::now();

	auto start2 = std::chrono::system_clock::now();
	int result2 = brute_force_search(string, substring, true);
	auto end2 = std::chrono::system_clock::now();

	std::cout << "result1: " << result1 << std::endl;

	std::cout << "Single thread algorithm: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " microseconds" << std::endl;

	std::cout << "result2: " << result2 << std::endl;

	std::cout << "Multy thread algorithm: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " microseconds" << std::endl;
	
	return 0;
}