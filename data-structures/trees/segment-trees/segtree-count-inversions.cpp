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

    int query(int queryLeft, int queryRight) {
        return query(0, size - 1, 0, queryLeft, queryRight);
    }
    
    int query(int left, int right, int node, int queryLeft, int queryRight) {
        // totally inside range
        if(queryLeft <= left && queryRight >= right)
            return sums[node];
        // totally outside
        if(left > queryRight || right < queryLeft)
            return 0;
        int mid = (left + right) / 2;
        return query(left, mid, 2*node + 1, queryLeft, queryRight) +
                query(mid + 1, right, 2*node + 2, queryLeft, queryRight);
    }

};

int main() {

    cout << "size of array:" << "\n";
    int sz;
    cin >> sz;
    vector<int> nums(sz);
    cout << "input " << sz << " numbers:" << "\n";
    for(int i = 0; i < sz; ++i) {
        cin >> nums[i];
    }

    // brute force:
    int ans = 0;
    for(int i = 0; i < sz; ++i) {
        int currAns = 0;

        for(int j = i - 1; j >= 0; --j) {
            if(nums[j] > nums[i]) currAns++;
        }
        ans += currAns;
        
        cout << "for idx " << i << ": " << currAns << "\n";
    }
    cout << "num of inversions: " << ans << "\n";
    cout << "\n";

    segtree tree;
    tree.init(sz);

    for(int i = 0; i < sz; ++i) {
        tree.update(i, 0);
    }
    
    // using segment trees and inversion counting:
    vector<pair<int, int>> aux(sz);
    for(int i = 0; i < sz; ++i) {
        aux[i] = {nums[i], i};
    }
    
    sort(aux.begin(), aux.end());

    ans = 0;    
    for(int i = 0; i < sz; ++i) {
        int idx = aux[i].second;
        int currAns = tree.query(idx, sz - 1);
        ans += currAns;
        tree.update(idx, 1);
        
        cout << "for idx " << aux[i].second << ": " << currAns << "\n";
    }
    cout << "num of inversions: " << ans << "\n";


    return 0;
}