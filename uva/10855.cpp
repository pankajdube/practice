#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int N, M;

int match_pattern(char **data, char **pattern)
{
	int match;
	int count = 0;
	int i, j, k, l;
	for (i = 0; i < N-M+1; i++) {
		for (j = 0; j < N-M+1; j++) {
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

void rotate_pattern(char **source, char **dest)
{
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			dest[i][j] = source[M -1 -j][i];
		}
	}
}

int main()
{

	int i, j;

	while (scanf("%d %d\n", &N, &M) && (N != 0 || M != 0)) {
		char **data = (char **) malloc(N * sizeof (char *));
		for (i = 0; i < N; i++)
			data[i] = (char *) malloc(N * sizeof (char));

		char **pattern = (char **) malloc(M * sizeof (char *));
		char **rot_pattern = (char **) malloc(M * sizeof (char *));
		for (i = 0; i < M; i++) {
			pattern[i] = (char *) malloc(M * sizeof (char));
			rot_pattern[i] = (char *) malloc(M * sizeof (char));
		}

		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (j != N -1)
					scanf("%c", &data[i][j]);
				else
					scanf("%c\n", &data[i][j]);
			}
		}

		for (i = 0; i < M; i++) {
			for (j = 0; j < M; j++) {
				if (j != M -1) 
					scanf("%c", &pattern[i][j]);
				else
					scanf("%c\n", &pattern[i][j]);
			}
		}
		for (int k = 0; k < 4; k++) {
			if ( k != 0) {
				rotate_pattern(pattern, rot_pattern);
				for (i = 0; i < M; i++) {
					for (j = 0; j < M; j++) {
						pattern[i][j] = rot_pattern[i][j];
					}
				}
			}
			int match = match_pattern(data, pattern);
			if (k < 3)
				printf("%d ", match);
			else
				printf("%d\n", match);
		}

		for (i = 0; i < M; i++) {
			free(pattern[i]);
		}
		free(pattern);
		for (i = 0; i < M; i++) {
			free(rot_pattern[i]);
		}
		free(rot_pattern);
		for (i = 0; i < N; i++) {
			free(data[i]);
		}
		free(data);
	}
	return 0;
}
