#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXLINE 100000

struct Line
{
	signed long left;
	signed long right;
};

Line line[MAXLINE];

int compare(const void* p1, const void *p2)
{
	Line *L1 = (Line *)p1;
	Line *L2 = (Line *)p2;

	if (L1->left < L2->left)
		return -1;
	else
		return 1;
}

int main()
{
	int testcase, M;
	signed long l, r;
	int curLeft, curCoverage;
	int count;

	scanf("%d\n", &testcase); 
	
	while (testcase--) {
		count = 0;
		scanf("%d\n", &M);
		do {
			scanf("%ld %ld\n", &l, &r);
			line[count].left = l;
			line[count].right = r;
			count++;
		} while (l != 0 || r != 0);

		/* sort the line array according to left point position */
		qsort(line, count, sizeof(line[0]), compare);
		curLeft = 0;
		curCoverage = 0;
		unsigned int i = 0;
		vector<Line> selectedLines;

		while (curCoverage < M) {
			int newLeft = curLeft;
			int selected = -1;
			for (; i < count; i++) {
				if (line[i].left > curLeft)
					break;
				else if (line[i].right >= newLeft) {
					newLeft = line[i].right;
					selected = i;
				}
			}

			if (selected == -1)
				break;

			selectedLines.push_back(line[selected]);
			curLeft = newLeft;
			curCoverage = curLeft;
		}

		if (curCoverage >= M) {
			printf("%ld\n", selectedLines.size());
			for (i = 0; i < selectedLines.size(); i++) {
				printf("%ld %ld\n", selectedLines[i].left, selectedLines[i].right);
			}
		}
		else {
			printf("0\n");
		}

		if (testcase)
			printf("\n");
	};
}
