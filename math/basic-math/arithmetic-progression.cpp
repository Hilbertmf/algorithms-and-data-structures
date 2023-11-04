// runs in O(1)
// given first element, diff between elements and number of elements
int getAPSum(int a1, int d, int n) {
    return ((2*a1 + (n - 1) * d) * n) / 2;
}

// given first & last elements and number of elements
int getAPSum(int a1, int an, int n) {
    return ((a1 + an) * n) / 2;
}