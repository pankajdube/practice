#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

#define MAX_XY 1000
#define MAX_DIST 1500
/* DO NOT FORGOT TO REMOVE BEFORE SUBMISSION */
//#define DEBUG_LOCAL

struct Student
{
	int x;
	int y;
	char name[20];
	bool paired;
};

vector<Student> students;

#ifdef DEBUG_LOCAL
void printdata()
{
	for (int i = 0; i < students.size(); i++) {
		printf("%s %d %d\n", students[i].name, students[i].x, students[i].y);
	}
}
#endif

float findDistance(int x1, int y1, int x2, int y2)
{
	float dist = sqrt((pow((x2-x1), 2) + pow((y2-y1),2)));
	return dist;	
}

int main()
{
	int N;
	float minDistanceSum;
	int caseId = 1;	
	while (scanf("%d\n", &N) && N != 0) {
		minDistanceSum = 0;
		students.clear();
		for (int i = 0; i < (2 * N); i++) {
			struct Student s;
			scanf("%s %d %d\n", s.name, &s.x, &s.y);
			s.paired = false;
			students.push_back(s);
		}

		for (int i = 0; i < N; i++) {
			float minDist = MAX_DIST;
			int k = -1;
			for (int j = i+1; j < (2 *N); j++) {
				if (!students[j].paired) {
					float dij = findDistance(students[i].x, students[i].y, students[j].x, students[j].y);
					if (dij < minDist) {
						minDist = dij;
						k = j;
					}
				}
			}
		if (k != -1) {
			printf("Group: [%d - %d] distance: %.2f\n", i, k, minDist);
			students[i].paired = true;
			students[k].paired = true;
			minDistanceSum += minDist;
		}
		}
		printf("Case %d: %.2f\n", caseId++, minDistanceSum);
	}

#ifdef DEBUG_LOCAL
	printdata();
#endif

	return 0;
}
