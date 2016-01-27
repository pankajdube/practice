#include <cstdio>
#include <cstring>

using namespace std;

//#define LOCAL_DEBUG

#define MAX 256

int charVal[MAX];

int main()
{
	int k, testcases, val, lines;
	unsigned char ch;
	int cents_paid, cents, dollar;
	scanf("%d\n", &testcases);

	while (testcases--) {
		memset (charVal, 0, sizeof charVal);
		cents_paid = 0;
		scanf("%d\n", &k);
		for (int i = 0; i < k; i++) {
			scanf("%c %d\n", &ch, &val);
#ifdef LOCAL_DEBUG
			printf("%c %d\n", ch, ch);
#endif
			if (ch >= MAX) {
			//printf("%c's asscii value is greater than MAX\n", ch);
			//printf("%c-MAX = %d\n", ch, ch-MAX);
			charVal[ch-MAX] = val;
			}
			else
				charVal[ch] = val;
		}
		scanf("%d\n", &lines);
		while (lines--) {
			while(scanf("%c", &ch) && ch != '\n') {
				if (ch >= MAX)
					cents_paid += charVal[ch-MAX];
				else
					cents_paid += charVal[ch];
			}
		}
		/* Calculate total cost in $ and print it */
		dollar = cents_paid / 100;
		cents = cents_paid % 100;
		printf("%d.%02d$\n", dollar, cents);
	}
	return 0;
}
