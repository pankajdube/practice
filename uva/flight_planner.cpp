#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

#define MAXNODES 2501

struct Edge
{
	int u, v;
	bool deleted;
};

struct Tree
{
	int diameter;
	int root;
};

int nodes;
vector <Edge> edges;
vector<int> g[MAXNODES];
int dist[MAXNODES];
int from[MAXNODES];

void bfs(int start)
{
	int i;
	queue<int> Q;

	for (i = 0; i < nodes; i++) {
		dist[i] = -1;
		from[i] = -1;
	}
		
	dist[start] = 0;
	Q.push(start);
	
	while (Q.size() > 0) {
		int u = Q.front();
		Q.pop();
		for (int j = 0; j < g[u].size(); j++) {
			Edge out = edges[g[u][j]];
			if (out.deleted)
				continue;
			int v = out.u == u ? out.v : out.u;
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				from[v] = u;
				Q.push(v);
			}
		}
	}
}

struct Tree get_subtree(int u)
{
	int i, max_dist = -1;
	int end_node = -1;
	Tree subtree;
	vector<int> path;
	
	bfs(u);
	for (i = 0; i < nodes; i++) {
		if (dist[i] > max_dist) {
			max_dist = dist[i];
			end_node = i;
		}
	}
	bfs(end_node);
	end_node = -1;
	max_dist = -1;
	for (i = 0; i < nodes; i++) {
		if (dist[i] > max_dist) {
			max_dist = dist[i];
			end_node = i;
		}
	}
	
	for (int j = end_node; j != -1; j = from[j])
		path.push_back(j);
	
	subtree.diameter = path.size() - 1;
	subtree.root = path[path.size() / 2];
	return subtree;
}

int main()
{
	int testcases, i;
	int min_dia;
	/* scan the number of test cases */
	scanf("%d\n", &testcases);
		
	while (testcases--) {
		scanf("%d\n", &nodes);
		min_dia = nodes;

		/* clear global variables */
		edges.clear();
		for (i = 0; i < nodes; i++)
			g[i].clear();

		/* scan input and intialize global variables */
		for (i = 0; i < (nodes - 1); i++) {
			Edge e;
			e.deleted = false;
			scanf("%d %d\n", &e.u, &e.v);
			e.u--;
			e.v--;
			edges.push_back(e);
			g[e.u].push_back(edges.size()-1);
			g[e.v].push_back(edges.size()-1);
		}

		Edge deleted, added;
		for (i = 0; i < edges.size(); i++) {
			edges[i].deleted = true;
			Tree left = get_subtree(edges[i].u);
			Tree right = get_subtree(edges[i].v);
			int a = left.diameter / 2;
			int b = (left.diameter + 1) / 2;
			int c = right.diameter / 2;
			int d = (right.diameter + 1) / 2;
			int new_dia = max(max(a+b, c+d), b+d+1);
			if (new_dia < min_dia) {
				min_dia = new_dia;
				deleted.u = edges[i].u;
				deleted.v = edges[i].v;
				added.u = left.root;
				added.v = right.root;
			}
			edges[i].deleted = false;
		}
		
		/* print the output */ 
		printf("%d\n", min_dia);
		printf("%d %d\n", deleted.u+1, deleted.v+1);
		printf("%d %d\n", added.u+1, added.v+1);
	}
	return 0;
}
