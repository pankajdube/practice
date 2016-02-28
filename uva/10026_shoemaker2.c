#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Task
{
    int time;
    int fine;
    int id;
};

void printdata(vector<Task> &T)
{
    int i;
    printf("%d", T[0].id);
    for (i = 1; i < T.size(); i++) {
            printf(" %d", T[i].id);
    }
    printf("\n");
}

bool comp(const Task &j1, const Task&j2)
{
    return j1.time * j2.fine < j2.time * j1.fine;
}

int main()
{  
    int cases;
	scanf("%d\n", &cases);
    while ( cases-- )
    {
        int nooftasks;
		scanf("%d\n", &nooftasks);

        vector<Task> task(nooftasks);
        for (int i = 0; i < nooftasks; ++i)
        {
			scanf("%d %d\n", &task[i].time, &task[i].fine);
            task[i].id = i + 1;
        }
        
        // Greedily pick a next task imposing the minimum fine.
        // Keep lexicographical order for equivalent tasks.
        stable_sort(task.begin(), task.end(), comp);
#if 0
		printf("%d", task[0].id);
        for (int i = 1; i < nooftasks; ++i)
				printf(" %d", task[i].id);
        printf("\n");
#endif
		printdata(task);
   
        if (cases)
				printf("\n");
    }
    return 0;
}
