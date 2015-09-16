#include <stdio.h>

#define SIZE 500
#define INF SIZE*SIZE
#define MAX(u, v) ((u > v) ? u : v)
/* dist[i][j] : distance between two nodes i and j
 * or 0 if there is no direct connection
 */
int dist[SIZE][SIZE];
/* length[i]: length of shortest path between source and node i */
int length[SIZE];
/* source node index */
int source;
/* destination node index */
int destination;
/* total nodes */
int nodes;
/* total edges */
int edges;

void print_data()
{
	int i, j;
	printf("%d %d\n", source, destination);
	printf("%d\n", edges);
	for (i = 0 ; i <= nodes; ++i) {
		for (j = 0; j <= nodes; ++j) {
			if (dist[i][j] != 0)
					printf("%d %d %d\n", i, j, dist[i][j]);
		}
	}
}

void print_shortest_path(int *predecessor, int dest)
{
	if (predecessor[dest] != -1)
		print_shortest_path(predecessor, predecessor[dest]);
	printf("-> %d ", dest);
}

void dijkstra()
{
	int i, k, min_node;
	int visited[SIZE];
	int predecessor[SIZE];
	/* initialize visited, predecessor, and length from source */
	for (i = 1; i <= nodes; ++i) {
		visited[i] = 0;
		predecessor[i] = -1;
		length[i] = INF;
	}
	/* mark length of source from source as zero */
	length[source] = 0;
	for (i = 1; i <= nodes; ++i) {
		min_node = -1;
		for (k = 1; k <= nodes; ++k) {
				if (!visited[k] && (min_node == -1 || length[k] < length[min_node]))
						min_node = k;
		}

		visited[min_node] = 1; 
		for (k = 1; k <= nodes; ++k) {
			if (dist[min_node][k] && (length[min_node] + dist[min_node][k] < length[k])) {
					length[k] = length[min_node] + dist[min_node][k];
					predecessor[k] = min_node;
			}
		}
		if (min_node == destination)
			break;		
	}
	printf("Shortest path between source: %d and Destination: %d is: %d\n", \
					source, destination, length[destination]);
	printf("Shortest Path is: ");
	print_shortest_path(predecessor, destination);
}

int main()
{
	int i, j, k, d;
	nodes = -1;
	/* scan source node and destination node index */
	scanf("%d %d\n", &source, &destination);
	/* scan total edges */
	scanf("%d\n", &edges);
	/* scan distance between edges i and j */
	for (k = 0; k < edges; k++) {
		scanf("%d %d %d\n", &i, &j, &d);
		dist[i][j] = d;
		nodes = MAX(i, MAX(j, nodes));	
	}
	print_data();
	dijkstra();
	return 0;
}
