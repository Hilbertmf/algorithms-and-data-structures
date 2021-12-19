#include <bits/stdc++.h> 
using namespace std; 
#define MEM(arr, val) memset(arr, (val), sizeof(arr))

// calculate minimum number of ways to make change
int getMinNoWays(int coins[], int noCoins, int amount) { 
	int dp[amount+1];
	MEM(dp, 0);
	
	dp[0] = 1;
	
	for (int coin = 0; coin < noCoins; coin++) {
		for (int i = 1; i <= amount; i++) {
			if (i >= coin)
				dp[i] += dp[i - coin];
		}
	}
	
	return dp[amount];
}
 
int main() {

	int n, amount; 
	cout << "enter number of coins" << endl;
	cin >> n;
	int coins[n+1];
	cout << "enter coins" << endl;
	for (int i = 0; i < n; i++) 
		cin >> coins[i];
	
	cout << "enter wanted amount" << endl;
	cin >> amount;

	cout << getMinNoWays(coins, n, amount) << endl;
	return 0; 
}
