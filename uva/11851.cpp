#include <cstdio>
#include <cstring>

using namespace std;

/*#define LOCAL_DEBUG */

int g[3][3];

#ifdef LOCAL_DEBUG
void printdata()
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d", g[i][j]);
		}
		printf("\n");
	}
}
#endif

int iszero()
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (g[i][j] > 0)
				return 0;
		}
	}
	return 1;
}

void transform()
{
	int fg[3][3];
	fg[0][0] = (g[0][1] + g[1][0]) % 2;
	fg[0][1] = (g[0][0] + g[1][1] + g[0][2]) % 2;
	fg[0][2] = (g[0][1] + g[1][2]) % 2;
	fg[1][0] = (g[0][0] + g[1][1] + g[2][0]) % 2;
	fg[1][1] = (g[0][1] + g[1][0] + g[1][2] + g[2][1]) % 2;
	fg[1][2] = (g[0][2] + g[1][1] + g[2][2]) % 2;
	fg[2][0] = (g[1][0] + g[2][1]) % 2;
	fg[2][1] = (g[2][0] + g[1][1] + g[2][2]) % 2;
	fg[2][2] = (g[1][2] + g[2][1]) % 2;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			g[i][j] = fg[i][j];
		}
	}
}


int main()
{
	int testcases;
	scanf("%d\n", &testcases);

	while (testcases--) {
		memset(g, 0, sizeof g);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				scanf("%1d", &g[i][j]);
			}
		}
		int index = -1;
		while (!iszero()) {
			transform();
			index++;
		}
		printf("%d\n", index);
	}
}
