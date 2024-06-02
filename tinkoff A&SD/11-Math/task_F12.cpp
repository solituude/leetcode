#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull binpow(ull a, ull p, ull mod) {
    ull res = 1;
    while (p != 0) {
        if (p % 2 != 0) {
            res = ((res % mod) * (a % mod)) % mod;
        }
        a = ((a % mod) * (a % mod)) % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    ull n, m, k, mod;
    cin >> n >> m >> k >> mod;
    ull countPasswords = binpow(m, n, mod);
    ull reverseK = binpow(k, mod - 2, mod);
    ull res = ((countPasswords % mod) * (reverseK % mod)) % mod;
    cout << res;
    return 0;
}