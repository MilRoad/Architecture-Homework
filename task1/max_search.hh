int get_min(int* line, int m)
{
	int min = line[0];
	for (int j = 0; j < m; j++)
	{
		if(line[j] < min)
			{
				min = line[j];
			}
	}
	return min;
}
int max_search(int** array, unsigned int n, unsigned int m, bool is_parallel)
{
	int* min_elements = new int[n];

	#pragma omp parallel if(is_parallel) 
	{
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			min_elements[i] = get_min(array[i], m);
		}
	}

	int max = min_elements[0];
	#pragma omp parallel for
	for(int i = 0; i < n; i++)
	{
		if(min_elements[i] > max)
		{
			max = min_elements[i];
		}
	}
	return max;
}