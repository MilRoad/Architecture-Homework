int* row_product(int** a, int* b, int m, int n, unsigned int threads_num)
{
	int* result = new int[m];
	for(int i = 0; i < m; i++)
	{
		result[i] = 0;
	}
	#pragma omp parallel shared(a, b, result) num_threads(threads_num)
	{
		#pragma omp for nowait
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				result[i] += a[i][j] * b[j];
			}
		}
	}
	return result;
}

int* column_product(int** a, int* b, int m, int n, unsigned int threads_num)
{
	int* result = new int[m];
	for(int i = 0; i < m; i++)
	{
		result[i] = 0;
	}
	#pragma omp parallel shared(a, b, result) num_threads(threads_num)
	{
		#pragma omp for
		for(int j = 0; j < n; j++)
		{
			for(int i = 0; i < m; i++)
			{
				result[i] += a[i][j] * b[j];
			}
		}
	}
	return result;
}

int* block_product(int** a, int* b, int m, int n, unsigned int threads_num)
{
	int* result = new int[m];
	for(int i = 0; i < m; i++)
	{
		result[i] = 0;
	}
	#pragma omp parallel shared(a, b, result) num_threads(threads_num)
	{
		int s = omp_get_num_threads();
		int q = s;
		int block_height = m / s;
		int block_width = n / q;

		#pragma omp for
		for(int block_count = 0; block_count < s*q; block_count++)
		{
			int i = block_count / q;
			int j = block_count % q;
			for(int k = i*block_height; k < (i+1) * block_height; k++)
				for(int l = j*block_width; l < (j+1) * block_width; l++)
					result[k] += a[k][l] * b[l];
		}
	}
	return result;
}