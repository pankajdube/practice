/*
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600851475143 ?
*/

#include <stdio.h>
#include <math.h>

long find_max_prime_factor(long value)
{
	long largest_prime_factor = value;
	long divider = 2;
	while (value % divider == 0) {
			printf("value: %lu divider: %lu\n", value, divider);
			value = value / divider;
			largest_prime_factor = divider;
	}

	divider++;

	for (;divider <= sqrt(value); divider = divider + 2) {
		    printf("Checkking divider: %lu\n", divider);
		while (value % divider == 0) {
			printf("value: %lu divider: %lu\n", value, divider);
			value = value / divider;
			largest_prime_factor = divider; 
		}
	}

	if (value > 2)
		largest_prime_factor = value;

	return largest_prime_factor;
}

int main()
{
	long max_value = 600851475143;
	long max_prime_factor = max_value;
	max_prime_factor = find_max_prime_factor(max_value);
	printf("largest prime factor of %lu is %lu\n", max_value, max_prime_factor);
	return 1;
} 

