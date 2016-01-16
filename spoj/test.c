#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>


void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

void print_elements(std::vector<int> data)
{
	for (size_t i = 0; i < data.size(); i++)
		printf("%d\n", data[i]);
}

void quick_sort(std::vector<int> &data, int left, int right)
{
	int i, j, pivot;
	if (left < right) {
			pivot = left;
			i = left;
			j = right;
			while (i < j) {
					while (data[i] <= data[pivot] && i < right)
							i++;
					while (data[j] >= data[pivot] && j > left)
							j--;

					if (i < j)
							swap(&data[i], &data[j]);
			}
			if (j != pivot)
					swap(&data[j], &data[pivot]);
			quick_sort(data, left, j-1);
			quick_sort(data, j+1, right);
	}
}

int main()
{
	int i, new_data;
//	double duration;
//	clock_t start;
	std::vector<int> data;

	scanf("%d\n", &new_data);
	
	while (new_data != 42) {
		data.push_back((int) new_data);
		scanf("%d\n", &new_data);
	}
	
//	printf("Given Array Elements: \n");
//	print_elements(data);
//	start = clock();	
	quick_sort(data, 0, data.size()-1);
//	duration = (double) ((clock()-start)/CLOCKS_PER_SEC);
//	printf("Sorted in %f sec \n", duration);
	print_elements(data);

	return 0;
}
