#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7; // 10^9 + 7
 
long long power(long long a, long long b) {
    if(b == 0) return 1;
    if(b == 1) return a;
 
    long long res = 1;

    while (b) {
        if (b & 1)
            res = (res * a) % MOD;
        a *= a;
        a %= MOD;
        b >>= 1;
    }

    return res % MOD;
}
 
int main() {
    int queries;
    cin >> queries;
    
    while(queries--){
 
        long long a, b;
        cin >> a >> b;
        cout << power(a, b) << "\n";
 
    }    
    return 0;
}