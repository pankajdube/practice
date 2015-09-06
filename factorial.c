#include <stdio.h>
#include <time.h>

unsigned int factorial2(int n)
{
	int i;
	unsigned int last=1;
	unsigned int answer = 1;
	printf("%s(%d)\n",__func__,n);
	if (n <= 1)
		return n;
	for (i = 2; i <= n; i++) {
		answer = answer * i;
	}

	return answer;
}

unsigned int factorial1(int n)
{
	printf("%s(%d)\n",__func__,n);
	if (n <= 1)
		return n;

	return (unsigned int) (n * factorial1(n-1));
}

int main()
{
	unsigned int answer;
	double duration;
	clock_t start;
	int n;
	printf("Enter the required term number:\n");
	scanf("%d", &n);
#if 1
	start = clock();
	answer = factorial2(n);
	duration = (double) ((clock()-start)/CLOCKS_PER_SEC);
	printf("factorial-2 operation took time: %f sec\n", duration);
	printf("%d th term of factorial term is %d\n", n, answer);
	printf("=====================================\n");
#endif
#if 1
	start = clock();
	answer = factorial1(n);
	duration = (double) ((clock()-start)/CLOCKS_PER_SEC);
	printf("factorial-1 operation took time: %f sec\n", duration);
	printf("%d th term of factorial term is %d\n", n, answer);
#endif
	return 0;
}
