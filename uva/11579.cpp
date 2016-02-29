#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 100000 + 10
using namespace std;
double sides[MAXN];
int sides_cnt;

inline double triangle_area(double a, double b, double c)
{
	double p;
	double area;
	if (((a + b) < c) || ((b + c) < a) || ((a + c) < b))
		return 0;
	p = (a + b + c) / 2.0;
	area = sqrt(p * (p - a) * (p - b) * (p - c));
	return area; 
}

int main()
{
	int test_cnt;
	int i, j, k;
	double area, max_area;

	scanf ("%d\n", &test_cnt);
	for (i = 1; i <= test_cnt; i++) {
		area = 0.0;
		max_area = 0.0;
		scanf ("%d\n", &sides_cnt);

		for (j = 0; j < sides_cnt; j++) {
			scanf("%lf", &sides[j]);
		}
		sort(sides, sides + sides_cnt);
		for (k = sides_cnt - 1; k >= 2; k--) {
			area  = triangle_area(sides[k], sides[k-1], sides[k-2]);
			if (area > max_area)
				max_area = area;
		}
		printf("%.2lf\n", max_area);
	}
	
}
