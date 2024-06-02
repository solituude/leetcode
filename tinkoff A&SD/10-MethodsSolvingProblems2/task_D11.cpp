#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int l, n;
    cin >> l >> n;
    vector<int> cut(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cut[i];
    }
    cut[0] = 0;
    cut.push_back(l);
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int i = 1; i < n + 2; i++) {
        for (int j = i - 2; j >= 0; j--) {
            dp[j][i] = 1e9;
            for (int k = j + 1; k < i; k++) {
                dp[j][i] = min(dp[j][i], dp[j][k] + dp[k][i]);
            }
            dp[j][i] += cut[i] - cut[j];
        }
    }
    cout << dp[0][n+1];
    return 0;
}