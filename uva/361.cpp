#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 201
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))

using namespace std;

struct point
{
	int x;
	int y;
};

const char *state [] = {"neither", "safe", "robbed"};

int C, R, O;
struct point robbers[MAXN];
struct point cops[MAXN];
struct point citizens[MAXN];
const char *citizen_state[MAXN];

inline int area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs(x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2));
}

bool is_inbetween(int x1, int y1, int x2, int y2, int x, int y)
{
	int minX, maxX, minY, maxY;
	maxX = max(x1, x2);
	minX = (x1 + x2) - maxX;
	maxY = max(y1, y2);
	minY = (y1 + y2) - maxY;
	if (x <= maxX && x >= minX) {
		if (y <= maxY && y >= minY)
			return true;
	}
	return false;
}

bool is_inside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
	int A, A1, A2, A3;
	
	A = area(x1, y1, x2, y2, x3, y3);
	if (A == 0) {
		if ((x1 == x && y1 == y) || (x2 == x && y2 == y) || (x3 == x && y3 == y))
			return true;
	}
	printf("A: %d Triangle(%d, %d, %d, %d, %d, %d)\n", A, x1, y1, x2, y2, x3, y3);	
	A1 = area(x, y, x2, y2, x3, y3);
	if (A1 == 0 && is_inbetween(x2, y2, x3, y3, x, y))
		return true;
	printf("A1: %d Triangle(%d, %d, %d, %d, %d, %d)\n", A1, x, y, x2, y2, x3, y3);	
	A2 = area(x1, y1, x, y, x3, y3);
	if (A2 == 0 && is_inbetween(x1, y1, x3, y3, x, y))
		return true;
	printf("A2: %d Triangle(%d, %d, %d, %d, %d, %d)\n", A2, x1, y1, x, y, x3, y3);	
	A3 = area(x1, y1, x2, y2, x, y); 
	if (A3 == 0 && is_inbetween(x1, y1, x2, y2, x, y))
		return true;
	printf("A3: Triangle(%d: %d, %d, %d, %d, %d, %d)\n", A3, x1, y1, x2, y2, x, y);	
	if (A == 0 && (A1 == 0 || A2 == 0 || A3 == 0))
		return true; 
	return (A == A1 + A2 + A3);
}

bool is_citizen_safe(int x, int y)
{
	int i;
	for (i = 0; i < C-2; i++) {
		if (is_inside(cops[i].x, cops[i].y, cops[i+1].x, cops[i+1].y, cops[i+2].x, cops[i+2].y, x, y))
			return true;
	}
	return false;
}

bool is_citizen_robbed(int x, int y)
{
	int i;
	for (i = 0; i < R-2; i++) {
		if (is_inside(robbers[i].x, robbers[i].y, robbers[i+1].x, robbers[i+1].y, robbers[i+2].x, robbers[i+2].y, x, y))
			return true;
	}
	return false;
}

int main()
{
	int i, id = 1;
	while (scanf("%d %d %d\n", &C, &R, &O) && (C+R+O != 0)) {
		memset(robbers, 0, sizeof robbers);
		memset(cops, 0, sizeof cops);
		memset(citizens, 0, sizeof citizens);
		/* scan coordinates of cops */
		for (i = 0; i < C; i++)
			scanf("%d %d\n", &cops[i].x, &cops[i].y);
		/* scan coordinates of robbers */
		for (i = 0; i < R; i++)
			scanf("%d %d\n", &robbers[i].x, &robbers[i].y);
		/* scan coordinates of citizens */
		for (i = 0; i < O; i++) {
			scanf("%d %d\n", &citizens[i].x, &citizens[i].y);
			if (is_citizen_safe(citizens[i].x, citizens[i].y))
				citizen_state[i] = state[1];
			else {
				if (is_citizen_robbed(citizens[i].x, citizens[i].y))
					citizen_state[i] = state[2];
				else
					citizen_state[i] = state[0];
			}
									
		}
		/* print status of each citizen */
		printf("Data set %d:\n", id++);
		for (i = 0; i < O; i++) {
			printf("\t Citizen at (%d,%d) is %s.\n", citizens[i].x, citizens[i].y, citizen_state[i]);
		}
		printf("\n");
	}	
	return 0;
}
