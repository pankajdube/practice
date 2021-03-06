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

int totalactivephones(int **data, int X1, int X2, int Y1, int Y2)
{
//	printf("find total active phones: X1: %d X2: %d, Y1: %d Y2: %d\n", X1, X2, Y1, Y2);
	int i, j;
	int total = 0;
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

	data = (int **) zalloc(S * sizeof(int *));
	for (i = 0; i < S; i++) {
		data[i] = (int *) zalloc(S * sizeof(int));
	}
	
	scanf("%d", &I);

	while (I != 3) {
			switch (I) {
					case 1:
							scanf("%d %d %d\n", &X, &Y, &A);
							data[X][Y] += A;
							//printf("%d %d %d %d\n", I, X, Y, A);
							//printvalues(data, S);
							break;
					case 2:
							scanf("%d %d %d %d\n", &L, &B, &R, &T);
							//printf("%d %d %d %d %d\n", I, L, B, R, T);
							//printvalues(data, S);
							printf("%d\n", totalactivephones(data, L, R, B, T));
							break;
			}
			scanf("%d", &I);
	}
	
	for (i = 0; i < S; i++)
		free(data[i]);

	free(data);

	//printf("Terminating\n");
	return 0;	
}
