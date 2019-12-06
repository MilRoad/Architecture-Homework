int brute_force_search(const char* string, const char* substring, bool is_parallel)
{
	int result = -1;
	#pragma omp parallel shared(string, substring) if(is_parallel)
	{
		#pragma omp for
		for(int i = 0; i < strlen(string) - strlen(substring) + 1; i++)
		{
			int matches_count = 0;
			for(int j = 0; j < strlen(substring); j++)
			{
				if(string[i + j] != substring[j])
					break;
				matches_count++;
			}
			if(matches_count == strlen(substring))
			{
				//#pragma omp single
				result = i;
				//break;
			}
		}
	}
	return result;
}