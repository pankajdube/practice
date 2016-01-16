#include <stdio.h>

#define MAX_TEST 100
#define MAX_LEN	400

char expr[MAX_LEN];
char stack_buffer[MAX_LEN];
char operators[5] = {'+','-','*','/','^'};
int stack_pointer;

enum type {
OPERAND = 0,
LEFTPAREN = 1,
RIGHTPAREN = 2,
OPERATOR = 3,
};

void printbuffer(int len)
{
	int i;
	printf("%d\n", len);
	for (i = 0; i < len; i++)
		printf("%c", expr[i]);

	printf("\n");
}

int is_token(char ch)
{
	int token;
	int i;
	for (i = 0; i < 5; i++) {
			if (ch == operators[i])
				return OPERATOR;
	}
	
	if (ch == '(')
		return LEFTPAREN;
	else if (ch == ')')
		return RIGHTPAREN;
	else
		return OPERAND;
}

int is_low_priority(char s, char d)
{
	int s_idx, d_idx;
	int i;
	for (i = 0; i < 5; i++) {
		if (s == operators[i])
			s_idx = i;
		if (d == operators[i])
			d_idx = i;
	}

	return s_idx < d_idx ? 1 : 0;
}

void infix_to_postfix(int len)
{
	int i;
	char ch;

	for (i = 0; i < len; i++) {
		if (is_token(expr[i]) == OPERAND)
			printf("%c", expr[i]);
		else if (is_token(expr[i]) == RIGHTPAREN) {
			while (stack_pointer >= 0 && stack_buffer[stack_pointer] != '(')
				printf("%c", stack_buffer[stack_pointer--]);
		} else if ((is_token(expr[i]) == OPERATOR) || (is_token(expr[i]) == LEFTPAREN)) {
				while (stack_pointer >= 0 &&
					(is_token(stack_buffer[stack_pointer]) == OPERATOR || is_token(stack_buffer[stack_pointer]) == LEFTPAREN)*/) {
					if (is_token(stack_buffer[stack_pointer]) == LEFTPAREN) {
						stack_pointer--; 
						break;
					}
					if (is_low_priority(stack_buffer[stack_pointer], expr[i])) {
						printf("%c", stack_buffer[stack_pointer--]);
					} else
						break;
				}
				stack_buffer[++stack_pointer] = expr[i];
		}
	}

	while (stack_pointer >= 0)
		printf("%c", stack_buffer[stack_pointer--]);

	printf("\n");
}

int main()
{
	int testnos, len;
	char ch;

	scanf("%d\n", &testnos);
	
	while (testnos--) {
			stack_pointer = -1;
			len = 0;
			ch = '\n';
			while(scanf("%c", &ch) > 0 && ch != '\n') {
				expr[len++] = ch;
			}
			infix_to_postfix(len);
			//printbuffer(len);
	}

	return 0;
}

