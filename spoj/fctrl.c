#include <stdio.h>
#include <math.h>

int power(int base, int pow)
{
	int i;
	int result = base;
	for (i = 1; i < pow; i++)
		result *= base;

	return result;
}	

int main ()
{
	int test_count;
	int number;
	int number_of_zeroes;

	scanf("%d\n", &test_count);
	while (test_count > 0) {
		number_of_zeroes = 0;
		scanf("%d\n", &number);
	
		int divider = 5;
		while (divider < number) {
			number_of_zeroes += (number / divider);
			divider *= 5; 
		}	
		printf("%d\n", number_of_zeroes);
		test_count--;
	}
	
	return 0;
}
