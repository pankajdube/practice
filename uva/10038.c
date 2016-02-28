#include <stdio.h>
#include <string.h>

#define MAX 3000
int data[MAX];

int main()
{
	int n;
	int i;
	while (scanf("%d", &n) && n != '\n') {
		memset(data, 0, sizeof data); 
		for (i = 0; i < n; i++)
			scanf("%d", &data[i]);

		printf("%d ", n);
		for (i = 0; i < n; i++)
			printf("%d ", data[i]);
	}
	return 0;
}
