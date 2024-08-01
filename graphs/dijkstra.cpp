// time: O(E*logE)
// space: O(V + E)
#include <bits/stdc++.h> 
using namespace std; 
#define INF (long long)1e9

vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
	int n = graph.size();
	vector<int> dists(n, INF);
	dists[start] = 0;
	// max heap by default, so negate the dists
	priority_queue<pair<int, int>> heap;
	heap.push({0, start}); // dist, vertex
	vector<char> vis(n);

	while(!heap.empty()) {
		int dist = -heap.top().first;
		int v = heap.top().second;
		heap.pop();

		if (vis[v]) continue;
		vis[v] = true;

		for(auto &[adj, w] : graph[v]) {
			if(dists[adj] > dists[v] + w) {
				dists[adj] = dists[v] + w;
				heap.push({-dists[adj], adj});
			}
		}
	}
	return dists;
}
