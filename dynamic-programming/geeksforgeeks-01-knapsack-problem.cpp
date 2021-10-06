// problem can be fount at: https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1#
#include <bits/stdc++.h>
using namespace std;

class Solution
{
  public:
  //Function to return max value that can be put in knapsack of capacity W.
  int knapSack(int capacity, int wt[], int val[], int numItems)
  {
    int cache[numItems+1][capacity+1];
    int includeIth, excludeIth;

    for(int i=0; i <= numItems; i++) {
      for(int w=0; w <= capacity; w++) {
        if (i == 0|| w == 0)
          cache[i][w] = 0;
        else if (wt[i-1] > w)
          cache[i][w] = cache[i-1][w];
        else {
          includeIth = val[i-1] + cache[i-1][w - wt[i-1]] ;
          excludeIth = cache[i-1][w];
          cache[i][w] = max(includeIth, excludeIth);
        }
      }
    }
    
    return cache[numItems][capacity];
  }
};

int main() 
{ 
	int cases;
	cin >> cases;
	while (cases--)
	{
    int numItems, capacity;
    cin >> numItems >> capacity;

    int val[numItems];
    int wt[numItems];
    
    for (int i = 0; i < numItems; i++)
      cin >> val[i];

    for (int i = 0; i < numItems; i++)
      cin >> wt[i];

		Solution obj;
		cout << obj.knapSack(capacity, wt, val, numItems) << endl;
	}
 
	return 0; 
}