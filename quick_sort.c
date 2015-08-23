#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int data[SIZE];
int size;

void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

void print_elements()
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", data[i]);
	
	printf("\n");
}
void quick_sort(int *data, int left, int right)
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
	int i;
	double duration;
	clock_t start;

	scanf("%d", &size);
	
	for (i = 0; i < size; i++)
		scanf("%d", &data[i]);
	
	printf("Given Array Elements: \n");
	print_elements(-1, 0);
	start = clock();	
	quick_sort(data, 0, size-1);
	duration = (double) ((clock()-start)/CLOCKS_PER_SEC);
	printf("Sorted in %f sec \n", duration);
	print_elements(-1, 0);	
	return 0;
}
