#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>

using namespace std;
#define MAXN 10001
#define MAXC 1000000000
#define LOCAL_DEBUG 1
#define dprintf(fmt, ...) \
	do { if (LOCAL_DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while(0)

struct Graph
{
	int V;
	int E;
	int P;
};

struct Graph G;
/* convention followed for pair in this program, first = destination, and second = cost */
typedef pair <int, int> ii;
typedef vector <ii> vi;
/* AdjList: stores directed graph's edges and associated weight */
vector<vi> AdjList;
/* RadjList: stores directed reverse graph's edges and associated weight */
vector<vi> RadjList;
/* dist1: keeps minimum distance from souce i */
int dist1[MAXN];
int dist2[MAXN];
/* ans: */
int ans;

int dijkstra(int s, int t)
{
	priority_queue < ii, vi, greater <ii> > pq;
	/* Mark distance of source as Zero */
	dist1[s] = 0;
	/* Push source and its cost as first element into priority queue */
	pq.push(ii(s, 0));
	/* process pq untill it is empty */
	while (!pq.empty()) {
		/* popout topmost element from priority queue */
		ii u = pq.top();
		pq.pop();
		/* if cost in dist table matches with cost of element */
		if (dist1[u.first] == u.second) {
			vector<pair <int, int> >::iterator pi;
			/* for each neighbour of u.first check if there is shortest path available */
			for (pi = AdjList[u.first].begin(); pi != AdjList[u.first].end(); pi++) {
				if (dist1[pi->first] > dist1[u.first] + pi->second) {
					dist1[pi->first] = dist1[u.first] + pi->second;
					pq.push(ii(pi->first, dist1[pi->first]));
				}	
			}
			
		}	
	}
	/* return shorted distance of destination from source */
	return dist1[t];
}

void dijkstra2(int s, int t)
{
	priority_queue < ii, vi, greater <ii> > pq;
	/* As we are finding shorted path in reverse graph
	 * mark distance of destination as Zero 
	 */
	dist2[t] = 0;
	/* Push destination and its cost as first element into priority queue */
	pq.push(ii(t, 0));
	/* process pq untill it is empty */
	while (!pq.empty()) {
		/* popout topmost element from priority queue */
		ii u = pq.top();
		pq.pop();
		/* if cost in dist table matches with cost of element */
		if (dist2[u.first] == u.second) {
			vector<pair <int, int> >::iterator pi;
			/* for each neighbour of u.first check if there is shortest path available */
			for (pi = RadjList[u.first].begin(); pi != RadjList[u.first].end(); pi++) {
				if (dist2[pi->first] > dist2[u.first] + pi->second) {
					dist2[pi->first] = dist2[u.first] + pi->second;
					pq.push(ii(pi->first, dist2[pi->first]));
				}	
			}
			
		}	
	}
}

void init()
{
	ans = 0;
	AdjList.clear();
	RadjList.clear();
	memset(dist1, MAXC, sizeof dist1);
	memset(dist2, MAXC, sizeof dist2);
	AdjList.resize(G.E);
	RadjList.resize(G.E);
}

int main()
{
	int T, s, t;
	int i, u, v, c;
	/* scan the number of test cases */
	scanf("%d", &T);
	while (T--) {
		dprintf("Test Case ###### ##### %d\n",T);
		/* scan the number of vertices, edges, source, destination and max cost allowed */
		scanf("%d %d %d %d %d", &G.V, &G.E, &s, &t, &G.P);
		/* reset global data */
		init();
		/* scan each edge of weighted graph and its cost */
		for (i = 0; i < G.E; i++) {
			scanf("%d %d %d", &u, &v, &c);
			AdjList[u].push_back(ii(v,c));
			RadjList[v].push_back(ii(u, c));
			//dprintf("%s, u:%d: v:%d c:%d\n",__func__,u, v, c);
		}
		/* Compute the shorted distance of distance from source */
		ans = dijkstra(s, t);
		dprintf("ans: %d, G.P: %d\n", ans, G.P);
		if (ans <= G.P) {
			ans = 0;
			/* run diskstra on reverse graph and compute minimum cost from t to s */
			dijkstra2(s, t);
			for (i = 1; i <= G.V; i++) {
				vector<pair <int, int> >::iterator pi;
				for (pi = AdjList[i].begin(); pi != AdjList[i].end(); pi++) {
					if (dist1[i] + pi->second + dist2[pi->first] <= G.P) {
						ans = max (ans, pi->second);
					}
				}
			}
	
			printf("%d\n", ans);
		} else	
			printf("-1\n");
	};
	return 0;
}
