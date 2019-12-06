int** product(int** a, int** b, int m, int n, int k, bool is_parallel)
{
	int** result = new int*[m];
	for(int i = 0; i < m; i++)
	{
		result[i] = new int[k];
	}
	#pragma omp parallel shared(a, b) if(is_parallel)
	{
		for(int i = 0; i < m; i++)
		{
			#pragma omp for nowait  
			for(int j = 0; j < k; j++)
			{
				result[i][j] = 0;
				for(int s = 0; s < n; s++)
				{
					result[i][j] += a[i][s] * b[s][j];
				}
			}
		}
	}
	return result;
}