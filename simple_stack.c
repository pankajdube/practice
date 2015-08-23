#include <stdio.h>

#define STACK_SIZE 100

static int stack[STACK_SIZE];

static int stack_top = -1;

void push(int element)
{
	if (stack_top == STACK_SIZE-1) {
		printf("!!! Stack is FULL!!!\n");
		return;
	}
	stack[++stack_top] = element;
}

int is_stack_empty()
{
	return stack_top == -1 ? 1 : 0;
}

int pop()
{
	if (is_stack_empty()) {
		printf("!!! Stack is empty\n");
		return -1;
	}

	return stack[stack_top--];
}

int main()
{
	int select, element;
	printf("Select Stack Operations: (1) Push; (2): Pop; (0): Exit\n");
	scanf("%d", &select);

	do {
			switch (select) {
					case 1:
							printf("Enter element to be pushed into stack: ");
							scanf("%d", &element);
							push(element);
							printf("\n");
							break;
					case 2:
							element = pop();
							printf("Element %d is popped up\n", element);
							break;

					case 3: 
							printf("Existing !!!\n");
							return 0;
			}
			printf("Select Stack Operations: (1) Push; (2): Pop; (0): Exit\n");
			scanf("%d", &select);
	} while (select);
	return 0;
}
