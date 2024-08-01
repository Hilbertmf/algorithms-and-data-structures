// topic: Shortest Paths: all shortest paths for all (i, j)
// time: O(V³)
// space: O(V² + E)
#include <bits/stdc++.h> 
using namespace std;
const int INF = 1e9;

vector<vector<int>> dist;

void floydWarshall(int n, vector<vector<pair<int, int>>>& graph) {
    dist = vector<vector<int>> (n, vector<int>(n, INF));
    for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i == j) dist[i][j] = 0;
			else {
				for(auto &edge : graph[i]) {
					if (edge.first == j)
						dist[i][j] = min(dist[i][j], edge.second);
				}
			}
		}
    }   

    for(int mid = 0; mid < n; ++mid) {
        for(int from = 0; from < n; ++from) {
            for(int to = 0; to < n; ++to) {
                if (dist[from][mid] != INF && dist[mid][to] != INF)
                    dist[from][to] = min(dist[from][to],
                                         dist[from][mid] + dist[mid][to]);
            }
        }
    }
}