#include <stdio.h>
#include <math.h>
#include <vector.h>

void print_prime_numbers(int m, int n)
{
	int n_sqrt = (int) sqrt(n);
	vector <int> primes;
		
	for (; m <=n; m++) {
		if ((m % 2 != 0) || (m % 3 != 0) || (m % 5 != 0) || (m % 7 != 0))
	}
}
int main()
{
	int test_count, test_id;
	int m, n;
	int test;

	scanf("%d\n", &test_count);
	for (test_id = 1; test_id <= test_count; test_id++) {
		scanf("%d %d\n", &m, &n);
		printf("ID: %d, m: %d, n: %d\n", test_id, m, n);
		print_prime_numbers(m , n);
	}
	return 0;
}
