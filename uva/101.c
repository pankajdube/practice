#include <stdio.h>
#include <malloc.h>

#define LOCAL_DEBUG

struct stack
{
	int data[25];
	int top;
};

void do_move_onto(struct stack *blocks, int a, int b)
{
	int c;
	/* move any blocks stacked if any on top of block a to their initial position */
	while (blocks[a].top) {
		c = blocks[a].data[blocks[a].top--];
		blocks[c].data[0] = c;
		blocks[c].top = 0;
	}
	/* move any blocks stacked if any on top of block b to their initial position */
	while (blocks[b].top) {
		c = blocks[b].data[blocks[b].top--];
		blocks[c].data[0] = c;
		blocks[c].top = 0;
	}
	/*finally move block a onto b */
	blocks[b].top++;
	blocks[b].data[blocks[b].top] = a;
	blocks[a].top--;
}

void do_move_over(struct stack *blocks, int a, int b)
{
	int c;
	/* move any blocks stacked if any on top of block a to their initial position */
	while (blocks[a].top) {
		c = blocks[a].data[blocks[a].top--];
		blocks[c].data[0] = c;
		blocks[c].top = 0;
	}
	/*finally move block a onto stack containing block b */
	blocks[b].top++;
	blocks[b].data[blocks[b].top] = a;
	blocks[a].top--;
}

void do_pile_onto(struct stack *blocks, int a, int b)
{
	int c, i;
	/* move any blocks stacked if any on top of block b to their initial position */
	while (blocks[b].top) {
		c = blocks[b].data[blocks[b].top--];
		blocks[c].data[0] = c;
		blocks[c].top = 0;
	}
	/*finally move all blocks stacked over a onto b */
	for (i = 0; i <= blocks[a].top; i++) {
		blocks[b].data[++blocks[b].top] = blocks[a].data[i];
	}
	blocks[a].top = -1;
}

void do_pile_over(struct stack *blocks, int a, int b)
{
	int i;
	/*move all blocks stacked over a onto b */
	for (i = 0; i <= blocks[a].top; i++) {
		blocks[b].data[++blocks[b].top] = blocks[a].data[i];
	}
	blocks[a].top = -1;
}

void print_blocks(struct stack *blocks, int n)
{
	int i, top, j;
	for (i = 0; i < n; i++) {
		top = blocks[i].top;
		if (top == -1)
			printf("%d:\n", i);
		else {
			printf("%d: ", i);
			for (j = 0; j < top; j++) {
				printf("%d ", blocks[i].data[j]);
			}
			printf("%d\n", blocks[i].data[j]);
		}
	}
}
 
int main()
{
	int i, n, a, b;
	char op1[5], op2[5];
	struct stack* blocks;
	scanf("%d\n", &n);
	blocks = malloc(n * sizeof(struct stack));
	for (i = 0; i < n; i++) {
		blocks[i].data[0] = i;
		blocks[i].top = 0;
	}
#ifdef LOCAL_DEBUG
	printf("%d\n", n);
#endif
	
	while (scanf("%s", op1) && strcmp(op1, "quit")) {
		scanf("%d %s %d\n", &a, op2, &b);
		if (!strcmp(op1, "move") && !strcmp(op2, "onto")) {
			do_move_onto(blocks, a, b);
#ifdef LOCAL_DEBUG
			printf("%s %d %s %d\n", op1, a, op2, b);
			print_blocks(blocks, n);
#endif
			
		} else if (!strcmp(op1, "move") && !strcmp(op2, "over")) {
			do_move_over(blocks, a, b);
#ifdef LOCAL_DEBUG
			printf("%s %d %s %d\n", op1, a, op2, b);
			print_blocks(blocks, n);
#endif
		} else if (!strcmp(op1, "pile") && !strcmp(op2, "onto")) {
			do_pile_onto(blocks, a, b);
#ifdef LOCAL_DEBUG
			printf("%s %d %s %d\n", op1, a, op2, b);
			print_blocks(blocks, n);
#endif
		} else if (!strcmp(op1, "pile") && !strcmp(op2, "over")) {
			do_pile_over(blocks, a, b);
#ifdef LOCAL_DEBUG
			printf("%s %d %s %d\n", op1, a, op2, b);
			print_blocks(blocks, n);
#endif
		}
	}

	return 0;
}
