#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

/**
 *  dp[i][j][k] = Watts consumed when the bulbs from (i..j) exclusive have been switched off,
 *		  where the current position of the robot is pos[k].
 */

int main()
{
	int T, S, N;
	cin >> T;
	while ( T-- )
	{
		cin >> N >> S;
		int pos[N+1];

		pos[0] = 0;
		for(int i=1; i<=N; i++)
		   cin >> pos[i];

		int dp[N+2][N+2][N+2];
		memset(dp, 0, sizeof(dp));

		for(int i=N; i>=0; i--)
		   for(int j=i-1; j>=0; j--)
			dp[0][i][j] = (N-i+1)*(pos[i] - pos[j]) + dp[0][i+1][i];

		for(int i=1; i<=N; i++)
		   for(int j=i+1; j<=N; j++)
			dp[i][N+1][j] = i*(pos[j] - pos[i]) + dp[i-1][N+1][i];

		for(int i=1; i<=N; i++)
		{
		   for(int j=N; j>i; j--)
		   {
		      for(int k=i+1; k<j; k++)
		      {
			   int left  = (N-j+i+1)*(pos[k] - pos[i]) + dp[i-1][j][i];
			   int right = (N-j+i+1)*(pos[j] - pos[k]) + dp[i][j+1][j];
			   dp[i][j][k] = min(left, right);
		      }
		   }
		}

		int curr = 0;
		while ( pos[curr] < S )
		   ++curr;

		if ( S < pos[1] )		cout << dp[0][2][1] + N*(pos[1] - S) << endl;
		else if ( S > pos[N] )		cout << dp[N-1][N+1][N] + N*(S - pos[N]) << endl;
		else if ( S == pos[curr] )	cout << dp[curr-1][curr+1][curr] << endl;
		else
		{
			cout << min( N*(pos[curr] - S  ) + dp[curr-1][curr+1][curr],
				     N*(S - pos[curr-1]) + dp[curr-2][curr][curr-1] )
			     << endl;
		}
	}
	return 0;
}
