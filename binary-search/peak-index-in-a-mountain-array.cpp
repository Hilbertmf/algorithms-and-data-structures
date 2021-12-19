#include <iostream> 
#include <bits/stdc++.h>
 
using namespace std;
 
class Solution {
public:
  bool isPeak(vector<int>& arr, int pos) {
    if (arr[pos] > arr[pos-1] && arr[pos] > arr[pos+1])
      return true;
    return false;
  }
  
  int calcMid(int left, int right) {
    return (left + (right - left)/2);
  }
  
  int peakIndexInMountainArray(vector<int>& arr) {
    
    int left = 0;
    int right = arr.size() - 1;
    int currPos = calcMid(left, right);
    
    while(!isPeak(arr, currPos)) {
      if (arr[currPos+1] > arr[currPos])
        left = currPos;
      else
        right = currPos;
      currPos = calcMid(left, right);
    }

    return currPos;
  }
};
