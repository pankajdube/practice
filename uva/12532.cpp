#include <cstdio>
#include <vector>
using namespace std;

/*#define LOCAL_DEBUG*/
#define DATASIZE 100005
int data[DATASIZE];
vector<int> dataNeg;
vector<int> dataZero;

int lastbitOne(int n)
{
	return n & (-n);
}

int getSum(vector<int> &data, int index)
{
	int sum = 0;
	for (; index > 0; index -= lastbitOne(index))
		sum += data[index];

	return sum;
}

int query(vector<int> &data, int I, int V)
{
	return getSum(data, V) - (I == 1 ? 0 : getSum(data, I-1));
}

void updateData(vector<int> &data, int i, int val)
{
	for(; i < (int) data.size(); i += lastbitOne(i))
		data[i] += val;
}

int main()
{
	int i, Answer, N, K, I, V;
	char op;

	while (scanf("%d %d\n", &N, &K) != EOF) {
		dataNeg.assign(N+1, 0);
		dataZero.assign(N+1, 0);
		for (i = 1; i <= N; i++) {
			scanf("%d", &data[i]);
			if (data[i] < 0)
				updateData(dataNeg, i, 1);
			if (data[i] == 0)
				updateData(dataZero, i, 1);
		}
#ifdef LOCAL_DEBUG
		printf("%d %d\n", N, K);
		for (i = 1; i <= N; i++)
			printf("%d ", data[i]);
		printf("\n");
#endif
		for (i = 0; i < K; i++) {
			scanf("%c", &op);
			while (op != 'C' && op != 'P')
				scanf("%c", &op);
			scanf("%d %d\n", &I, &V);

			if (op == 'P') {
				if (query(dataZero, I, V))
					printf("0");
				else if (query(dataNeg, I, V) % 2 == 0)
					printf("+");
				else
					printf("-");
			} else if (op == 'C') {
				if (data[I] >= 0 && V < 0)
					updateData(dataNeg, I, 1);
				else if (data[I] < 0 && V >=0)
					updateData(dataNeg, I, 1);
				if (data[I] != 0 && V == 0)
					updateData(dataZero, I, 1);
				else if (data[I] == 0 && V != 0)
					updateData(dataZero, I, -1);

				data[I] = V;
			}
#ifdef LOCAL_DEBUG
			printf("%c %d %d\n", op, I, V);
#endif
		}
		printf("\n");
	}

	return 0;
}

