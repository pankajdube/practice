#include <stdio.h>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int lcs(char* str1, char* str2, int len1, int len2)
{
		if (len1 == 0 || len2 == 0)
				return 0;
		if (str1[len1-1] == str2[len2-1]) 
				return (1 + lcs(str1, str2, len1 -1, len2 -1));
		else
				return max(lcs(str1, str2, len1, len2-1), lcs(str1, str2, len1-1, len2));
}

void print_longest_common_subsequence(int lcs_count, int** l, char* str1, char *str2, int len1, int len2);

int dynamic_lcs(char* str1, char* str2, int len1, int len2)
{
	printf("\n");
	//printf("len1: %d len2: %d", len1, len2);
	int l[len1+1][len2+1];
	int d[len1+1][len2+1];
	int max_len_lcs = len1 > len2 ? len1 : len2;
	int lcs_idx[max_len_lcs];
	int i, j, k=0;
	for (i = 0; i <=len1; i++, k++) {
		lcs_idx[k] = -1;
		for (j = 0; j <= len2; j++) {
			if (i == 0 || j == 0)
				l[i][j] = 0;
			else {
					if (str1[i-1] == str2[j-1]) {
							l[i][j] = 1 + l[i-1][j-1];
							d[i][j] = 0; //LeftTop Move
					} else if (l[i][j-1] >= l[i-1][j]) {
							l[i][j] = l[i][j-1];
							d[i][j] = -1; //Left Move
					} else {
							l[i][j] = l[i-1][j];
							d[i][j] = 1;//top Move
					}
			}
		}
	}

	i = len1;
	j = len2;
	k = l[len1][len2];
	while (i >= 0 && j >= 0) {
		if (d[i][j] == 0) {
			lcs_idx[k--] = i;
			i--;
			j--;
		} else if (d[i][j] == -1)
			j--;
		else if (d[i][j] == 1)
			i--;
	}
	printf("\n");
	printf("Longest Common Subsequence is: \n");
	for (k=0;k < l[len1][len2]; k++)
		printf("%c", str1[lcs_idx[k]]);
	printf("\n");
	return l[len1][len2];
}

void print_longest_common_subsequence(int lcs_count, int** l, char* str1, char *str2, int len1, int len2)
{
	int i = len1;
	int j = len2;
	while (i > 1 && j > 1) {
		if (l[i][j] == l[i-1][j-1]) {
			i = i -1;
			j = j -1;
		}
		else if (l[i][j] == l[i-1][j])
			i = i -1;
		else if (l[i][j] == l[i][j-1])
			j = j -1;
	
		if (str1[i-1] == str2[j-1])
			printf("%c", str1[i-1]);
	}
}

#define MAX_LEN 100

int main()
{
	int test_count;
	int i, len1, len2, lcs_count, max_str_len;
	char str1[MAX_LEN];
	char str2[MAX_LEN];
	char ch;
	scanf("%d\n", &test_count);
	for (i = 1; i <= test_count; i++) {
			len1 = len2 = 0;
			do {
					scanf("%c", &str1[len1]);
					len1++;
			} while (str1[len1-1] != '\n');

			do {
					scanf("%c", &str2[len2]);
					len2++;
			} while (str2[len2-1] != '\n');
			//lcs_count = lcs(str1, str2, len1 -1 , len2 -1);
			//printf("%d# Length of longest common subsequence is: %d\n", i, lcs_count);
			lcs_count = dynamic_lcs(str1, str2, len1 -1 , len2 -1);
			printf("%d# Length of Dynamic longest common subsequence is: %d\n", i, lcs_count);
	}
	printf("\n");
	return 0;

}
