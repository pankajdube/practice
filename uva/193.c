#include <cstdio>
#include <cstring>

using namespace std;

#define MAXNODE 101
#define WHITE 0
#define BLACK 1

int graph[MAXNODE][MAXNODE];
int colored[MAXNODE];
int blacknodes[MAXNODE];
int max_black_count;
int nodes;


int check_adjacent_color(int current)
{
	for (int i = 1; i <= nodes; i++) {
		if (graph[i][current] && colored[i])
			return 0;
	}
	return 1;
}

void dfs(int current)
{
	if (current > nodes) {
		int count = 0;
		for (int i = 1; i <= nodes; i++) {
			if (colored[i])
				count++;
		}
		if (count > max_black_count) {
			max_black_count = count;
			for (int i = 1, j = 0; i <=nodes; i++) {
				if (colored[i])
					blacknodes[j++] = i;
			}
		}
		return;
	} else {
		colored[current] = WHITE;
		dfs(current + 1);
		colored[current] = BLACK;
		if (check_adjacent_color(current))
			dfs(current+1);
		colored[current] = WHITE;
	}
}

int main()
{
	int testcases;
	int edges;
	/* scan test case numbers */
	scanf("%d\n", &testcases);

	while (testcases--) {
		memset(graph, 0, sizeof graph);
		memset(colored, 0, sizeof colored);
		memset(blacknodes, 0, sizeof blacknodes);
		/* scan number of nodes and edges */
		scanf("%d %d\n", &nodes, &edges);
		/* scan each edge and create adjacency matrix of graph */
		for (int i = 0; i < edges; i++) {
			int u, v;
			scanf("%d %d\n", &u, &v);
			graph[u][v] = graph[v][u] = 1;
		}
		/* init max_black_count to be zero */
		max_black_count = 0;

		/* call DFS on graph */
		dfs(1);

		/* print solution of graph coloring */
		printf("%d\n", max_black_count);
		for (int i = 0; i < max_black_count; i++) {
			if (i != max_black_count - 1)
				printf("%d ", blacknodes[i]);
			else
				printf("%d", blacknodes[i]);
		}
		printf("\n");
	}
		

	return 0;
}
