#include <bits/stdc++.h>
using namespace std;
#define MID(a, b) (a + b) / 2

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
    int size;
    vector<int> nodes;

    void init(int n) {
        size = n;
        nodes.resize(n * 4);
    }

    int query(int l, int r, int node, int from, int to) {
        // totally inside this node range
        if (allIn(from, to, l, r))
            return nodes[node];
        // totally outside
        else if (allOut(from, to, l, r))
            return 0;
        int mid = MID(from, to);
        return query(l, r, 2*node+1, from, mid) +
               query(l, r, 2*node+2, mid + 1, to);
    }
    int query(int left, int right) {
        return query(left, right, 0, 0, size - 1);
    }

    void update(int pos, int val, int node, int from, int to) {
        if (leaf(from, to))
            nodes[node] = val;
        else {
            int mid = MID(from, to);
            if (pos <= mid)
                update(pos, val, 2*node+1, from, mid);
            else
                update(pos, val, 2*node+2, mid + 1, to);
            // update ancestrals
            nodes[node] = nodes[2*node + 1] + nodes[2*node + 2];
        }
    }
    void update(int pos, int val) {
        update(pos, val, 0, 0, size - 1);
    }
};
