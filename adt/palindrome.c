/*
 * This program helps in computing minimum cost to convert a
 * given string into palindrome
 * Author: Pankaj Dubey <pankaj.dubey@samsung.com>
 */

#include <stdio.h>
#include <time.h>

/* Disable the debugging prints by default */
#define DEBUG 0 
/* Macro for printing debug prints */
#define debug_print(...) \
            do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#define MAX_TEST 10
#define MAX_LENGTH 100005

static int test_count;
static int insert_cost;
static int delete_cost;
static int replace_cost;
char source_string[MAX_LENGTH];

inline int smallest(int x, int y, int z) {
		return 	((x < y) ? ((x < z) ? x : z) : ((z < y) ? z : y));
}

int editDistance2(char str1[], int size) {
		// cost matrix
		unsigned int cost[2][size];
		int i = 0,j;
		int min_cost = 0xFFFFF;
		int r = 0, pr;
		int x, y, z;

		for(j=0;j<size;j++) {
				// source string is NULL
				// so we need 'j' insert operations
				cost[r][j] = j*insert_cost;
		}
		
		//compute cost(i,j) and eventually return cost(m,n)
		for(i = 1; i < size; i++) {
				r = !r;
				pr = !r;
				cost[r][0] = i*delete_cost;
				for(j = i; j < size; j++) {
						x = cost[pr][j] + delete_cost;
						y = cost[r][j-1] + insert_cost;
						// if str1(i-1) != str1(size-j-1), add the replace cost
						if (str1[i-1] != str1[size-j-1])
								z = cost[pr][j-1] + replace_cost;
						else
								z = cost[pr][j-1];

						// find minimum cost
						cost[r][j] = smallest(x, y, z);
						if (((i + j) == size) || ((i+j) == size -1) || ((i+j) == size+1)) { 
								min_cost = min_cost < cost[r][j] ? min_cost : cost[r][j];
								//printf("%d\n", cost[r][j]);
						}
				}
		}
		//printf("\n");
		// return min_cost
		return min_cost; 
}

//main
int main() {
	int i, j, k;
	int min_cost, string_size;
	double duration;
	clock_t start;

	scanf("%d\n", &test_count);

	printf("=============================================================\n");	
	printf("Test_ID\t\tMIN_COST\tTime_Taken\n");	
	printf("=============================================================\n");	
	for (i = 1; i <= test_count; i++) {
			j = 0;
			string_size = 0;
			insert_cost = delete_cost = replace_cost = 0;
			scanf("%d %d %d\n", &insert_cost, &delete_cost, &replace_cost);
			do {
				scanf("%c", &source_string[j++]);
				string_size++;
			} while (source_string[j-1] != '\n');
		
			start = clock();
			int min_cost = editDistance2(source_string, string_size);
			duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
			printf("%4d\t\t%4d\t\t%f\n", i, min_cost, duration);
	}		
   return 0;
}
