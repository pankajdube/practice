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
	int *visited;
	int *indegree;
	int *outdegree;
	int **Adj;
};

struct Queue *CreateQueue()
{
	struct Queue *Q = NULL;
	Q = (struct Queue *) malloc(sizeof(struct Queue));
	if (!Q)
		return NULL;

	Q->front = Q->rear = NULL;
	return Q;
}

int IsEmptyQueue(struct Queue *Q)
{
	return (Q->front == NULL ? 1 : 0);
}

void EnQueue(struct Queue *Q, int data)
{
	struct ListNode *node = NULL;
	node = (struct ListNode *) malloc(sizeof(struct ListNode));
	if (!node) {
		printf("OOM Error\n");
		return;
	}
	node->data = data;
	node->next = NULL;
	if (Q->rear)
		Q->rear->next = node;
	Q->rear = node;
	
	if (Q->front == NULL)
		Q->front = Q->rear;
}

int DeQueue(struct Queue *Q)
{
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

	return data;
}

void DeleteQueue(struct Queue *Q)
{
	struct ListNode *temp;
	while (Q->front) {
		temp = Q->front;
		Q->front = temp->next;
		free(temp);
		temp = NULL;
	}
	free(Q);
}

void PrintGraph(struct Graph *G)
{
	int u, v;
	for (u = 0; u < G->nodes; u++) {
		for (v = 0; v < G->nodes; v++) {
			printf("%7d", G->Adj[u][v]);
		}
		printf("\n");
	}
}

void TopologicalSorting(struct Graph *G)
{
	struct Queue *Q = NULL;
	int counter;
	int connected_nodes = 0; 
	int u, v;
	int  *topologicalOrder = (int*) malloc(G->nodes * sizeof(int));
	if (!topologicalOrder) {
		printf("OOM Error\n");
		return;
	}

	Q = CreateQueue();
	if (!Q) {
		printf("OOM Error\n");
		return;
	}
	counter = 0;
	for (u = 0; u < G->nodes; u++) {
		if (G->outdegree[u] != 0 && G->indegree[u] == 0) {
			printf("Enqueue %d\n",u);
			EnQueue(Q, u);
		}
		if (G->outdegree[u] + G->indegree[u])
			connected_nodes++;
	}
	printf("%s: %d\n",__func__,__LINE__);
	while (!IsEmptyQueue(Q)) {
			printf("%s: %d\n",__func__,__LINE__);
			u = DeQueue(Q);
			printf("Dequeue: %d\n", u);
			topologicalOrder[u] = ++counter;
			for (v = 0; v < G->nodes; v++) {
					if (G->Adj[u][v]) {
							printf("Adj[%d][%d]: %d\n",u, v, G->Adj[u][v]);
							if (--G->indegree[v] == 0) {
									printf("Enqueue %d\n",v);
									EnQueue(Q, v);
							}
					}
			}
	}
	printf("%s: %d: counter: %d\n",__func__,__LINE__, counter);

	if (counter != connected_nodes)
		printf("Graph has a Cycle\n");
	else {
		printf("Node\t\tTopologicalOrder\n");
		for (u = 0; u < counter; u++) {
			printf("%d\t\t%d\n",u, topologicalOrder[u]);
		}
	}
	printf("%s: %d\n",__func__,__LINE__);
	free(topologicalOrder);
	topologicalOrder = NULL;
	printf("%s: %d\n",__func__,__LINE__);
	DeleteQueue(Q);
	printf("%s: %d\n",__func__,__LINE__);
	Q = NULL;
}

void PopulateIndegree(struct Graph *G)
{
	int u, v;
	for (u = 0; u < G->nodes; u++) {
		G->indegree[u] = 0;
		G->outdegree[u] = 0;
	}
	for (u = 0; u < G->nodes; u++) {
		for (v = 0; v < G->nodes; v++) {
			if (G->Adj[u][v]) {
				G->indegree[v] = G->indegree[v] + 1;
				G->outdegree[u] = G->indegree[u] + 1;
			}
		}
	}
	printf("\nnode\tindegree\n");
	for (u = 0; u < G->nodes; u++)
		printf("%d\t%d\n",u, G->indegree[u]);
}

int main()
{
	struct Graph *G;
	int u, v, test_id;
	scanf("%d", &test_id);
	do {
		/* Allocate Graph and initialize member */
		G = (struct Graph *) malloc(sizeof(struct Graph));
		scanf("%d",&G->nodes);
		G->visited = (int *) malloc(G->nodes * sizeof(int));
		G->indegree = (int *) malloc(G->nodes * sizeof(int));
		G->outdegree = (int *) malloc(G->nodes * sizeof(int));
		G->Adj = (int **) malloc(G->nodes * sizeof(int *));
		for (u = 0; u < G->nodes; u++) {
			G->Adj[u] = (int *) malloc(G->nodes * sizeof(int));
			G->visited[u] = 0;
		}
		/* Populate Adjcency Matrix for the graph */
		for (u = 0; u < G->nodes; u++) {
			for (v = 0; v < G->nodes; v++) {
				scanf("%d", &G->Adj[u][v]);
			}
		}
		PopulateIndegree(G);
		PrintGraph(G);
		printf("\n");
		TopologicalSorting(G);		
		/* Free Memory and Cleanup */
		free(G->visited);
		G->visited = NULL;
		free(G->indegree);
		G->indegree = NULL;
		free(G->outdegree);
		G->outdegree = NULL;
		for (u = 0; u < G->nodes; u++) {
			free(G->Adj[u]);
			G->Adj[u] = NULL;
		}
		free(G->Adj);
		G->Adj = NULL;
		free(G);
		G = NULL;
	} while (--test_id > 0);
	return 0;
}
