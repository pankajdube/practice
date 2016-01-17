#include <stdio.h>

#define MAXCHARPERLINE 12
char data[200];
int len;

void decode(int top, int left, int row, int col)
{
	int oddrow, oddcol;
	int newrow, newcol;
	int newtop, newleft;
//	printf("decode(top: %d: left: %d, row: %d, col: %d)\n", top, left, row, col);

	if (row > 1 && col == 1) {
			newcol = col;
			newrow = row / 2;
			oddrow = row % 2;
			oddcol = col;
	} else if (row == 1 && col > 1) {
			newrow = row;
			newcol = col / 2;
			oddrow = row;
			oddcol = col % 2;
	} else {
			oddrow = row % 2;
			oddcol = col % 2;
			newrow = row / 2;
			newcol = col / 2;
	}

//	printf("newrow: %d newcol: %d oddrow: %d oddcol: %d\n", newrow, newcol, oddrow, oddcol);
	if (row < 0 || col < 0) {
		printf("ERROR\n");	
		return;
	}
	if (row == 1 && col == 1) {
		printf("cell[%d, %d]\n", top, left);
		return;
	}

	if (oddrow && oddcol) {
		//Both Row and Col are Odd numbers
		newrow++;
		newcol++;
	} else if (oddrow && !oddcol) {
		//Rows are odd but Col are even
			if (row != 1)	
					newrow++;
	} else if (!oddrow && oddcol) {
			//Rows are even and cols are odd
			if (col != 1)
					newcol++;
	} else if (!oddrow && !oddcol) {
		//Row and Col both are even
	}

//	printf("After: newrow: %d newcol: %d\n", newrow, newcol);
	if (row > 1 && col == 1) {
			//Decode TL
			decode(top, left, newrow, newcol);
			//Decode BL
			decode(top+newrow, left, row-newrow, newcol);
	} else if (row == 1 && col > 1) {
			//Decode TL
			decode(top, left, newrow, newcol);
			//Decode TR
			decode(top, left+newcol, newrow, col-newcol);
	} else {
			//Decode TL
			decode(top, left, newrow, newcol);
			//Decode TR
			decode(top, left+newcol, newrow, col-newcol);
			//Decode BL
			decode(top+newrow, left, row-newrow, newcol);
			//Decode BR
			decode(top+newrow, left+newcol, row-newrow, col-newcol);
	}
}

int main()
{
	int i;
	char ch;
	len = 0;
#if 0
	i = scanf("%c", &data[len]);
	printf("scanned data length: %d\n", i);
	while (data[len] != '\n') {
		len++;
		printf("len: %d\n", len);
		scanf("%c", &data[len]);
		if ((len+1) % MAXCHARPERLINE == 0)
				scanf("%c\n", &ch);
	}

	printf("Total length of data is: %d\n", len);
	for (i = 0; i < len; i++)
		printf("%c", data[i]);
#endif
	decode(0, 0, 5, 5);
	return 0;
}
