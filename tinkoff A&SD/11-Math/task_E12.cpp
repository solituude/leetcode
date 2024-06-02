#include <iostream>

using namespace std;

int MOD = 1e9 + 7;

typedef unsigned long long ull;

ull factorial(int a) {
    ull res = 1;
    for (int i = 2; i <= a; i++) {
        res = (res * i) % MOD;
    }
    return res;
}

ull binpow(ull a, ull p) {
    ull res = 1;
    while (p != 0) {
        if (p % 2 != 0) {
            res = ((res % MOD) * (a % MOD)) % MOD;
        }
        a = ((a % MOD) * (a % MOD)) % MOD;
        p >>= 1;
    }
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    ull a = factorial(n);
    ull b = (factorial(k) * factorial(n - k)) % MOD;
    ull inverseB = binpow(b, MOD - 2);
    ull res = ((a % MOD) * (inverseB % MOD)) % MOD;
    cout << res;
    return 0;
}
