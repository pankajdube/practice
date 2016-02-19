#include <stdio.h>

int cycle_length(unsigned int n)
{
	int length = 0;

increment:
	length++;
	if (n == 1) {
		return length;
	}
	if (n % 2 != 0) {
		n = 3 * n + 1;
		length++;
		n = n >> 1;
	}
	else
		n = n >> 1;
	goto increment;
}

void swap(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int main()
{
	int i, j, k;
	int temp_i, temp_j;
	int max_cycle_len, cur_len;
	while (scanf("%d %d\n", &i, &j) != EOF) {
		max_cycle_len = 0;
		temp_i = i;
		temp_j = j;
		if (i > j)
			swap(&i, &j);

		for (k = i; k <= j; k++) {
			cur_len = cycle_length(k);
			if (cur_len > max_cycle_len)
				max_cycle_len = cur_len;
		}
		printf("%d %d %d\n", temp_i, temp_j, max_cycle_len);
	};
	return 0;
}
