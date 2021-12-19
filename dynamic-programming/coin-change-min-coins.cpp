#include <bits/stdc++.h> 
using namespace std; 
#define INF (int)1e9 
void initArray(int arr[], int length, int val) { 
	for (int i = 0; i < length; i++) 
		arr[i] = val; 
	return; 
} 
 
// calculate minimum number of coins to make change
int getMinNoCoins(int coins[], int noCoins, int amount) { 
	
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

	cout << getMinNoCoins(coins, n, amount) << endl;
	return 0; 
}
