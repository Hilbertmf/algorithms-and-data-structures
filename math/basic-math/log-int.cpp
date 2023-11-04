// runs in O(logn)
// get the integral part of logb(n)
int logBaseB(unsigned int n, unsigned int b) {
    int res = 0;    
    
    while (n >= b) {
        res++;
        n /= b;
    }return res;
}
