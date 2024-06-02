#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string str, temp, strMin;
    bool repeat;
    cin >> str;
    int n = (int)str.size(), r, l2;
    vector<vector<string>> dp(n, vector<string>(n));
    for (int size = 1; size <= n; size++) {
        for (int l = 0; l + size - 1 < n; l++) {
            strMin = str.substr(l, size);
            r = l + size - 1;
            if (size > 4) {
                for (int r1 = l; r1 < r; r1++) {
                    l2 = r1 + 1;
                    temp = dp[l][r1] + dp[l2][r];
                    if (temp.size() < strMin.size()) strMin = temp;
                }
                for (int k = 1; k < size; k++) {
                    if (size % k == 0) {
                        repeat = true;
                        for (int i = l + k; i <= r; i++) {
                            if (str[i] != str[i - k]) {
                                repeat = false;
                                break;
                            }
                        }
                        if (repeat) {
                            temp = to_string(size / k) + '(' + dp[l][l + k - 1] + ')';
                            if (temp.size() < strMin.size()) strMin = temp;
                        }
                    }
                }
            }
            dp[l][r] = strMin;
        }
    }
    cout << dp[0][n - 1];
    return 0;
}