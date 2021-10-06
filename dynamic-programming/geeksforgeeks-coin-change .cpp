// problem can be fount at: https://practice.geeksforgeeks.org/problems/coin-change2448/1#
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long int count(int coins[], int numCoins, int value) {

    // this problem is a classic problem called UNBOUNDED KNAPSACK
    long long dp[1010][1010];
    memset(dp, 0, sizeof(dp));

    for(int i = 0; i <= numCoins; i++) {
      for(int j = 0; j <= value; j++) {
        // base cases: if value is zero then 
        // there's one solution: {} empty
        if (j == 0)
          dp[i][j] = 1;
        // if theres no coins and value > 0: no solution
        else if(i == 0)
          dp[i][j] = 0;
        else if(coins[i-1] <= j) {
          // number of ways excluding ith coin + including ith coin
          dp[i][j] = (dp[i-1][j]) + (0 + dp[i][j - coins[i-1]]);
        }
        else {
          dp[i][j] = dp[i-1][j];
        }
      }
    }
    
    return dp[numCoins][value];
    }
};

int main() 
{ 
	int cases;
	cin >> cases;
	while (cases--)
	{
		int numCoins, value;
		cin >> value >> numCoins;
    
    int coins[numCoins];
    for (int i = 0; i < numCoins; i++)
      cin >> coins[i];

		Solution obj;
		cout << obj.count(coins, numCoins, value) << endl;
	}
 
	return 0; 
}