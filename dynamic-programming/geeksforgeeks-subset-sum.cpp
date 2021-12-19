// https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1/
#include <iostream> 
#include <bits/stdc++.h>
 
using namespace std;

class Solution{   
public:
    bool isSubsetSum(int length, int arr[], int sum){
        // code here
        int dp[length+1][sum+1];
        
        for(int i = 0; i <= length; i++) {
            for(int s = 0; s <= sum; s++) {
                // base cases
								if (i == 0 || s == 0)
                    dp[i][s] = 0;
                else if(s < arr[i-1])
                    dp[i][s] = dp[i-1][s];
                else {
                    int include = arr[i-1] + dp[i-1][s - arr[i-1]];
                    int exclude = dp[i-1][s];
                    dp[i][s] = max(include, exclude);
                }
            }
        }
        
        return dp[length][sum] == sum;
    }
};

int main() 
{ 
	int cases;
	cin >> cases;
	while (cases--)
	{
		int length, sum;
		cin >> length;
    
		int arr[length];
    for (int i = 0; i < length; i++)
      cin >> arr[i];

		cin >> sum;

		Solution obj;
		cout << obj.isSubsetSum(length, arr, sum) << endl;
	}
 
	return 0; 
}
