#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m, a, b, c, d, maxLenStr = 1e5 + 3;
    int pow[maxLenStr], hash[maxLenStr], k = 31;
    int mod = 1e9 + 7;
    pow[0] = 1;
    hash[0] = 0;

    for (int i = 1; i < maxLenStr; i++) {
        pow[i] = (int)(((ll)pow[i - 1] * (ll)k) % mod);
    }

    string str;
    cin >> str;

    for (int i = 0; i < str.size(); i++) {
        hash[i + 1] = (int)(((ll)hash[i] + (ll)pow[i] * (ll)(str[i] - 'a' + 1)) % mod);
    }
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;

        int h1 = hash[b + 1] - hash[a];
        if (h1 < 0) {
            h1 += mod;
        }
        h1 = (int)(1ll * h1 * pow[str.size() - a] % mod);

        int h2 = hash[d + 1] - hash[c];
        if (h2 < 0) {
            h2 += mod;
        }
        h2 = (int)(1ll * h2 * pow[str.size() - c] % mod);

        if (h1 == h2) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
    return 0;
}

//abacabadaba
//5
//1 3 5 7
//1 11 1 11
//3 3 9 9
//2 3 9 10
//3 4 7 8