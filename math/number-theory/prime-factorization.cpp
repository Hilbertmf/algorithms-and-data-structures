#include <vector.h>
using namespace std;

// runs in O(loglog(n))
vector<int> getPrimes(int n) {
    vector<int> primes;

    while (n % 2 == 0) {
        if(primes.size() == 0)
            primes.push_back(2);
        n /= 2;
    }

    for(int i = 3; i*i <= n; i += 2) {
        int count = 1;
        while (n % i == 0) {
            if(count == 1)
                primes.push_back(i);
            n /= i;
            count++;
        }
    }

    if(n > 2)
        primes.push_back(n);

    return primes;
}

map<int, int> getPrimesAndOccurences(int n) {
    map<int, int> primes;

    while (n % 2 == 0) {
        n /= 2;
        primes[2]++;
    }

    for(int i = 3; i*i <= n; i += 2) {
        while (n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }

    if(n > 2)
        primes[n]++;

    return primes;
}
