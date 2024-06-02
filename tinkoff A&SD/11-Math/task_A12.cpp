#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, k, a, b, ans;
    cin >> n >> k;
    a = n; b = k;
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    ans = (n * k) / a;
    cout << ans;
    return 0;
}
