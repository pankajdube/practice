#include <cstdio>
#include <vector>

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
	bool drawn;
};

struct rectangle right_most_rect;

vector<struct rectangle> rectangles;

inline unsigned int compute_area(struct rectangle rect)
{
	return ((rect.RT.x - rect.LB.x) * (rect.RT.y - rect.LB.y));
}

bool is_overlapping(struct rectangle cr)
{
	bool overlapping = false;
	int i;
	for (i = 0; i < rectangles.size(); i++) {
		struct rectangle r = rectangles[i];
		if ((cr.LB.x >= right_most_rect.RT.x || cr.LB.y >= right_most_rect.RT.y))
			break;
		
//		if (!r.drawn)
//			continue;	
//		printf("Checking (%d %d %d %d) with (%d %d %d %d)\n", cr.LB.x, cr.LB.y, cr.RT.x, cr.RT.y, r.LB.x, r.LB.y, r.RT.x, r.RT.y);
		if ((r.LB.x <= cr.LB.x) && (cr.LB.x < r.RT.x) && (r.LB.y <= cr.LB.y) && (cr.LB.y < r.RT.y)) {
			overlapping = true;
			break;
		}
		if ((r.LB.x < cr.RT.x) && (cr.RT.x <= r.RT.x) && (r.LB.y < cr.RT.y) && (cr.RT.y <= r.RT.y)) {
			overlapping = true;
			break;
		}
		if ((r.LB.x <= cr.LB.x) && (cr.LB.x < r.RT.x) && (cr.LB.y < r.RT.y) && (cr.RT.y > r.LB.y)) {
			overlapping = true;
			break;
		}
		if ((cr.LB.x <= r.LB.x) && (cr.LB.y <= r.LB.y) && (cr.RT.x >= r.RT.x) && (cr.RT.y >= r.RT.y)) {
			overlapping = true;
			break;
		} 
	}
	return overlapping;
}


int main()
{
	int test_cnt, rectangle_cnt;
	unsigned int area;
	int i, j;
	scanf ("%d\n", &test_cnt);
	for (i = 1; i <= test_cnt; i++) {
		area = 0;
		right_most_rect.LB.x = right_most_rect.LB.y = 0; 
		/* clear rectangle vector */
		rectangles.clear();
		/* scan count of rectangles */
		scanf("%d\n", &rectangle_cnt);
		/* scan coordinates of rectangles */
		for (j = 0; j < rectangle_cnt; j++) {
			struct rectangle r;
			scanf("%d %d %d %d\n", &r.LB.x, &r.LB.y, &r.RT.x, &r.RT.y);
			if (right_most_rect.LB.x < r.LB.x)
				right_most_rect = r;
			else if (right_most_rect.LB.y < r.LB.y)
				right_most_rect = r;
			if (j == 0) {
				//r.drawn = true;
				area += compute_area(r);
				rectangles.push_back(r);
			} else if(!is_overlapping(r)) {
					//r.drawn = true;
					area += compute_area(r);
					rectangles.push_back(r);
			}
		}
	
		printf("Case %d: %u\n", i, area);
	};
	printf("\n");	
	return 0;
}
