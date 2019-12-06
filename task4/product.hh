int** block_product(int** a, int** b, int m, int n, int k, unsigned int threads_num)
{
	int** result = new int*[m];
	for(int i = 0; i < m; i++)
		result[i] = new int[k];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < k; j++)
			result[i][j] = 0;
#pragma omp parallel num_threads(threads_num)
	{
		int p = omp_get_num_threads();
		int q = p;
		int r = p;
		int a_block_height = m / p;
		int a_block_width = n / q;
		int b_block_heigth = n / q;
		int b_block_width = k / r;
#pragma omp for
		for(int a_block_count = 0; a_block_count < p * q; a_block_count++ )
		{
			int i_block_index = a_block_count / q;
			int j_block_index = a_block_count % q;
			for(int t_block_index = 0; t_block_index < r; t_block_index++)
			{
				for(int i = i_block_index * a_block_height; i < (i_block_index + 1) * a_block_height; i++)
					for(int j = j_block_index * a_block_width; j < (j_block_index + 1) * a_block_width; j++)
						for(int t = t_block_index * b_block_width; t < (t_block_index + 1) * b_block_width; t++)
							result[i][t] += a[i][j] * b[j][t];				
			}
		}
	}
	return result;
}	