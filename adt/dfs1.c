/**
 * Depth First Search: An implementation using Adjacency Matrix
 */

#include <stdio.h>
#include <time.h>

#define MAX_NODES 100
static int graph_matrix [MAX_NODES][MAX_NODES];
static int visited [MAX_NODES];

/*
 * dfs_walk: implementation of dfs algorithm
 * @current_node: node at which current dfs will run
 */
void dfs_walk(int current_node, int size)
{
	int j;
	printf("%d ", current_node);
	visited[current_node] = 1;
	for (j = 0; j < size; j++) {
		if (!visited[j] && graph_matrix[current_node][j] == 1)
			dfs_walk(j, size);
	}
}

/*
 * print_adjacency_matrix: debug function to verify that program has read
 * input properly.
 * @size: total_nodes in the graph
 */
void print_adjacency_matrix(int size)
{
	int i, j;
	printf("Given graph has %d nodes and adjacency matrix is:\n", size);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%d ", graph_matrix[i][j]);
		}
		printf("\n");
	}
}

/*
 * main: Main entry point of program
 */
int main()
{
	int initial_node;
	int i, j, total_nodes;
	clock_t start;
	double duration;

	//scan total nodes in the graph
	scanf("%d", &total_nodes);
	//initial node to start with
	scanf("%d", &initial_node);
	//scan the adjacency matrix of the graph
	for (i = 0; i < total_nodes; i++) {
		for (j = 0; j < total_nodes; j++) {
			scanf("%d", &graph_matrix[i][j]);
		}
		// Mark visited of each node as zero
		visited[i] = 0;
	}

	print_adjacency_matrix(total_nodes);

	start = clock();
	dfs_walk(initial_node, total_nodes);
	duration = (double) ((clock() - start)/CLOCKS_PER_SEC);
	printf("\ndfs_walk completed in %f sec.\n", duration);
	return 0;
}
