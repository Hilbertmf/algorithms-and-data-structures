#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> prefix(n, vector<int>(n));

// time: O((r*c))
// space: O((r*c))
void populatePrefix2D(vector<vector<int>>& grid, vector<vector<int>>& prefix) {

    int rows = grid.size();
    int cols = grid[0].size();
    for(int i = 0; i < rows; ++i) {
        long long sum = 0;
        for(int j = 0; j < cols; ++j) {

            prefix[i][j] = grid[i][j];
            if(i > 0)
                prefix[i][j] += prefix[i - 1][j];
            if(j > 0)
                prefix[i][j] += sum;

            sum += grid[i][j];
        }
    }

}

// get every submatrix from 0,0 to i,j:
// time: O((r*c)²)
for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
        for(int r = 0; r <= i; ++r) {
            for(int c = 0; c <= j; ++c) {

                int submatrix_sum = prefix[i][j];
                int removals = 0;
                if(r > 0) {
                    submatrix_sum -= prefix[r - 1][j];
                    removals++;
                }
                if(c > 0) {
                    submatrix_sum -= prefix[i][c - 1];
                    removals++;
                }
                if(removals == 2 && r > 0 && c > 0)
                    submatrix_sum += prefix[r - 1][c - 1];

                if(submatrix_sum == target)
                    // Do something
            }
        }
    }
}