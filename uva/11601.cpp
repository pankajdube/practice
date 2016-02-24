#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXL 205

using namespace std;

struct point
{
	int x;
	int y;
};

struct rectangle
{
	struct point LB;
	struct point RT;
};

int rectangles[MAXL][MAXL];

inline int compute_area(struct rectangle rect)
{
	return ((rect.RT.x - rect.LB.x) * (rect.RT.y - rect.LB.y));
}

bool is_overlapping(struct rectangle cr)
{
	int i, j;
	for (i = cr.LB.x; i < cr.RT.x; i++) {
		for (j = cr.LB.y; j < cr.RT.y; j++) {
			if (rectangles[i][j])
				return true;
		}
	}
	for (i = cr.LB.x; i < cr.RT.x; i++) {
		for (j = cr.LB.y; j < cr.RT.y; j++) {
			rectangles[i][j] = 1;
		}
	}
	return false;
}


int main()
{
	int test_cnt, rectangle_cnt;
	int area;
	int i, j, k;
	scanf ("%d\n", &test_cnt);
	for (i = 1; i <= test_cnt; i++) {
		area = 0;
		memset(rectangles, 0, sizeof rectangles);
		/* scan count of rectangles */
		scanf("%d\n", &rectangle_cnt);
		/* scan coordinates of rectangles */
		for (j = 0; j < rectangle_cnt; j++) {
			struct rectangle r;
			scanf("%d %d %d %d\n", &r.LB.x, &r.LB.y, &r.RT.x, &r.RT.y);
			r.LB.x += 100;
			r.LB.y += 100;
			r.RT.x += 100;
			r.RT.y += 100;
			/* shift  rect by 100 on +x axis and +y axis */
			if(!is_overlapping(r))
				area += compute_area(r);
		}
	
		printf("Case %d: %d\n", i, area);
	};
	return 0;
}
