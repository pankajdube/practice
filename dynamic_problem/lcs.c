#include <stdio.h>

int max(int a, int b)
{
	return a > b ? a : b;
}

int lcs(char* str1, char* str2, int len1, int len2)
{
	if (str1[len1] == str2[len2])
		return (1 + lcs(str1, str2, len1 -1, len2 -1));
	else
		return max(lcs(str1, str2, len1 -1, len2), lcs(str1, str2, len1, len2-1));
}

int main()
{
	int len1, len2, lcs_count;
	char str1[] = "AGGTAB";
	char str2[] = "GXTXAYB";
	len1 = sizeof(str1)/sizeof(char);
	len2 = sizeof(str2)/sizeof(char);
	lcs_count = lcs(str1, str2, len1, len2);
	printf("Lenght of longest common subsequence is: %d\n", lcs_count);
	return 0;

}
