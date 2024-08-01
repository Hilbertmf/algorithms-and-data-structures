// topic: Topological sorting
// time: O(V + E)
// space: O(V)
#include <bits/stdc++.h>
using namespace std;

vector<int> topSort(vector<int>& in_degree,
vector<vector<int>>& graph) {
    vector<int> top_sort;
    queue<int> qu;
    for(int i = 0; i < in_degree.size(); ++i) {
        // has no parent
        if (in_degree[i] == 0)
            qu.push(i);
    }

    while (!qu.empty()) {
        int node = qu.front();
        qu.pop();

        top_sort.push_back(node);
        for(auto &adj : graph[node]) {
            in_degree[adj]--;
            if (in_degree[adj] == 0)
                qu.push(adj);
        }
    }
    
    return top_sort;
}

void printNodes(vector<int>& nodes);
void readGraph(vector<int>& in_degree, vector<vector<int>>& graph, int num_edges);

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    vector<int> in_degree(n);
    readGraph(in_degree, graph, m);
    vector<int> top_sort = topSort(in_degree, graph);

    // check valid
    if(top_sort.size() == n) {
        printNodes(top_sort);
    }
    else {
       cout << "IMPOSSIBLE\n"; 
    }
    
    return 0;
}

void readGraph(vector<int>& in_degree,
vector<vector<int>>& graph, int num_edges) {
    for(int i = 0; i < num_edges; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        in_degree[v]++;
    }
}

void printNodes(vector<int>& nodes) {
    for(int i = 0; i < nodes.size(); ++i) {
        if (i != 0) cout << " ";
        cout << nodes[i];
    }
    cout << "\n";
}