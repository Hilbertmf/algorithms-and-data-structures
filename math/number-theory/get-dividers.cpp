#include <vector.h>
using namespace std;

// runs in O(sqrt(n))
vector<int> getDividers(int n) {
    vector<int> dividers;
    for(int i = 2; i*i <= n; ++i) {
        if(n % i == 0) {
            dividers.push_back(i);
            if(n / i != i)
                dividers.push_back(n / i);
        }
    }
    return dividers;
}