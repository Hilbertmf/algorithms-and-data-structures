#include <bits/stdc++.h>
using namespace std;

class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        int totalCost = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> visited(V);
        pq.push({0, 0});

        while (!pq.empty()) {
            int node = pq.top().second;
            int cost = pq.top().first;
            pq.pop();

            if(visited[node]) continue;
            visited[node] = true;

            totalCost += cost;
            for(auto &vec : adj[node]) {
                int neighbor = vec[0];
                int weight = vec[1];
                if(visited[neighbor]) continue;
                pq.push({weight, neighbor});
            }
        }

        return totalCost;
    }
};

int main() { return 0;}