#include <cstdio>
#include <cstring>

using namespace std;

#define MAXSIZE 100000
int soldiers[MAXSIZE];

int main()
{
	int i, S, B, L, R;
	int idx;
	while (scanf("%d %d\n", &S, &B) && (S != 0 || B != 0)) {
		memset(soldiers, 1, sizeof soldiers);
		for (i = 0; i < B; i++) {
			/* scan the killed soldier boundries */
			scanf("%d %d\n", &L, &R);
			/* mark killed soldiers */
			for (int j = L; j <=R; j++)
				soldiers[j] = 0;
			idx = -1;
			/* get index of first surviving soldier to the left of L */
			for (int k = L - 1; k >= 1; k--) {
				if (soldiers[k]) {
					idx = k;
					break;
				}
			}
			/* print the first surviving soldier */
			if (idx == -1)
				printf("* ");
			else	
				printf("%d ", idx);
			idx = -1;
			/* get index of first surviving soldier to the right of R */
			for (int k = R + 1; k <=S; k++) {
				if (soldiers[k]) {
					idx = k;
					break;
				}
			}
			/* print the first surviving soldier */
			if (idx == -1)
				printf("*\n");
			else	
				printf("%d\n", idx);

		}
		/* at the end print '-' */
		printf("-\n");
	}
	return 0;
}
