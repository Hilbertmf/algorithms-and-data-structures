// https://practice.geeksforgeeks.org/problems/minimum-sum-partition3317/1#
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{

  public:
	// we want to maximize subset sum but without going beyond 
	// half of total sum of our list to minimize the subset sum
	// difference
	int calcSum(int arr[], int length) {
	    int sum = 0;
	    for(int i=0; i<length; i++)
	        sum += arr[i];
	   return sum;
	}
	int minDifference(int arr[], int length)  {
	    int sum = calcSum(arr, length);
	    int wantedSubsetSum = sum % 2 == 0 ? sum/2 : (sum/2)+1;
	    int dp[length+1][sum+1];
	    
	    for(int i=0; i <= length; i++) {
	        for(int s = 0; s <= wantedSubsetSum; s++) {
	            int include, exclude;
	            if(i == 0 || s == 0)
	                dp[i][s] = 0;
	            else if(s < arr[i-1])
	                dp[i][s] = dp[i-1][s];
	            else {
	                include = arr[i-1] + dp[i-1][s - arr[i-1]];
	                exclude = dp[i-1][s];
	                dp[i][s] = max(include, exclude);
	            }
	        }
	    }
	    
	    int subsetSum1 = dp[length][wantedSubsetSum];
	    int subsetSum2 = abs(dp[length][wantedSubsetSum] - sum);
	    int diff = abs(subsetSum1 - subsetSum2);
	    return diff;
	} 
};


// { Driver Code Starts.
int main() 
{
   
   
   	int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        int a[n];
        for(int i = 0; i < n; i++)
        	cin >> a[i];

       

	    Solution ob;
	    cout << ob.minDifference(a, n) << "\n";
	     
    }
    return 0;
}  // } Driver Code Ends