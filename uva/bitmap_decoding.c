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
			plen++;
			if (plen >= CHARPERLINE) {
					printf("\n");
					plen = 0;
			}
		}
		//printf("\n");
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
	plen++;
	if (plen > CHARPERLINE) {
					printf("\n");
					plen = 0;
	}


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
					/*Both Row and Col are Odd numbers*/
					if (row != 1)
						newrow++;
					if (col != 1)
						newcol++;
			} else if (oddrow && !oddcol) {
					/* Rows are odd but Col are even */
					if (row != 1)	
							newrow++;
			} else if (!oddrow && oddcol) {
					/* Rows are even and cols are odd */
					if (col != 1)
							newcol++;
			} else if (!oddrow && !oddcol) {
					/* Row and Col both are even */
			}

			if (row > 1 && col == 1) {
					/* Decode TL */
					decodeBtoD(data, top, left, newrow, newcol);
					/* Decode BL */
					decodeBtoD(data, top+newrow, left, row-newrow, newcol);
			} else if (row == 1 && col > 1) {
					/* Decode TL */
					decodeBtoD(data, top, left, newrow, newcol);
					/* Decode TR */
					decodeBtoD(data, top, left+newcol, newrow, col-newcol);
			} else {
					/* Decode TL */
					decodeBtoD(data, top, left, newrow, newcol);
					/* Decode TR */
					decodeBtoD(data, top, left+newcol, newrow, col-newcol);
					/* Decode BL */
					decodeBtoD(data, top+newrow, left, row-newrow, newcol);
					/* Decode BR */
					decodeBtoD(data, top+newrow, left+newcol, row-newrow, col-newcol);
			}
	}
}

int decodeDtoB(int index, char *data, int top, int left, int row, int col)
{
	int oddrow, oddcol;
	int newrow, newcol;
	char code;
	int i, j;
	int r, c;
	r = row + top;
	c = col + left;
	code = data[index];
	/* printf("decodeDtoB: index: %d, top: %d left: %d row: %d col: %d\n", index, top, left, row, col); */
		if (code == '1') {
			for (i = top; i < r; i++) {
						for (j = left; j < c; j++) {
							pdata[i*dcol+j] = '1';
						}
			}
				return index;
		} else if (code == '0') {
					for (i = top; i < r; i++) {
									for (j = left; j < c; j++) {
										pdata[i*dcol+j] = '0';
									}
					}
				return index;
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
					/* Both Row and Col are Odd numbers */
				if (row != 1)
					newrow++;
				if (col != 1)
					newcol++;
			} else if (oddrow && !oddcol) {
					/* Rows are odd but Col are even */
					if (row != 1)	
							newrow++;
			} else if (!oddrow && oddcol) {
					/* Rows are even and cols are odd */
					if (col != 1)
							newcol++;
			} else if (!oddrow && !oddcol) {
					/* Row and Col both are even */
			}
			if (row > 1 && col == 1) {
					/* Decode TL */
					index = decodeDtoB(++index, data, top, left, newrow, newcol);
					/* Decode BL */
					index = decodeDtoB(++index, data, top+newrow, left, row-newrow, newcol);
			} else if (row == 1 && col > 1) {
					/* Decode TL */
					index = decodeDtoB(++index, data, top, left, newrow, newcol);
					/* Decode TR */
					index = decodeDtoB(++index, data, top, left+newcol, newrow, col-newcol);
			} else {
					/* Decode TL */
					index = decodeDtoB(++index, data, top, left, newrow, newcol);
					/* Decode TR */
					index = decodeDtoB(++index, data, top, left+newcol, newrow, col-newcol);
					/* Decode BL */
					index = decodeDtoB(++index, data, top+newrow, left, row-newrow, newcol);
					/* Decode BR */
					index = decodeDtoB(++index, data, top+newrow, left+newcol, row-newrow, col-newcol);
			}
			return index;
		}

		return index;
}

void scanDataelements(char type, int row, int col)
{
	char newline;
	int total;
	if (type == DTYPE) {
	dlen = 0;
	scanf("%c", &data[dlen]);
		while (data[dlen] != '\n') {
			dlen++;
			if (dlen % CHARPERLINE == 0)
					scanf("%c\n", &newline);
			scanf("%c", &data[dlen]);

		}
	}

	if (type == BTYPE) {
		total = row * col;
		dlen = 0;
		while (dlen < total){
			scanf("%c", &data[dlen]);
			if (data[dlen] != '\n')
				dlen++;
		}
	}

}

int main()
{
	char type;
	/* scan the first character */
	scanf("%c", &type);
	/* process until we hit EOFILE character */
	while (type != EOFILE) {
		plen = 0;
		/* scan row and col numbers */
		scanf("%d %d\n", &drow, &dcol);
		//printf("%c: %d: %d\n", type, drow, dcol);
		/* scan elements of given type of data */
		if (drow != 0 && dcol != 0)
			scanDataelements(type, drow, dcol);
		if (type == BTYPE) {
				printf("%c %d %d\n",DTYPE, drow, dcol);
				if (drow != 0 && dcol != 0)
					decodeBtoD(data, 0, 0, drow, dcol);
				else
					printf("\n");
				//printDataElements2(data, drow, dcol);
				printf("\n");
		} else if (type == DTYPE) {
				printf("%c %d %d\n",BTYPE, drow, dcol);
				decodeDtoB(0, data, 0, 0, drow, dcol);
				printDataElements2(pdata, drow, dcol);
				printf("\n");
		}

		scanf("\n%c", &type);
		//printf("%c\n", type);
	}
	return 0;
}
