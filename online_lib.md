# Algorithms and Data Structures for Competitive Programming

- **[Data Structures](#data-structures)**
  - **[Segment Tree](#segment-tree)**
  - **[Union Find](#union-find)**
- **[Graphs](#graphs)**
  - **[Topological Sorting](#topological-sorting)**
  - **[Minimum Spanning Tree](#minimum-spanning-tree)**
  - **[Dijkstra](#dijkstra)**
  - **[Bellman-Ford](#bellman-ford)**
  - **[Floyd-Warshall](#floyd-warshall)**
  - **[Bipartite Verification](#bipartite-verification)**
  - **[LCA via Binary Lifting](#lca-via-binary-lifting)**
  - **[Tarjan - Strong Connected Components (SCCs)](#tarjan---strong-connected-components-sccs)**
- **[Math](#math)**
  - **[Number Theory](#number-theory)**
    - **[Binary Exponentiation](#binary-exponentiation)**
    - **[Sieve of Eratosthenes](#sieve-of-eratosthenes)**
    - **[Segmented Sieve](#segmented-sieve)**
    - **[Binomial Coefficient](#binomial-coefficient)**
- **[Strings](#strings)**
  - **[Z Function](#z-function)**

## Data Structures

### Segment Tree

```cpp
bool leaf(int from, int to) {
    return from == to;
}
bool allIn(int from, int to, int l, int r) {
    return l <= from && to <= r;
}
bool allOut(int from, int to, int l, int r) {
    return to < l || r < from;
}

class Segtree {
public:
    void init(int n) {
        size = n;
        nodes.resize(n * 4, 0);
        lazy.resize(n * 4, 0);
    }
    
    void build(vector<int>& vals) {
        build(vals, 0, 0, size - 1);
    }
    
    int query(int left, int right) {
        return query(left, right, 0, 0, size - 1);
    }
    
    void updateRange(int left, int right, int val) {
        updateRange(left, right, val, 0, 0, size - 1);
    }
    
    void update(int pos, int val) {
        update(pos, val, 0, 0, size - 1);
    }
private:
    int size;
    vector<int> nodes;
    vector<int> lazy;
    
    void build(vector<int>& vals, int node, int from, int to) {
        if (leaf(from, to)) {
            nodes[node] = vals[from];
        } else {
            int mid = MID(from, to);
            build(vals, 2 * node + 1, from, mid);
            build(vals, 2 * node + 2, mid + 1, to);
            nodes[node] = nodes[2 * node + 1] + nodes[2 * node + 2];
        }
    }
    
    void propagate(int node, int from, int to) {
        if (lazy[node] != 0) {
            nodes[node] += lazy[node] * (to - from + 1);
            if (!leaf(from, to)) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0; 
        }
    }
    
    int query(int l, int r, int node, int from, int to) {
        propagate(node, from, to);
        if (allIn(from, to, l, r)) {
            return nodes[node];
        }
        if (allOut(from, to, l, r)) {
            return 0;
        }
        int mid = MID(from, to);
        return query(l, r, 2 * node + 1, from, mid) +
               query(l, r, 2 * node + 2, mid + 1, to);
    }
    
    void updateRange(int l, int r, int val, int node, int from, int to) {
        propagate(node, from, to);
        if (allIn(from, to, l, r)) {
            lazy[node] += val;
            propagate(node, from, to);
        } else if (!allOut(from, to, l, r)) {
            int mid = MID(from, to);
            updateRange(l, r, val, 2 * node + 1, from, mid);
            updateRange(l, r, val, 2 * node + 2, mid + 1, to);
            nodes[node] = nodes[2 * node + 1] + nodes[2 * node + 2];
        }
    }
    
    void update(int pos, int val, int node, int from, int to) {
        propagate(node, from, to);
        if (leaf(from, to)) {
            nodes[node] = val;
        } else {
            int mid = MID(from, to);
            if (pos <= mid) {
                update(pos, val, 2 * node + 1, from, mid);
            } else {
                update(pos, val, 2 * node + 2, mid + 1, to);
            }
            nodes[node] = nodes[2 * node + 1] + nodes[2 * node + 2];
        }
    }
};

```

### Union Find

```cpp
class UnionFind {
public:

    vector<int> parents;
    vector<int> group_sizes;
    int num_elems;
    int num_groups;

    UnionFind(int size) {
        if (size <= 0) return;

        num_elems = size;
        num_groups = size;
        parents.resize(size);
        group_sizes.resize(size);

        for(int i = 0; i < size; ++i) {
            parents[i] = i;
            group_sizes[i] = 1;
        }
    }

    int find(int node) {

        int root = node;
        while (root != parents[root]) {
            root = parents[root];
        }

        // path compression
        while (node != parents[node]) {
            int next = parents[node];
            parents[node] = root;
            node = next;
        }

        return root;
    }

    bool isConnected(int node1, int node2) {
        return find(node1) == find(node2);
    }

    int groupSize(int node) {
        return group_sizes[find(node)];
    }

    int size() {
        return num_elems;
    }

    int numComponents() {
        return num_groups;
    }

    void join(int node1, int node2) {

        int root1 = find(node1);
        int root2 = find(node2);
        
        if (root1 == root2)
            return;

        if (group_sizes[root1] > group_sizes[root2]) {
            group_sizes[root1] += group_sizes[root2];
            parents[root2] = root1;
        }
        else {
            group_sizes[root2] += group_sizes[root1];
            parents[root1] = root2;
        }

        num_groups--;
    }
};
```

## Graphs

### Topological Sorting

```cpp
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
```

### Minimum Spanning Tree

```cpp
// topic: Minimum Spanning Tree (kruskal)
// time: O(ElogE + E*α)
// space: O(V + E)
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
```

### Dijkstra
For dense graphs:
```cpp
// time: O(V² + E)
// space: O(V + E)
void dijkstra(int src, vector<int> & dist, vector<int> & par,
vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    dist.assign(n, INF);
    par.assign(n, -1);
    vector<char> vis(n, false);

    dist[src] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (v == -1 || dist[j] < dist[v]))
                v = j;
        }

        if (dist[v] == INF)
            break;

        vis[v] = true;
        for (auto edge : graph[v]) {
            int to = edge.first;
            int len = edge.second;

            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                par[to] = v;
            }
        }
    }
}

// get path
vector<int> restore_path(int src, int dst, vector<int> const& par) {
    vector<int> path;
    for (int v = t; v != s; v = par[v])
        path.push_back(v);
    path.push_back(s);
    reverse(path.begin(), path.end());
    return path;
}
```

For sparse graphs use a heap:
```cpp
vector<int> dijkstra(int start, vector<int> & dist, vector<int>& par,
vector<vector<pair<int, int>>>& graph) {
	int n = graph.size();
	dist[start] = 0;
	// max heap by default, so negate the dist
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
			if(dist[adj] > dist[v] + w) {
				dist[adj] = dist[v] + w;
        par[adj] = v;
				heap.push({-dist[adj], adj});
			}
		}
	}
	return dist;
}
```

### Bellman-Ford
Use for graphs w/ negative weights
```cpp
// time: O(V * E)
// space: O(V + E)
vector<int> path;
vector<int> dist;
int bellmanFord(int src, int dest, int n,
vector<vector<pair<int, int>>>& graph, bool wantPath) {
    dist = vector<int>(n, INF);
    vector<int> par(n, -1);
    dist[src] = 0;

    for (int i = 0; i < n - 1; ++i) {
        bool any_changes = false;
        for (int from = 0; from < n; ++from) {
            for (auto& [to, w] : graph[from]) {
                if (dist[from] < INF && dist[to] > dist[from] + w) {
                    dist[to] = dist[from] + w;
                    any_changes = true;
                    par[to] = from;
                }
            }
        }
    }

    if (wantPath && dist[dest] != INF) {
        for (int cur = dest; cur != -1; cur = par[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
    }
    return dist[dest];
}
```

### Floyd-Warshall

```cpp
// topic: Shortest Paths: all shortest paths for all (i, j)
// time: O(V³)
// space: O(V² + E)
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
```

### Bipartite Verification

```cpp
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
            else if(color[neighbor] == color[v]) return false;
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
```

### LCA via Binary Lifting

```cpp
// time: for precomputing O(Nlog)
// time: per query O(log(N))
// space: O(Nlog)
void getDepth(int node, int parent,
vector<int>& par, vector<vector<int>>& tree,
vector<int>& depth, int d) {
    par[node] = parent;
    depth[node] = d;
    for(auto &adj : tree[node]) {
        if (adj == parent) continue;
        getDepth(adj, node, par, tree, depth, d + 1);
    }
}

int getLOG(int depth) {
    int LOG = 1;
    while ((1 << LOG) <= depth) LOG++;
    return LOG;
}

int goUp(int& node, int steps, vector<vector<int>>& up, int LOG) {
    for(int i = 0; i < LOG; ++i, steps >>= 1) {
        if (steps & 1)
            node = up[node][i];
    }
    return node;
}

int lca(int a, int b, vector<vector<int>>& up, int LOG, vector<int>& depth) {
    if (depth[a] < depth[b])
        swap(a, b);

    int diff_depth = depth[a] - depth[b];
    goUp(a, diff_depth, up, LOG);

    if (a == b) return a;

    for (int i = LOG - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}

void binaryLifting(vector<int>& par, int& LOG, vector<int>& depth,
vector<vector<int>>& up, vector<vector<int>>& tree) {
    int n = par.size();
    // choose 0 as the root
    int root = 0;
    getDepth(root, root, par, tree, depth, 0);
    LOG = getLOG(n);
    up = vector<vector<int>>(n, vector<int>(LOG));

    // set parents
    for (int i = 0; i < n; ++i)
        up[i][0] = par[i];
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i < n; ++i) {
            up[i][j] = up[ up[i][j - 1] ][j - 1];
        }
    }
}

int main()  {

    int n, q;
    cin >> n >> q;
    vector<int> par(n);
    vector<vector<int>> tree(n);

    // if 0 is root:
    par[0] = 0;
    for(int i = 1; i < n; ++i) {
        int boss;
        cin >> boss;
        boss--;
        par[i] = boss;
        tree[i].push_back(boss);
        tree[boss].push_back(i);
    }

    // if we receive the edges:
    // for(int i = 0; i < n; ++i) {
    //     int a, b;
    //     cin >> a >> b;
    //     --a; --b;
    //     tree[a].push_back(b);
    //     tree[b].push_back(a);
    // }

    vector<int> depth(n);
    vector<vector<int>> up;
    int LOG;
    binaryLifting(par, LOG, depth, up, tree);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << lca(a, b, up, LOG, depth) + 1 << "\n";
    }

    return 0;
}
```

### Tarjan - Strong Connected Components (SCCs)

```cpp
class Tarjan {
public:
    int n;
    Tarjan(const vector<vector<int>>& graph) : graph(graph), n(graph.size()) {
        low.assign(n, INT_MAX);
        idx.assign(n, -1);
        vis.assign(n, false);
        on_stack.assign(n, false);
        counter = 0;
        num_sccs = 0;
    }

    vector<vector<int>> getSCCs() {
        vector<vector<int>> sccs;
        stack<int> invariant;
        for(int i = 0; i < n; ++i) {
            if (!vis[i]) {
                tarjanHelper(i, invariant, sccs);
            }
        }
        return sccs;
    }

    vector<pair<int, int>> getBridges() {
        vector<pair<int, int>> bridges;
        vector<int> disc(n, -1), low(n, -1);
        vector<bool> visited(n, false);
        int time = 0;

        function<void(int, int)> bridgeHelper = [&](int u, int parent) {
            visited[u] = true;
            disc[u] = low[u] = ++time;
            for(int v : graph[u]) {
                if (!visited[v]) {
                    bridgeHelper(v, u);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > disc[u]) {
                        bridges.push_back({u, v});
                    }
                } else if (v != parent) {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        for(int i = 0; i < n; ++i) {
            if (!visited[i]) {
                bridgeHelper(i, -1);
            }
        }
        return bridges;
    }

    vector<int> getArticulationPoints() {
        vector<int> articulation_points;
        vector<int> disc(n, -1), low(n, -1);
        vector<bool> visited(n, false), ap(n, false);
        int time = 0;

        function<void(int, int)> articulationHelper = [&](int u, int parent) {
            visited[u] = true;
            disc[u] = low[u] = ++time;
            int children = 0;
            for(int v : graph[u]) {
                if (!visited[v]) {
                    children++;
                    articulationHelper(v, u);
                    low[u] = min(low[u], low[v]);
                    if (parent != -1 && low[v] >= disc[u]) {
                        ap[u] = true;
                    }
                } else if (v != parent) {
                    low[u] = min(low[u], disc[v]);
                }
            }
            if (parent == -1 && children > 1) {
                ap[u] = true;
            }
        };

        for(int i = 0; i < n; ++i) {
            if (!visited[i]) {
                articulationHelper(i, -1);
            }
        }

        for(int i = 0; i < n; ++i) {
            if (ap[i]) {
                articulation_points.push_back(i);
            }
        }
        return articulation_points;
    }

    vector<vector<int>> getCondensationGraph() {
        vector<vector<int>> sccs = getSCCs();
        vector<int> scc_id(n, -1);
        vector<vector<int>> cond_graph;

        for(int i = 0; i < sccs.size(); ++i) {
            for(int v : sccs[i]) {
                scc_id[v] = i;
            }
        }

        unordered_set<int> nodes;
        for(const auto& scc : sccs) {
            cond_graph.push_back({});
            for(int u : scc) {
                for(int v : graph[u]) {
                    int scc_u = scc_id[u];
                    int scc_v = scc_id[v];
                    if (scc_u != scc_v && !nodes.count(scc_u * n + scc_v)) {
                        cond_graph[scc_u].push_back(scc_v);
                        nodes.insert(scc_u * n + scc_v);
                    }
                }
            }
        }
        return cond_graph;
    }

private:
    vector<vector<int>> graph;
    vector<int> low, idx;
    vector<bool> vis, on_stack;
    int counter, num_sccs;
    vector<vector<int>> sccs;

    void tarjanHelper(int cur, stack<int>& invariant, vector<vector<int>>& sccs) {
        idx[cur] = low[cur] = counter++;
        on_stack[cur] = true;
        invariant.push(cur);
        vis[cur] = true;

        for(int adj : graph[cur]) {
            if (!vis[adj]) {
                tarjanHelper(adj, invariant, sccs);
            }
            if (on_stack[adj]) {
                low[cur] = min(low[cur], low[adj]);
            }
        }

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
};
```

## Math

### Number Theory

#### Primality Test
Miller Rabin
```cpp
// time: O(logn)
// space: O(logn)
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}
```

#### Binary Exponentiation

```cpp
long long binpow(long long a, long long b, long long MOD) {
    a %= MOD;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
```
#### Sieve of Eratosthenes

```cpp
// time: O(nloglog)
// space: O(n)
vector<int> getPrimes(int n) {
    vector<bool> isPrime(n+1, true);
    vector<int> primes;
    isPrime[0] = false;
    isPrime[1] = false;
    
    for(int i = 2; i*i <= n; ++i) {
        if(!isPrime[i]) continue;
        
        for(int j = i*i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }

    for(int i = 0; i <= n; ++i) {
        if(isPrime[i]) primes.push_back(i);
    }
    
    return primes;
}
```

#### Segmented Sieve
```cpp
// count primes up to n
int count_primes(int n) {
    const int S = 10000;

    vector<int> primes;
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 2, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i])
                result++;
        }
    }
    return result;
}

// primes in range:
vector<char> segmentedSieve(long long L, long long R) {
    // generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<char> isPrime(R - L + 1, true);
    for (long long i : primes)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    return isPrime;
}
```

#### Binomial Coefficient
Simple version: probably works
```cpp
int inv(int a) {
    return a <= 1 ? a : MOD - (long long)(MOD/a) * inv(MOD % a) % MOD;
}

// compute fat
void computeFat(vector<int>& factorial, int n) {
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i % m;
    }
}

long long binomial_coefficient(int n, int k, vector<int>& factorial) {
    return factorial[n] * inv(factorial[k] * factorial[n - k] % MOD) % MOD;
}
```
#### Totient Function
Counts the number of integers between 1 and n inclusive, which are coprime to n.
```cpp
// time: O(sqrt(N))
// space: O(1)
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}
```

Totient of all nums from 1 to n
```cpp
// time: O(Nloglog)
// space: O(n)
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
```

## Strings

### Z Function

```cpp
// time: O(n)
// space: O(n)
int advance_right(string& s, int left, int right) {
    while(right < s.size() && s[right - left] == s[right]) {
        ++right;
    }
    --right;
    return right;
}

vector<int> z_func(string& pattern, string& text) {

    string s = pattern + "$" + text;
    vector<int> z(s.size());
    int left = 0, right = 0;

    for(int i = 1; i < s.size(); ++i) {
        if(i > right) {
            left = right = i;
            right = advance_right(s, left, right);
            z[i] = right - left + 1;
        }
        else { // inside z-box
            // position inside the box compared to pattern
            int i1 = i - left;
            // if i can't touch right border of z-box
            if(z[i1] + i - 1 < right) {
                z[i] = z[i1];
            }
            else {
                // reset z-box and try to expand it
                left = i;
                right = advance_right(s, left, right);
                z[i] = right - left + 1;
            }
        }
    }
    return z;
}

int main() {
    string txt, pat;
    cin >> pat >> txt;

    vector<int> z = z_func(pat, txt);
    vector<int> ans; // array w/ indices of pattern match

    for(int i = pat.size() + 1; i < z.size(); ++i) {
        if(z[i] == pat.size()) ans.push_back(i - pat.size() + 1);
    }

    for(auto &item : ans) {
        cout << item << " ";
    }

    cout << "\n";
    // print elems of z array
    for(int i = pat.size()+1; i < z.size(); ++i) {
        cout << z[i] << " ";
    }

    return 0;
}
```
