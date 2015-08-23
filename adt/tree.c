/*
 * This program helps in computing minimum balane node and it's value in a tree.
 * Author: Pankaj Dubey <pankaj.dubey@samsung.com>
 */

#include <stdio.h>
#include <vector>
#include <time.h>

#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))
#define MAX_NODE 50000
#define INT_MIN 0
#define INT_MAX 0xFFFF

using namespace std;

struct node
{
	vector<int> value;
} nodes[MAX_NODE+5];

bool flag[MAX_NODE+5];

int total_nodes, minBal, minId;

void init_tree()
{
	int i;
	for (i = 1; i <= total_nodes; i++)
	{
		flag[i] = false;
		nodes[i].value.clear();
	}
}

int dfs_walk(int curNode)
{
	int curMax = INT_MIN, toId, total = 0, curNum;
	vector<int>::iterator iter = nodes[curNode].value.begin();
	
	for(; iter != nodes[curNode].value.end(); iter++)
	{
		toId = *iter;
		if (!flag[toId])
		{
			flag[toId] = true;
			curNum = dfs_walk(toId);
			curMax = max(curMax, curNum);
			total += curNum;
		}
	}

	total += 1;
	curMax = max(curMax, total_nodes - total);
	if (curMax < minBal)
	{
		minBal = curMax;
		minId = curNode;
	}

	return total;
}

int main()
{
	int i, caseN, from, to, testId;
	double duration;
    clock_t start;

	scanf("%d", &caseN);
	printf("=============================================================================\n");
    printf("Case No\t    Min_Balance\t Node_Value\tTime_Taken(sec)\n");
    printf("=============================================================================\n");

	for (testId = 1; testId <= caseN; testId++)
	{
		scanf("%d", &total_nodes);
		start = clock();
		init_tree();
		for (i = 1; i < total_nodes; i++)
		{
			scanf("%d%d", &from, &to);
			nodes[from].value.push_back(to);
			nodes[to].value.push_back(from);
		}
		minBal = INT_MAX;
		dfs_walk(1);
		duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
		printf("Case %d:\t\t%d\t  %d\t\t%f\n", testId, minBal, minId, duration);
	}

	return 0;
}
