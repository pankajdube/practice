#include <cstdio>
#include <cmath>

#undef LOCAL_DEBUG

void sort_coordinates(float xy[][2])
{
	int i, j;
	float temp[2];
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2 - i; j++) {
			if (xy[j][1] >= xy[j+1][1]) {
				temp[0] = xy[j][0];
				temp[1] = xy[j][1];
				xy[j][0] = xy[j+1][0];
				xy[j][1] = xy[j+1][1];
				xy[j+1][0] = temp[0];
				xy[j+1][1] = temp[1];
			}
		}
	}
}

int main()
{
	int i, Yi;
	float sum, m1, m2;
	float x1, x2;
	float xy[3][2];
	int Ymin, Ymax, Xmin, Xmax;

	int Answer;
	do 
	{
		Answer = 0;
		Xmin = Ymin = 0;
		Xmax = Ymax = 0;
		sum = 0.0;
		x1 = 0.0;
		x2 = 0.0;
		/* scan triangle points */
		for (i = 0; i < 3; i++) {
			if (i < 2)
				scanf("%f %f", &xy[i][0], &xy[i][1]);
			else
				scanf("%f %f\n", &xy[i][0], &xy[i][1]);
			sum += xy[i][0] + xy[i][1];
		}
		/* end point scanned */
		if (sum == 0.0) {
			printf("\n");
			break;
		}
		/* sort coordinates in increasing order of y */
		sort_coordinates(xy);
		/* check scan line boundries */
		if (xy[0][1] == xy[1][1]) {
			Ymin = ceil(xy[0][1]);
			Ymax = floor(xy[2][1]);
			m1 = (xy[2][0] - xy[0][0])/(xy[2][1] - xy[0][1]);
			m2 = (xy[2][0] - xy[1][0])/(xy[2][1] - xy[1][1]);
			/* find intersection of y = Yi with (X2,Y2)->(X0,Y0) and (X2,Y2)->(X1,Y1) */
			for (Yi = Ymin; Yi <= Ymax; Yi++) {
				x1 = m1 * (Yi - xy[0][1]) + xy[0][0];
				x2 = m2 * (Yi - xy[1][1]) + xy[1][0];
				if (x1 <= x2) {
					Xmin = ceil(x1);
					Xmax = floor(x2);
				} else {
					Xmin = ceil(x2);
					Xmax = floor(x1);
				}
				Answer += (Xmax - Xmin + 1);
			}
		} else {
			/* find intersection of y = Yi with (X2,Y2)->(X0,Y0) and (X0,Y0)->(X1,Y1) */
			Ymin = ceil(xy[0][1]);
			Ymax = floor(xy[1][1]);
			m1 = (xy[2][0] - xy[0][0])/(xy[2][1] - xy[0][1]);
			m2 = (xy[1][0] - xy[0][0])/(xy[1][1] - xy[0][1]);
			for (Yi = Ymin; Yi <= Ymax; Yi++) {
				x1 = m1 * (Yi - xy[0][1]) + xy[0][0];
				x2 = m2 * (Yi - xy[1][1]) + xy[1][0];
				if (x1 <= x2) {
					Xmin = ceil(x1);
					Xmax = floor(x2);
				} else {
					Xmin = ceil(x2);
					Xmax = floor(x1);
				}
				Answer += (Xmax - Xmin + 1);
			
			}
			/* find intersection of y = Yi with (X2,Y2)->(X0,Y0) and (X2,Y2)->(X1,Y1) */
			Ymin = ceil(xy[1][1]);
			Ymax = floor(xy[2][1]);
			m1 = (xy[2][0] - xy[0][0])/(xy[2][1] - xy[0][1]);
			m2 = (xy[2][0] - xy[1][0])/(xy[2][1] - xy[1][1]);
			/* find intersection of y = Yi with (X2,Y2)->(X0,Y0) and (X2,Y2)->(X1,Y1) */
			for (Yi = Ymin; Yi <= Ymax; Yi++) {
				x1 = m1 * (Yi - xy[0][1]) + xy[0][0];
				x2 = m2 * (Yi - xy[1][1]) + xy[1][0];
				if (x1 <= x2) {
					Xmin = ceil(x1);
					Xmax = floor(x2);
				} else {
					Xmin = ceil(x2);
					Xmax = floor(x1);
				}
				Answer += (Xmax - Xmin + 1);
			}
		}
		
#ifdef LOCAL_DEBUG
		for (i = 0; i < 3; i++) {
			if (i < 2)
				printf("%.1f %.1f ", xy[i][0], xy[i][1]);
			else
				printf("%.1f %.1f\n", xy[i][0], xy[i][1]);
		}
#endif
		printf("%4d\n", Answer);
	} while (1);
	return 0;
}
