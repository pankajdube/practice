#include <stdio.h>
#include <time.h>

unsigned int fibonacci2(int n)
{
	int i;
	unsigned int last=1, second_last=0;
	unsigned int answer = 0;
	if (n <= 1)
		return n;
	for (i = 2; i <= n; i++) {
		answer = last + second_last;
		second_last = last;
		last = answer;
	}

	return answer;
}

unsigned int fibonacci1(int n)
{
	if (n <= 1)
		return n;

	return fibonacci1(n-1) + fibonacci1(n-2);
}

int main()
{
	unsigned int answer;
	double duration;
	clock_t start;
	int n;
	printf("Enter the required term number:\n");
	scanf("%d", &n);
	start = clock();
	answer = fibonacci2(n);
	duration = (double) ((clock()-start)/CLOCKS_PER_SEC);
	printf("fibonacci-2 operation took time: %f sec\n", duration);
	printf("%d th term of fibonacci term is %d\n", n, answer);
	printf("=====================================\n");
	start = clock();
	answer = fibonacci1(n);
	duration = (double) ((clock()-start)/CLOCKS_PER_SEC);
	printf("fibonacci-1 operation took time: %f sec\n", duration);
	printf("%d th term of fibonacci term is %d\n", n, answer);
	return 0;
}
