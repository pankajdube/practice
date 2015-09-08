#include <stdio.h>
#include <malloc.h>

unsigned int *table = NULL;

unsigned int min(unsigned int a, unsigned int b)
{
	return a <= b ? a : b;
}

int MakeChange(int *denomination, int amount, int num_denominations)
{
	int i, j;
	unsigned int coins = 0;
	table[0] = 0;
	
	for (i = 1; i <= amount; i++) {
		coins = -1;
		for (j = 0; j < num_denominations; j++) {
			if (denomination[j] <= i) {
					coins = min(coins, table[i-denomination[j]]);
			}
		}
		if (coins < -1)
			table[i] = coins + 1;
		else
			table[i] = -1;
	}

	coins = table[amount];

	return coins;
}

int main()
{
	int i, min_change;
	int amount;
	int num_denominations;
	int *denominations = NULL;

	scanf("%d %d\n", &amount, &num_denominations);
	table = (int *) malloc(sizeof(int) * (amount+1));
	denominations = (int *) malloc(sizeof(int) * num_denominations);

	if (denominations == NULL || table == NULL) {
		printf("Failed to allocate Memory\n");
		return -1;
	}

	for (i = 0; i < amount+1; i++)
		table[i] = -1;

	for (i = 0; i < num_denominations; i++)
		scanf("%d", &denominations[i]);

	min_change = MakeChange(denominations, amount, num_denominations);
	printf("For amount: %d minimum %d coins required\n", amount, min_change);

	return 0;
}
