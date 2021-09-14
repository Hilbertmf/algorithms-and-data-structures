#include <iostream> 
#include <bits/stdc++.h>
#define INFINITE 0x3f3f3f3f

using namespace std;
void fillUglyNumsArray(int n, unsigned long long *ugly_nums) {
	int power_2 = 1, power_3 = 1, power_5 = 1;
	unsigned long long next_mul_2, next_mul_3, next_mul_5;
	
	for(int i=2;i <= n;i++)
		ugly_nums[i] = INFINITE;
	ugly_nums[1] = 1;
	
	for(int i=2;i<=n;i++)
	{
		next_mul_2 = ugly_nums[power_2]*2;
		next_mul_3 = ugly_nums[power_3]*3;
		next_mul_5 = ugly_nums[power_5]*5;
		
		ugly_nums[i] = min({next_mul_2, next_mul_3, next_mul_5});
		
		// increment the power of chosen prime
		if(ugly_nums[i] == next_mul_2)
				power_2++;
		if(ugly_nums[i] == next_mul_3)
				power_3++;
		if(ugly_nums[i] == next_mul_5)
				power_5++;
	}
}
 
int main() 
{ 
	int num;
	scanf("%d", &num);
	unsigned long long ugly_nums[num+10];

	fillUglyNumsArray(num, ugly_nums);
	
	unsigned long long result = ugly_nums[num];
	printf("Ugly number(%d) = %llu\n", num, result);
 
	return 0; 
}
