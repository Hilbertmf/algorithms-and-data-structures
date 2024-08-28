#include <bits/stdc++.h>
using namespace std;

void tarjanHelper(int cur, vector<vector<int>>& graph,
vector<int>& idx, vector<int>& low, int& counter,
vector<char>& vis, vector<char>& on_stack,
stack<int>& invariant, int& num_sccs,
vector<vector<int>>& sccs) {
    idx[cur] = low[cur] = counter++;
    on_stack[cur] = true;
    invariant.push(cur);
    vis[cur] = true;

    for(auto &adj : graph[cur]) {
        if (!vis[adj])
            tarjanHelper(adj, graph, idx, low, counter, vis,
                        on_stack, invariant, num_sccs, sccs);
        if (on_stack[adj])
            low[cur] = min(low[cur], low[adj]);
    }

    // we're at root of scc
    if (idx[cur] == low[cur]) {
        vector<int> scc;
        while (!invariant.empty()) {
            int v = invariant.top();
            invariant.pop();
            on_stack[v] = false;
            low[v] = cur;
            scc.push_back(v);
            if (v == cur) break;
        }
        sccs.push_back(scc);
        num_sccs++;
    }
}

vector<vector<int>> tarjan(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> sccs;
    vector<int> low(n, INT_MAX), idx(n);
    vector<char> vis(n, false), on_stack(n, false);
    stack<int> invariant;
    int counter = 0, num_sccs = 0;

    for(int i = 0; i < n; ++i) {
        if (!vis[i])
            tarjanHelper(i, graph, idx, low, counter, vis,
                         on_stack, invariant, num_sccs, sccs);
    }
    return sccs;
}