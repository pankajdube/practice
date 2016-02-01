#include <cstdio>

using namespace std;

int main()
{
	unsigned long SZ, P;
	while (scanf("%ld %ld\n", &SZ, &P) && (SZ != 0 || P != 0)) {
		unsigned long line, column;
		line = column = -1;
		unsigned long maxvalue = SZ * SZ;
		if (P == 1) {
			line = column = (SZ + 1) / 2;
			printf("Line = %d, column = %d.\n", line, column);
		} else if (P == maxvalue) {
			printf("Line = %d, column = %d.\n", SZ, SZ);
		} else {
			unsigned long r = 0;
			unsigned long start, end;
			/* first find in which ring P lies */
			for (unsigned long i = SZ; i > 1; i-=2) {
				start = i * i;
				end = 1 + start - (i-1) * 4;
				if (end <= P && P <= start)
					break;
				r++;
			}
			int found = 0;

			/* find the position of P in this ring */
			while (start >= end) {
				line = column = SZ -r;

				/* check rightmost column of the ring */
				for (; line > r + 1; line--) {
					if (start == P) {
						found = 1;
						break;
					} else
						start--;
				}
				/* if we found element break the loop */
				if (found)
					break;

				/* check bottom most line of the ring */
				for (; column > r + 1; column--) {
					if (start == P) {
						found = 1;
						break;
					} else
						start--;
				}
				/* if we found element break the loop */
				if (found)
					break;
				/* check left most column of the ring */
				for (; line < SZ -r; line++) {
					if (start == P) {
						found = 1;
						break;
					} else
						start--;
				}
				/* if we found element break the loop */
				if (found)
					break;
				/* check top most line of the ring */
				for (; column < SZ -r ; column++) {
					if (start == P) {
						found = 1;
						break;
					} else
						start--;
				}
				/* if we found element break the loop */
				if (found)
					break;
			}
			printf("Line = %d, column = %d.\n", line, column);
		}
	}
	//printf("\n");
	return 0;
}
