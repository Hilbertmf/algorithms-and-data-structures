#include <bits/stdc++.h>
using namespace std;

struct segtree {
    int size;
    vector<int> sums;

    void init(int _size) {
        size = _size;
        sums = vector<int>(size * 4);
    }

    void update(int pos, int val) {
        update(pos, val, 0, size - 1, 0);
    }

    void update(int pos, int val, int left, int right, int node) {
        // if leaf
        if(left == right)
            sums[node] = val;
        else {
            int mid = (left + right) / 2;
            if(pos <= mid)
                update(pos, val, left, mid, 2*node + 1);
            else
                update(pos, val, mid + 1, right, 2*node + 2);
            // update ancestrals
            sums[node] = sums[2*node + 1] + sums[2*node + 2];
        }
    }

    int querySum(int queryLeft, int queryRight) {
        return querySum(0, size - 1, 0, queryLeft, queryRight);
    }
    
    int querySum(int left, int right, int node, int queryLeft, int queryRight) {
        // totally inside range
        if(queryLeft <= left && queryRight >= right)
            return sums[node];
        // totally outside
        if(left > queryRight || right < queryLeft)
            return 0;
        int mid = (left + right) / 2;
        return querySum(left, mid, 2*node + 1, queryLeft, queryRight) +
                querySum(mid + 1, right, 2*node + 2, queryLeft, queryRight);
    }

};
