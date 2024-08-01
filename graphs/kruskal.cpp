// topic: Minimum Spanning Tree (kruskal)
// time: O(ElogE + E*α)
// space: O(V + E)
#include <bits/stdc++.h>
using namespace std;

class UnionFind;

long long kruskal(int n, vector<vector<int>>& edges) {
    
    UnionFind dsu(n);
    sort(edges.begin(), edges.end(),
    [&](vector<int>& v1, vector<int>& v2){
        return v1[0] < v2[0];
    });

    long long cost = 0;

    for(auto &edge : edges) {
        int u = edge[1], v = edge[2];
        
        // ignore edges that form cycles
        if (dsu.isConnected(u, v)) continue;

        // this edge is added to the tree
        cost += edge[0];
        dsu.join(u, v);
    }

    // check if graph is connected
    int node = edges[0][1];
    for(int i = 0; i < n; ++i) {
        if (!dsu.isConnected(i, node))
            return -1;
    }

    return cost;
}

void readEdges(vector<vector<int>>& edges, int num_edges);

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges;
    readEdges(edges, m);
    long long mst = kruskal(n, edges);
    if(mst == -1) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << mst << "\n";
    }
    
    return 0;
}

void readEdges(vector<vector<int>>& edges, int num_edges) {
    for(int i = 0; i < num_edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        edges.push_back({w, u, v});
        edges.push_back({w, v, u});
    }
}