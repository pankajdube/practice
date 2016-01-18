#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct task
{
	int idx;
	int time;
	int fine;
};

void printdata(vector<task> &T)
{
	int i;
	printf("%d", T[0].idx);
	for (i = 1; i < T.size(); i++) {
			printf(" ");
			printf("%d", T[i].idx);
	}
	printf("\n");
}

bool compare(const task &t1, const task &t2)
{
	return t1.time * t2.fine < t2.time * t1.fine;
}

int main ()
{
	int cases, nooftasks;
	int i, j;
	scanf("%d\n", &cases);
	for (j = 1; j <= cases; j++) {
			scanf("%d\n", &nooftasks);
			vector<task> T(nooftasks);

			for (i = 0; i < nooftasks; ++i) {
					T[i].idx = i+1;
					scanf("%d %d\n",&T[i].time, &T[i].fine);
			}
			stable_sort(T.begin(), T.end(), compare);
			printdata(T);
			if (j != cases)
				printf("\n");
	}

	return 0;
}
