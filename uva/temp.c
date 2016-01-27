#include <cstdio>

struct Student
{
	char name[20];
	int rollno;
};

int main()
{
	int i, N;
	while (scanf("%d\n", &N) && N != 0) {
		for (i = 0; i < N; i++) {
			Student s;
			scanf ("%s %d\n", s.name, &s.rollno);
			printf("StudentName: %s, StudentRollNO: %d\n", s.name, s.rollno);
		}
	}
}
