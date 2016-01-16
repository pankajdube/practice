#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void printvalues(int **data, int size)
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%d ", data[i][j]);
		}
	printf("\n");
	}
}

long long totalactivephones(int **data, int X1, int X2, int Y1, int Y2)
{
	int i, j;
	long total = 0;
	for (i = X1; i <= X2; i++) {
			for (j = Y1; j <= Y2; j++) {
				total += data[i][j];
			}
	}

	return total;
}

int main ()
{
	int I, S, X, Y, A, L, B, R, T;
	int **data;
	int i;

	scanf("%d %d\n", &I, &S);

	data = (int **) malloc(S * sizeof(int *));
	for (i = 0; i < S; i++) {
		data[i] = (int *) malloc(S * sizeof(int));
	}
	
	scanf("%d", &I);

	while (I != 3) {
			switch (I) {
					case 1:
							scanf("%d %d %d\n", &X, &Y, &A);
							data[X][Y] += A;
							//printvalues(data, S);
							break;
					case 2:
							scanf("%d %d %d %d\n", &L, &B, &R, &T);
							//printvalues(data, S);
							printf("%lld\n", totalactivephones(data, L, R, B, T));
							break;
			}
			scanf("%d", &I);
	}
	
	for (i = 0; i < S; i++)
		free(data[i]);

	free(data);

	return 0;	
}
