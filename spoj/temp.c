#include <stdio.h>

#define LOWBIT(x) x&(-x)
#define RANGE 10
int main()
{
	int i;
	for (i = 1; i < RANGE; i++)
		printf("i: %d, LOWBIT(i): %d\n", i, LOWBIT(i));

	return 0;
}
