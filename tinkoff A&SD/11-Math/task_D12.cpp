#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    long long res = 1, mod = 1e9;
    cin >> n;

    for (int i = 2; i <= n; i++) {
        res = (long long)(res * i);
        while (res > 0 && res % 10 == 0) {
            res /= 10;
        }
        res %= mod;
    }
//    cout << res << endl;
//    while (res > 0 && res % 10 == 0) {
//        res /= 10;
//    }
    cout << res % 10;
    return 0;
}
