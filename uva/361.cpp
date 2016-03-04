#include <cstdio>
#include <cstdlib>
#include <cstring>
#define DEBUG_LOCAL
#undef DEBUG_LOCAL
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
	if (x > maxX || x < minX || y > maxY || y < minY)
		return false;

	return true;
}

bool is_inside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
	int A, A1, A2, A3;
	
	A = area(x1, y1, x2, y2, x3, y3);
	if (A == 0) {
		if (x1 == x2 && y1 == y2 && x2 == x3 && y2 == y3) {
			if(x1 == x && y1 == y)
				return true;
			else
				return false;
		}
		
		if ((x1 == x && y1 == y) || (x2 == x && y2 == y) || (x3 == x && y3 == y))
			return true;
	}
#ifdef DEBUG_LOCAL
	printf("A: %d Triangle(%d, %d, %d, %d, %d, %d)\n", A, x1, y1, x2, y2, x3, y3);
#endif	
	A1 = area(x, y, x2, y2, x3, y3);
	if (A1 == 0 && is_inbetween(x2, y2, x3, y3, x, y))
		return true;
#ifdef DEBUG_LOCAL
	printf("A1: %d Triangle(%d, %d, %d, %d, %d, %d)\n", A1, x, y, x2, y2, x3, y3);
#endif	
	A2 = area(x1, y1, x, y, x3, y3);
	if (A2 == 0 && is_inbetween(x1, y1, x3, y3, x, y))
		return true;
#ifdef DEBUG_LOCAL
	printf("A2: %d Triangle(%d, %d, %d, %d, %d, %d)\n", A2, x1, y1, x, y, x3, y3);
#endif	
	A3 = area(x1, y1, x2, y2, x, y); 
	if (A3 == 0 && is_inbetween(x1, y1, x2, y2, x, y))
		return true;
#ifdef DEBUG_LOCAL
	printf("A3: Triangle(%d: %d, %d, %d, %d, %d, %d)\n", A3, x1, y1, x2, y2, x, y);
#endif	
//	if (A == 0 && (A1 == 0 || A2 == 0 || A3 == 0))
	if ((A + A1 + A2 + A3) == 0)
		return false;
	return (A == A1 + A2 + A3);
}

bool is_citizen_safe(int x, int y)
{
	int i, j, k;
	for (i = 0; i < C-2; i++) {
		for (j = i+1; j < C-1; j++) {
			for (k = j+1; k < C; k++) {
				if (is_inside(cops[i].x, cops[i].y, cops[j].x, cops[j].y, cops[k].x, cops[k].y, x, y))
					return true;
			}
		}
	}
	return false;
}

bool is_citizen_robbed(int x, int y)
{
	int i, j, k;
	for (i = 0; i < C-2; i++) {
		for (j = i+1; j < C-1; j++) {
			for (k = j+1; k < C; k++) {
				if (is_inside(robbers[i].x, robbers[i].y, robbers[j].x, robbers[j].y, robbers[k].x, robbers[k].y, x, y))
					return true;
			}
		}
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
		/* print status of each citizen */
		printf("Data set %d:\n", id++);
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
			printf("     Citizen at (%d,%d) is %s.\n", citizens[i].x, citizens[i].y, citizen_state[i]);
		}
		printf("\n");
	}	
	return 0;
}
