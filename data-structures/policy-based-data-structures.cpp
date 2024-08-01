#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, // key type
null_type, // mapped-policy
less<int>, // key comparison function
rb_tree_tag, // underlying data structure
tree_order_statistics_node_update>
ordered_set;
// use order_of_key and find_by_order methods
ordered_set bit;