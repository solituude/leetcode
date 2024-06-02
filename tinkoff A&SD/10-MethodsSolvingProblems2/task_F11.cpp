#include <iostream>
#include <vector>

using namespace std;

vector<int> A(11);
vector<int> s(21);
int len, minLen, n, m;
int64_t countCoin;
vector<int> sm(21);

void solve(int i, int64_t sum) {
    if (sum > n) return;

    if (i > m) {
        if (sum == n && (minLen == 0 || len < minLen)) {
            minLen = len;
            for (int j = 1; j <= minLen; j++)
                sm[j] = s[j];
        }
    } else {
        solve(i + 1, sum);
        for (int j = 1; j <= 2; j++) {
            len++;
            s[len] = A[i];
            solve(i + 1, sum + A[i] * j);
        }
        len -= 2;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> A[i];
        countCoin += A[i];
    }

    if (countCoin * 2 >= n) {
        solve(1, 0);
        cout << minLen << '\n';
        for (int i = 1; i <= minLen; i++)
            cout << sm[i] << ' ';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}
