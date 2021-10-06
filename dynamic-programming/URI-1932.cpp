#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// naive solution with dynamic programming: gets TLE

int main() {
	// your code goes here
	int num_days, tax;
	cin >>  num_days >> tax;
	// profit is our tabulation array to store best profits
	int profit[200010] = {0}, prices[200010];
	
	for(int i=0; i<num_days; i++)
	{
		cin >> prices[i];
	}
	
	profit[0] = 0;
	for(int i=1;i < num_days; i++)
	{
		profit[i] = profit[i-1];
		for(int j=0; j < i; j++)
		{
			// optimize sales
			// profit[j] stands for accumulated max profit till index j
			profit[i] = max(profit[i], profit[j] + (prices[i] - (prices[j]+tax)) );
		}
	}
	printf("%d\n", profit[num_days-1]);
	return 0;
}