#include <stdio.h>

#define MAXROW 200
#define MAXCOL 200
#define CHARPERLINE 50
#define EOFILE	'#'
#define BTYPE 'B'
#define DTYPE 'D'

char data[MAXROW * MAXCOL];
int dlen, drow, dcol;
char pdata[MAXROW * MAXCOL];
int plen;

/* functions to print values of scanned data elements */
void printDataElements(char* data, int length)
{
	int i;
	printf("Printing %d dataelements\n", length);
	for (i = 0; i < length; i++) {
		if ((i+1) % CHARPERLINE  == 0)
			printf("\n");
		printf("%c", data[i]);
	}
	printf("\n");
}

void printDataElements2(char *data, int row, int col)
{
#if 1
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%c", data[i*col+j]);
		}
		printf("\n");
	}
#endif
}

char decodeSubData(char* data, int top, int left, int row, int col)
{
	int i, j;
	int r, c;
	int sum = 0;
	r = row + top;
	c = col + left;
	for (i = top; i < r; i++) {
			for (j = left; j < c; j++) {
				if (data[i*dcol+j] == '1')
					sum++;
			}
	}
	
	if (sum == 0)
		return '0';
	else if (sum == row * col)
		return '1';
	else 
		return 'D';
}

void decodeBtoD(char* data, int top, int left, int row, int col)
{
	int oddrow, oddcol;
	int newrow, newcol;
	char datatype;

	datatype = decodeSubData(data, top, left, row, col);

	if (datatype == '1' || datatype == '0')
			printf("%c", datatype);
	else {
			printf("%c", datatype);
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

			if (row > 1 && col == 1) {
					//Decode TL
					decodeBtoD(data, top, left, newrow, newcol);
					//Decode BL
					decodeBtoD(data, top+newrow, left, row-newrow, newcol);
			} else if (row == 1 && col > 1) {
					//Decode TL
					decodeBtoD(data, top, left, newrow, newcol);
					//Decode TR
					decodeBtoD(data, top, left+newcol, newrow, col-newcol);
			} else {
					//Decode TL
					decodeBtoD(data, top, left, newrow, newcol);
					//Decode TR
					decodeBtoD(data, top, left+newcol, newrow, col-newcol);
					//Decode BL
					decodeBtoD(data, top+newrow, left, row-newrow, newcol);
					//Decode BR
					decodeBtoD(data, top+newrow, left+newcol, row-newrow, col-newcol);
			}
	}
}

void decodeDtoB(char* data, int index, int top, int left, int row, int col)
{
	int oddrow, oddcol;
	int newrow, newcol;
		char code;
		int i, j;
		code = data[index];
		if (code == '1') {
				for (i = 0; i < row; i++)
						for (j = 0; j < col; j++)
							printf("1");
		} else if (code == '0') {
				for (i = 0; i < row; i++)
						for (j = 0; j < col; j++)
							printf("0");
		} else if (code == 'D') {
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
			if (row > 1 && col == 1) {
					//Decode TL
					decodeDtoB(index++, data, top, left, newrow, newcol);
					//Decode BL
					decodeDtoB(index++, data, top+newrow, left, row-newrow, newcol);
			} else if (row == 1 && col > 1) {
					//Decode TL
					decodeDtoB(data, top, left, newrow, newcol);
					//Decode TR
					decodeDtoB(data, top, left+newcol, newrow, col-newcol);
			} else {
					//Decode TL
					decodeDtoB(data, top, left, newrow, newcol);
					//Decode TR
					decodeDtoB(data, top, left+newcol, newrow, col-newcol);
					//Decode BL
					decodeDtoB(data, top+newrow, left, row-newrow, newcol);
					//Decode BR
					decodeDtoB(data, top+newrow, left+newcol, row-newrow, col-newcol);
			}
		}
}

void scanDataelements(char type)
{
	int count = 1;
	char newline;

	dlen = 0;
	scanf("%c", &data[dlen]);
	while (data[dlen] != '\n') {
		dlen++;
		scanf("%c", &data[dlen]);
		if ((dlen+1) % CHARPERLINE == 0)
			scanf("%c\n", &newline);
	}
}

int main()
{
	int i, j;
	char type;
	char *localdata;
	//scan the first character
	scanf("%c", &type);
	//process untill we hit EOFILE character
	while (type != EOFILE) {
		//scan row and col numbers
		scanf("%d %d\n", &drow, &dcol);
		//scan elements of given type of data
		scanDataelements(type);
		if (type == BTYPE) {
				decodeBtoD(data, 0, 0, drow, dcol);
		} else if (type == DTYPE) {
				//decodeDtoB(data, drow, dcol);
		}

		scanf("\n%c", &type);
	}
	return 0;
}
