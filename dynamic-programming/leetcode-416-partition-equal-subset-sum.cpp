#include <iostream> 
#include <bits/stdc++.h>
 
using namespace std;
 
class Solution {
public:
    
// if the array can be partioned into two subsets such
// that the sum is equal, then:
// sum(arr) % 2 == 0
// and sum(set1) == sum(set2) == sum(arr)/2
  
// if array length = 1, then its false
//  
// we can model the problem as if its a knapsack with capacity = sum(set1)
// values[i] = weights[i] = arr[i]
// then we can try to fill the knapsack until totalSum / 2
// if dp[noItems][totalSum/2] == totalSum / 2 then return true
  
  
  int sum(vector<int>& nums) {
    int acc = 0;
    for(auto i = nums.begin(); i != nums.end(); i++)
      acc += *i;
    
    return acc;
  }
  
  bool canPartition(vector<int> &nums) {
    //TODO: Write - Your - Code
    int noItems = nums.size();
    int totSum = sum(nums);
    int dp[noItems+1][totSum+1];

    // edge cases
    if(totSum %2 != 0 || noItems < 2)
      return false;

    for(int i = 0; i <= noItems; i++) {
      for(int w = 0; w <= totSum/2; w++) {
        if(i == 0 || w == 0)
          dp[i][w] = 0;
        else if(w < nums[i-1])
          dp[i][w] = dp[i-1][w];
        else {
          int include = nums[i-1] + dp[i-1][w - nums[i-1]];
          int exclude = dp[i-1][w];
          dp[i][w] = max(include, exclude);
        }
      }
    }

    return dp[noItems][totSum/2] == totSum/2;
  }
};