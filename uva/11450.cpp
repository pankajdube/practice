#include <cstdio>
#include <vector>

using namespace std;
//#define LOCAL_DEBUG
#define MAX_M 201
#define MAX_C 21
#define MAX_K 21
/* max amount available for spending */
int amount;
/* number of garments to be baught */
int garments;
/* memo[i][j]: stores if using i garment an amount of j can be spent */
int memo[MAX_C][MAX_M];
/* models[i][j]: gives price of jth model of i' th class garment*/
vector <int> models[MAX_K];
/* stores max_spending possible for each case */
int max_spending;

#ifdef LOCAL_DEBUG
void print_data()
{
	int i, j;
	printf("%d %d\n", amount, garments);
	for (i = 0; i < garments; i++) {
		for (j = 0; j < models[i].size(); j++) {
			printf("%d ", models[i][j]);
		}
		printf("\n");
	}
}

#endif
void reset()
{
#ifdef LOCAL_DEBUG
	printf("<<<< %s: %d\n",__func__,__LINE__);
#endif
	int i, j;
	max_spending = -1;	
	for (i = 0; i < MAX_C; i++) {
		for (j = 0; j < MAX_M; j++) {
			memo[i][j] = false;
		}
		models[i].clear();
	}
#ifdef LOCAL_DEBUG
	printf("%s: %d >>>>\n",__func__,__LINE__);
#endif
}

void compute_max_spending(int g, int sum)
{
#ifdef LOCAL_DEBUG1
	printf("%s(%d, %d)\n",__func__, g, sum);
#endif
	int i;
	/* if g is reached max garments to be purchased then check for spending */
	if (g == garments) {
		/* if current spending (sum) is less than required (amount) and
		 * sum is greater than max_spending then update max and return
		 */
		if (sum <= amount && sum > max_spending)
			max_spending = sum;
		return;
	}
	/* if current spending crossed max amount then return */
	if (sum > amount)
		return;
	/* if memo[g][sum] is already computed then return */
	if (memo[g][sum])
		return;
	/* mark memo[g][sum] as computed */
	memo[g][sum] = true;
	/* iterate over all classes of garments */
	for (i = 0; i < models[i].size(); i++) {
		compute_max_spending(g + 1, sum + models[g][i]); 
	}
}

int main()
{
	int T, i, j, K, p;
	/* scan total number of test cases */
	scanf("%d", &T);
	/* process each test case data */
	while (T--) {
		/* reset global data */
		reset();
		/* scan input data */
		scanf("%d %d", &amount, &garments);
		for (i = 0; i < garments; i++) {
			scanf("%d", &K);
			while (K--) {
				scanf("%d", &p);
				models[i].push_back(p);
			}
		}
#ifdef LOCAL_DEBUG
		print_data();
#endif
		/* compute max_spending possible */
		compute_max_spending(0, 0);
		/* print the result */
		if (max_spending == -1)
			printf("no solution\n");
		else
			printf("%d\n", max_spending);
	}

	return 0;
}

