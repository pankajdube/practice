#include <stdio.h>
#include <malloc.h>

#define INT_MAX 10000000

struct Graph {
	int nodes;
	int *visited;
	int **adj;
	int *key;
	int *parent;
};

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

int minKeyIndex(struct Graph *G)
{
	int i, min = INT_MAX; 
	int min_index;
	for (i = 0; i < G->nodes; i++) {
		if (!G->visited[i] && G->key[i] < min) {
			min = G->key[i];
			min_index = i;
		}
	}
	return min_index;
}

void printMST(struct Graph *G)
{
	int i;
	printf("Edge		Weight\n");
	for (i = 1; i < G->nodes; i++)
		printf("%d - %d 	%d\n", G->parent[i], i, G->adj[i][G->parent[i]]);	
}

void primsMST(struct Graph *G)
{
	int i, u;
	for(i = 0; i < G->nodes; i++) {
		u = minKeyIndex(G);
		G->visited[u] = 1;
		int v;
		for (v = 0; v < G->nodes; v++) {
			if(G->adj[u][v] && !G->visited[v] && G->adj[u][v] < G->key[v]) {
				G->parent[v] = u;
				G->key[v] = G->adj[u][v];
			}
		}
	}
}

int main()
{
	struct Graph *G;
	int i, j, test_id, start_node;
	scanf("%d", &test_id);
	do {
			G = (struct Graph *) malloc(sizeof(struct Graph));
			printf("TEST_CASE: %d\n", test_id);
			scanf("%d", &G->nodes);
			printf("G->nodes: %d\n", G->nodes);
			scanf("%d", &start_node);
			printf("start_node: %d\n", start_node);
			G->adj = malloc(sizeof(G->nodes * G->nodes * sizeof(int)));
			G->adj = (int **) malloc(G->nodes * sizeof(int *));
			for (i = 0; i < G->nodes; i++)
					G->adj[i] = (int *)malloc(G->nodes * sizeof(int));
			
			G->visited = malloc(sizeof(G->nodes * sizeof(int)));
			G->key = malloc(sizeof(G->nodes * sizeof(int)));
			G->parent = malloc(sizeof(G->nodes * sizeof(int)));

			for (i = 0; i < G->nodes; i++) {
					for (j = 0; j < G->nodes; j++) {
							scanf("%d", &G->adj[i][j]);
					}
					G->visited[i] = 0;
					G->key[i] = INT_MAX;
			}
			// Set initial condition
			G->key[0] = 0;
			G->parent[0] = -1;

			printf("Test: %d Adjacency Matrix is: \n", test_id);
			print_graph_adjacency_matrix(G);
			printf("\n Running Prims MST \n");
			//BFSTraversal(G, start_node);
			primsMST(G);
			printMST(G);
			
			for (i = 0; i < G->nodes; i++)
				free(G->adj[i]);

			free(G->adj);
			G->adj = NULL;
			free(G);
			G = NULL;
	} while(--test_id > 0);

	return 0;
}
