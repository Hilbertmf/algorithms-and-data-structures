#include <iostream> 
#include <bits/stdc++.h>
 
using namespace std;
 
int calcMid(int left, int right) {
	return left + (right - left)/2;
}

bool condition(int n) {
	// some code to test if problem condition is satisfied
	return isBadVersion(n) && !isBadVersion(n-1);
}

int binarySearch(int arr[], int n) {
	int left = 0;
	int right = n-1;

	// edge cases
	if(condition(left))
		return left;
	if(condition(right))
		return right;

	int i = calcMid(left, right);
	while(!condition(i)) {
		if(arr[i+1] > arr[i])
			left = i;
		else
			right = i;
			
		i = calcMid(left, right);
	}

	return i;
}

int main() 
{ 
	int aux;
 
	scanf("%d", &aux);
 
	printf("%d", aux);
 
	return 0; 
}
