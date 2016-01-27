#include <cstdio>
#include <cstring>

using namespace std;
/*#define LOCAL_DEBUG*/
#define MAX 3000

int data[MAX];
int diff[MAX];

int main()
{
	int n, i;
	int abs_diff;
	int is_jolly;
	while (scanf("%d", &n) != EOF) {
		is_jolly = 1;
		abs_diff = 0;
		memset(data, 0, sizeof data);
		memset(diff, 0, sizeof diff);
		for (i = 0; i < n; i++) {
			if (i != n - 1)
				scanf("%d", &data[i]);
			else
				scanf("%d\n", &data[i]);

			if (i > 0) {
				abs_diff = data[i] - data[i-1];
				if (abs_diff < 0)
					abs_diff = 0 - abs_diff;
				if (abs_diff < n)
					diff[abs_diff] = 1;
			}
		}
#ifdef LOCAL_DEBUG
		printf("%d ", n);
		/* print the data */
		for (i = 0; i < n; i++) {
			if (i != n -1)
				printf("%d ", data[i]);
			else	
				printf("%d\n", data[i]);
		}
#endif
		
		for (i = 1; i < n; i++) {
			if (!diff[i]) {
				is_jolly = 0;
				break;
			}
		}
		if (is_jolly)
			printf("Jolly\n");
		else
			printf("Not jolly\n");	
	}
	
	return 0;
}
