// runs in O(1)
// given first element, ratio and num of elements
int PG(int a1, int q, int n) {
    return (a1 * (powl(q, n) - 1)) / (q - 1);
}