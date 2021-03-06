/**
 * Depth First Search: An implementation using Adjacency Matrix
 */

#include <stdio.h>
#include <time.h>

#define MAX_NODES 100
static int graph_matrix [MAX_NODES][MAX_NODES];
static int visited [MAX_NODES];
static int predecessor[MAX_NODES];

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

void print_predecessor(int node_index, int size)
{
	int i;
	printf("\n Predecessor: %d\n", node_index);
	for (i = 0; i < size; i++) {
		printf("%d ", predecessor[i]);
	}

	printf("\n");
}

int has_cycle(int node_index, int size)
{
	int i;
	visited[node_index] = 1;
	for (i = 0; i < size; i++) {
		if (graph_matrix[node_index][i]) {
			if (predecessor[i] != node_index && visited[i]) {
				predecessor[i] = node_index;
				print_predecessor(node_index, size);
				return 1; //Cycle Exist
			}
			else {
				predecessor[i] = node_index;
				return has_cycle(i, size);
			}
		}
	}
	return 0;
}

int detectcycle(int size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (!visited[i] && has_cycle(i, size))
			return 1;
	}

	return 0;
}

/*
 * main: Main entry point of program
 */
int main()
{
	int initial_node;
	int i, j, total_nodes, test_count = 0;
	int isCycle = 0;
	clock_t start;
	double duration;
	//scan total test cases
	scanf("%d", &test_count);
	while (test_count-- > 0) {
			isCycle = 0;
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
					predecessor[i] = -1;
			}

			print_adjacency_matrix(total_nodes);

			start = clock();
			//dfs_walk(initial_node, total_nodes);
			isCycle = detectcycle(total_nodes);
			duration = (double) ((clock() - start)/CLOCKS_PER_SEC);
			printf("\nOperation completed in %f sec.\n", duration);
			printf("\n Given Graph %s cycle\n", (isCycle ? "Has" : "Have no"));
	}
	return 0;
}
