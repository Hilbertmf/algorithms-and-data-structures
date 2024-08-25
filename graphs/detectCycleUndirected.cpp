// time: O(V + E)
// space: O(V)
#include <bits/stdc++.h> 
using namespace std;

const int UNVISITED = 0;
const int VISITING = 1;
const int VISITED = 2;

vector<int> color;
vector<int> parent;
vector<vector<int>> graph;

vector<int> constructCycle(vector<int>& parent, int start, int end) {
    vector<int> cycle;
    cycle.push_back(end);
    while (start != end) {
        cycle.push_back(start);
        start = parent[start];
    }
    cycle.push_back(end);
    return cycle;
}

void dfsHelper(int node, int par, vector<int>& parent,
vector<int>& color, int& start, int& end) {
    
    color[node] = VISITING;
    for(int adj : graph[node]) {
        if (start != -1) return;
        if (color[adj] == VISITED || adj == par)
            continue;

        // cycle
        if (color[adj] == VISITING) {
            start = node;
            end = adj;
            return;
        }

        parent[adj] = node;
        dfsHelper(adj, node, parent, color, start, end);
    }
    color[node] = VISITED;
}

vector<int> getCycle() {
    int n = graph.size();
    color = vector<int>(n, UNVISITED);
    parent = vector<int>(n, -1);
    int start = -1, end = -1;

    for(int v = 0; v < n && start == -1; ++v) {
        if (color[v] == UNVISITED) {
            dfsHelper(v, -1, parent, color, start, end);
        }
    }

    vector<int> cycle;
    if(start != -1) {
        cycle = constructCycle(parent, start, end);
    }
    return cycle;
}

void readGraph(vector<vector<int>>& graph, int num_edges);
void printNodes(vector<int>& nodes);

int main() {

    int n, m;
    cin >> n >> m;
    graph = vector<vector<int>>(n);
    readGraph(graph, m);
    vector<int> cycle = getCycle();

    if(cycle.empty()) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << cycle.size() << "\n";
        printNodes(cycle);
    }

    return 0;
}

void readGraph(vector<vector<int>>& graph, int num_edges) {
    for(int i = 0; i < num_edges; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void printNodes(vector<int>& nodes) {
    for(int i = 0; i < nodes.size(); ++i) {
        if (i != 0) cout << " ";
        cout << nodes[i] + 1;
    }
    cout << "\n";
}
