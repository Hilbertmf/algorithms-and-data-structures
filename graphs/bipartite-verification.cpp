// time: O(V + E)
// space: O(V)

bool bfs(int node, vector<vector<int>>& graph, vector<int>& color) {
    queue<int> qu;
    qu.push(node);
    color[node] = 0;
    
    while(!qu.empty()) {
        int v = qu.front();
        qu.pop();

        for(auto &neighbor : graph[v]) {
            if(color[neighbor] == -1) {
                color[neighbor] = color[v] ^ 1;
                qu.push(neighbor);
            }
            else if(color[neighbor] == color[v])
                return false;
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    vector<int> color(graph.size(), -1);
    bool ans = true;

    for(int i = 0; i < graph.size() && ans; ++i) {
        if(color[i] == -1)
            ans &= bfs(i, graph, color);
    }

    return ans;
}
