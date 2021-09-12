#include <iostream> 
#include <bits/stdc++.h>
 
using namespace std;
 
int climbStairs(int n)
{
	int dp[10010] = {0};
	dp[0] = 1;
	dp[1] = 1;
	for(int i=2;i <= n; i++)
			dp[i] = dp[i-1] + dp[i-2];
	return dp[n];
}

// generalization if the person can climb up to k stairs for a given value k
int main() 
{ 
	int num_steps, jump_size;
	while(scanf("%d %d", &num_steps, &jump_size) && num_steps != 0)
	{
		int dp[num_steps+10] = {0};
		
		// base cases
		dp[0] = 1;
		dp[1] = 1;
		// populating dp array iteratively
		for(int i=jump_size; i<= num_steps; i++)
		{
			for(int j=1;j <= jump_size && j <= i; j++)
			// dp[n] = dp[n-1] + dp[n-2] + ... + dp[n-k] 
			// for k = maximum jump size possible
				dp[i] += dp[i-j];
		}
		// time complexity: O(n*k)
		// space complexity: O(n)
		printf("%d\n",dp[num_steps]);
 
	return 0; 
}
