/* If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
*/
#include <stdio.h>

int main()
{
	int sum = 0, i;
	int max_value = 1000;

	for (i = 1; i < max_value; i++) {
		if ((i%3 == 0) || (i%5 == 0))
			sum += i;
	}
	
	printf("Sum of all multiples of 3 or 5 below %d is %d\n", max_value, sum);
}

