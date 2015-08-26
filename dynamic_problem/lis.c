#include <stdio.h>
#include <malloc.h>
/**
 * Overlapping Subsequence Problem
 */

int dynamic_lis(int data[], int size)
{
	int *lis, i, j, max = 0;
	lis = (int *) malloc(sizeof(int) * size);

	//Initialize lis elements
	for (i = 0; i < size; i++)
		lis[i] = 1;

	//Compute in bottom up manner
	for (i = 1; i < size; i++) {
		for (j = 0; j < i; j++) {
			if (data[i] > data [j] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
		}
	}
	
	//Pick max of all lis value
	for (i = 0; i < size; i++)
		if (max < lis[i])
			max = lis[i];

	//Free memory
	free(lis);

	//return
	return max;	
}

int _lis(int data[], int size, int *max_length)
{
	printf("%s size: %d\n",__func__,size);
	/*base case*/
	if (size == 1)
		return 1;

	int i, res, max_found_here = 1;
	for (i = 1; i < size; i++) {
		res = _lis(data, i, max_length);
		if (data[i-1] < data[size-1] && (res + 1) > max_found_here)
			max_found_here = res + 1;		
	}

	if (*max_length < max_found_here)
		*max_length = max_found_here;

	return max_found_here;
}

int longest_increasing_subsequence(int data[], int size)
{
	int max_length = 1;
	_lis(data, size, &max_length);
	return max_length;
}

int main()
{
	int lis_count;
	int data[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
	int size = sizeof(data) / sizeof(data[0]);
	//lis_count = longest_increasing_subsequence(data, size);
	lis_count = dynamic_lis(data, size);

	printf("Longest Increasing Subsequence found: %d\n", lis_count);
	return 0;
}
