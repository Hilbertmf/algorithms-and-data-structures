#include <bits/stdc++.h>
using namespace std;

int solve(int numPipes, int maxSize, int pipeLengths[], int pipeValues[], int dp[1010][2010]) {
	if(numPipes == 0 || maxSize == 0) {
		return 0;
	}
	else if(dp[numPipes][maxSize] != 0) {
		return dp[numPipes][maxSize];
	}
	if(pipeLengths[numPipes-1] <= maxSize) {
		return dp[numPipes][maxSize] = max(
                          pipeValues[numPipes-1] + solve(numPipes, maxSize - pipeLengths[numPipes-1], pipeLengths, pipeValues,dp),
                          solve(numPipes-1, maxSize, pipeLengths, pipeValues, dp)
                          );
	}
	else {
		return solve(numPipes - 1, maxSize, pipeLengths, pipeValues, dp);
	}
}
int main(){
	int dp[1010][2010];
  memset(dp, 0, sizeof(dp));
  
  int numPipes, maxSize;
  scanf("%d %d", &numPipes, &maxSize);
	int pipeLengths[numPipes+10], pipeValues[numPipes+10];
	
	for(int i = 0; i < numPipes;i++) 
		scanf("%d %d",&pipeLengths[i], &pipeValues[i]);

	for(int i = 0;i <= numPipes;++i) {
		for(int j = 0;j <= maxSize;++j) {
			if(i == 0 || j == 0){
			  dp[i][j] = 0;
			}
			else if(pipeLengths[i-1] <= j) {
				dp[i][j] = max(pipeValues[i-1] + dp[i][j - pipeLengths[i-1]], dp[i-1][j]);
			}
			else {
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	printf("%d\n", dp[numPipes][maxSize]);
	// printf("%d\n", solve(numPipes, maxSize, pipeLengths, pipeValues, dp));
	return 0;
}