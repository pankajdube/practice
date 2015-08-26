#include <stdio.h>
#include <malloc.h>

void print_input(char *str, int len)
{
	int i;
	printf("Given String is: ");

	for (i = 0; i < len; i++)
		printf("%c", *(str + i));

	printf("\n");
}

void swap(char *a, char *b)
{
	char temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

void print_permutations(char *str, int left, int right, int *counter)
{
	int i;
	if (left == right) {
		printf("%s\n", str);
		*counter = *counter + 1;
	}
	
	for (i = left; i < right; i++) {
		swap ((str + left), (str + i));
		print_permutations(str, left + 1, right, counter);
		swap ((str + left), (str + i));
	}

}

int main()
{
	int i, length, counter = 0;
	char *str;
	scanf("%d\n", &length);
	printf("Given string length: %d\n", length);
	
	str = (char *) malloc(length * sizeof(char));
	for (i = 0; i < length; i++) {
		scanf("%c", (str + i));
	}

	print_input(str, length);

	printf("All possible permutations of %s are: \n", str);
	print_permutations(str, 0, length, &counter);
	printf("\nTotal of %d permutations printed\n", counter);
	return 0;
}
