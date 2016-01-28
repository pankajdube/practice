#include <cstdio>
#include <cstring>

using namespace std;

#define MAXSIZE 100000
int left[MAXSIZE];
int right[MAXSIZE]; 

int main()
{
	int i, S, B, L, R;
	while (scanf("%d %d\n", &S, &B) && (S != 0 || B != 0)) {
		memset(left, -1, sizeof left);
		memset(right, -1, sizeof right);
		/* init left and right buddies */
		for (i = 1; i <= S; i++) {
			if (i != 1)
				left[i] = i - 1;
			if (i != S)
				right[i] = i + 1;
		}

		for (i = 0; i < B; i++) {
			/* scan the killed soldier boundries */
			scanf("%d %d\n", &L, &R);
			/* print the first left surviving soldier */
			if (left[L] == -1)
				printf("* ");
			else	
				printf("%d ", left[L]);

			/* print the first right surviving soldier */
			if (right[R] == -1)
				printf("*\n");
			else	
				printf("%d\n", right[R]);
		
			/* update left and right buddies of remaining soldier */
			right[left[L]] = right[R];
			left[right[R]] = left[L];
		}
		/* at the end print '-' */
		printf("-\n");
	}
	return 0;
}
