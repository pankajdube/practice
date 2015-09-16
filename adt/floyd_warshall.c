#include <stdio.h>

#define SIZE 500
#define INF SIZE
#define MAX(u, v) ((u > v) ? u : v)
/* dist[i][j] : distance between two nodes i and j
 * or 0 if there is no direct connection
 */
int dist[SIZE][SIZE];
/* length[i]: length of shortest path between source and node i */
int length[SIZE];
/* total nodes */
int nodes;
/* total edges */
int edges;

void print_data(int data[][SIZE])
{
	int i, j;
	printf("%d\n", edges);
	for (i = 1 ; i <= nodes; ++i) {
		for (j = 1; j <= nodes; ++j) {
			if (data[i][j] != INF)
					printf("%7d", data[i][j]);
			else
					printf("%7s", "INF");
		}
		printf("\n");
	}
}

int ComputeGraphCenter(int data[][SIZE])
{
	int i, j, center;
	/* minDist[i]: length of shortest path from i to its farthest vertex */
	int minDist[SIZE];

	for (i = 1; i <= nodes; i++) {
		minDist[i] = 0;
		for (i = 1; i <= nodes; i++) {
			if (i != j && minDist[i] < data[i][j])
				minDist[i] = data[i][j];
		}
	}
	center = 1;
	for (i = 1; i <= nodes; i++) {
		if (minDist[i] < minDist[center])
			center = i;
	}

	return center;
}

int ComputeGraphMedian(int data[][SIZE])
{
	int i, j, median;
	/*minPathSum[i]: Sum of shortest paths from node i */
	int minPathSum[SIZE];

	for (i = 1; i <= nodes; i++) {
			minPathSum[i] = 0;
			for (j = 1; j <= nodes; j++) {
				if (i != j)
					minPathSum[i] = minPathSum[i] + data[i][j];
			}
	}
	median = 1;
	for (i = 1; i <= nodes; i++) {
			if (minPathSum[i] < minPathSum[median])
					median = i;
	}

	return median;	
}

void FloydWarshall()
{
	int i, j, k;
	int shortest_path[SIZE][SIZE];

	for (i = 1; i <= nodes; ++i) {
			for (j = 1; j <= nodes; ++j) {
					shortest_path[i][j] = dist[i][j];	
			}
	}
	
	for (k = 1; k <= nodes; ++k) {
			for (i = 1; i <= nodes; ++i) {
					for (j = 1; j <= nodes; ++j) {
							if (shortest_path[i][k] + shortest_path[k][j] < shortest_path[i][j])
									shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j];
					}	
			}	
	}
	
	printf("Shortest Path between each pair of vertices are:\n");
	print_data(shortest_path);
	printf("Median Node of this graph is: %d\n", ComputeGraphMedian(shortest_path));	
	printf("Center Node of this graph is: %d\n", ComputeGraphCenter(shortest_path));	
}

int main()
{
	int i, j, k, d, test_count, test_id;
	nodes = -1;
	test_id = 1;
	/* scan test_id */
	scanf("%d\n", &test_count);
	while (test_id <= test_count) {
			nodes = 0;
			edges = 0;
			/* scan total edges */
			scanf("%d\n", &edges);
			/* scan distance between edges i and j */
			for (k = 0; k < edges; k++) {
					scanf("%d %d %d\n", &i, &j, &d);
					dist[i][j] = d;
					nodes = MAX(i, MAX(j, nodes));	
			}
			for (i = 0 ; i <= nodes; ++i) {
					for (j = 0; j <= nodes; ++j) {
							if (dist[i][j] == 0 && (i != j))
									dist[i][j] = INF;
					}
			}

			printf("#%d\n", test_id);
			printf("Given Distance Matrix\n");
			print_data(dist);
			FloydWarshall();
			test_id++;
			for (i = 0 ; i <= nodes; ++i) {
					for (j = 0; j <= nodes; ++j) {
						dist[i][j] = 0;
					}
			}
	}	
	return 0;
}
