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

int dynamic_lcs(char* str1, char* str2, int len1, int len2)
{
	int l[len1+1][len2+1];
	int i, j;
	for (i = 0; i <=len1; i++) {
		for (j = 0; j <= len2; j++) {
			if (i == 0 || j == 0)
				l[i][j] = 0;
			else if (str1[i-1] == str2[j-1])
				l[i][j] = 1 + l[i-1][j-1];
			else
				l[i][j] = max(l[i][j-1], l[i-1][j]);
		}
	}

	return l[len1][len2];
}

int main()
{
	int i, len1, len2, lcs_count, max_str_len;
	char str1[] = "AGGTAB";
	char str2[] = "GXTXAYB";
	len1 = sizeof(str1)/sizeof(char);
	len2 = sizeof(str2)/sizeof(char);

	lcs_count = lcs(str1, str2, len1 -1 , len2 -1);
	printf("Lenght of longest common subsequence is: %d\n", lcs_count);
	lcs_count = dynamic_lcs(str1, str2, len1 -1 , len2 -1);
	printf("Lenght of Dynamic longest common subsequence is: %d\n", lcs_count);
	printf("\n");
	return 0;

}
