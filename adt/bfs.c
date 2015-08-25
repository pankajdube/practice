#include <stdio.h>
#include <malloc.h>

struct ListNode {
		int data;
		struct ListNode *next;
};

struct Queue {
	struct ListNode *front;
	struct ListNode *rear;
};

struct Graph {
	int nodes;
	int **adj;
};

struct Queue *CreateQueue() {
	struct Queue *Q;
	Q = (struct Queue *) malloc(sizeof(struct Queue));
	if (!Q)
		return NULL;
	Q->front = Q->rear = NULL;
	return Q;
}

int IsEmptyQueue(struct Queue *Q) {
	return (Q->front == NULL);
}

void EnQueue(struct Queue *Q, int data) {
	struct ListNode *node;
	node = (struct ListNode *) malloc(sizeof(struct ListNode));

	if (!node) {
		printf("EnQueue: Failed to crate new ListNode\n");
		return;
	}

	node->data = data;
	node->next = NULL;

	if (Q->rear)
		Q->rear->next = node;
	Q->rear = node;

	if (Q->front == NULL)
		Q->front = Q->rear;

	printf("Enqueue: Q->front: %p Q->rear: %p: \n", Q->front, Q->rear);
}

int DeQueue(struct Queue *Q) {
	int data = 0;
	struct ListNode *node;
	if (IsEmptyQueue(Q)) 
		return 0;
	else {
		node = Q->front;
		data = node->data;
		Q->front = node->next;
		free(node);
	}

	if (!Q->front)
		Q->rear = Q->front;

	printf("Dequeue: Q->front: %p Q->rear: %p: \n", Q->front, Q->rear);
	return data;
}

void DeleteQueue(struct Queue *Q) {
	struct ListNode *temp;
	while (Q->front) {
		temp = Q->front;
		Q->front = temp->next;
		free(temp);
	}
	free(Q);
}

void test_Queue()
{
	struct Queue *Q;
	int ans, data = 0;
	do {
		printf("Enter Operation: (1) Create; (2): Enqueue; (3): DeQueue; (4) DeleteQ; (0): Exit\n");
		scanf("%d", &ans);
		switch(ans) {
			case 1:
				Q = CreateQueue();
				break;
			case 2:
				printf("Enter Queue Element\n");
				scanf("%d", &data);
				if (!Q)
					Q = CreateQueue();
				EnQueue(Q, data);
				break;
			case 3:
				if (Q)
						data = DeQueue(Q);
				printf("Dequeued Element: %d\n", data);
				break;
			case 4:
				if (Q) {
					DeleteQueue(Q);
					Q = NULL;
				}
				break;
			case 0:
				if (Q) {
					DeleteQueue(Q);
					Q = NULL;
				}
				break;
			default:
				printf("Wrong Operation Selected\n");
		}
	} while (ans !=0);
}

void print_graph_adjacency_matrix(struct Graph *G)
{
	int i, j;
	for (i = 0; i < G->nodes; i++) {
			for (j = 0; j < G->nodes; j++) {
					printf("%d", G->adj[i][j]);
			}
			printf("\n");
	}
}

int main()
{
	struct Graph *G;
	int i, j, test_id, start_node;
	G = (struct Graph *) malloc(sizeof(struct Graph));
	scanf("%d", &test_id);
	do {
			printf("TEST_CASE: %d", test_id);
			scanf("%d", &G->nodes);
			scanf("%d", &start_node);
			G->adj = malloc(G->nodes * G->nodes);
			for (i = 0; i < G->nodes; i++)
					for (j = 0; j < G->nodes; j++)
							scanf("%d", &G->adj[i][j]);

			free(G->adj);
			G->adj = NULL;
			free(G);
			G = NULL;
	} while(--test_id > 0);

	return 0;
}
