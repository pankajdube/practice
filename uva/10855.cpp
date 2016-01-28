#include <cstdio>
#include <cstring>
#include <malloc>

using namespace std;

int N, M;

int match_pattern(char **data, char **pattern)
{
	int match;
	int count = 0;
	int i, j, k, l;
	for (i = 0; i < N-M; i++) {
		for (j = 0; j < N-M; j++) {
			match = 1;
			for (k = 0; k < M; k++) {
				for (l = 0; l < M; l++) {
					if (pattern[k][l] != data[i+k][j+l]) {
						match = 0;
						break;
					}
				}
				if (!match)
					break;
			}
			if (match)
				count++;
		}
		
	}	
	return count;
}

void rotate_pattern(char **pattern)
{

}
#if 0
void rotate_pattern(char **pattern)
{
	int i, j;
	int row = 0, col = 0;
	int r = M, c = M;
	int prev = pattern[row+1][col];
	int temp;
	while (row < r && col < c) {
		if ((row+1) == r || (col+1) == c)
			break;
		/* shift top row elements */
		for (i = col; i < c; i++) {
			temp = pattern[row][i];
			pattern[row][i] = prev;
			prev = temp;
		}
		/* shift right most column elements */
		for (i = row; i < r; i++) {
			temp = pattern[i][c-1]; 
		}
	
	}

}
#endif
int main()
{

	int i, j;

	while (scanf("%d %d\n", &N, &M) && (N != 0 || M != 0)) {
		char **data = (char **) malloc(N * sizeof (char *));
		for (i = 0; i < N; i++)
			data[i] = (char *) malloc( N * sizeof char);
		char **pattern = (char **) malloc(M * sizeof (char *));
		for (i = 0; i < M; i++)
			pattern[i] = (char *) malloc( M * sizeof char);

		memset(data, 0, sizeof data);
		memset(pattern, 0, sizeof pattern);
		
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (j != N -1)
					scanf("%c", data[i][j]);
				else
					scanf("%c\n", data[i][j]);
			}
		}
	
		for (i = 0; i < M; i++) {
			for (j = 0; j < M; j++) {
				if (j != M -1)
					scanf("%c", pattern[i][j]);
				else
					scanf("%c\n", pattern[i][j]);
			}
		}
		
		for (i = 0; i < 3; i++) {
			/* rotate pattern by i * 90 */
			rotate_pattern(pattern, i);
			int match = match_pattern(data, pattern);
			if (i < 2)
				printf("%d ", match);
			else
				printf("%d\n", match);
		}
	}
	return 0;
}
