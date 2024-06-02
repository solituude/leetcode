#include <iostream>
#include <vector>
#include <string>

using namespace std;

int INF = 1e9;

void maxCorrectString(vector<vector<int> > &dp, vector<vector<int> > &positions, int left, int right, string &s) {
    int first = right - left + 1;
    if (dp[left][right] == first) {
        return;
    }
    if (dp[left][right] == 0) {
        for (int i = left; i < right + 1; i++) {
            cout << s[i];
        }
        return;
    }
    if (positions[left][right] == -1) {
        cout << s[left];
        maxCorrectString(dp, positions, left + 1, right - 1, s);
        cout << s[right];
        return;
    }
    maxCorrectString(dp, positions, left, positions[left][right], s);
    maxCorrectString(dp, positions, positions[left][right] + 1, right, s);
}

int main() {
    int min, minCount;
    string str;
    cin >> str;
    vector<vector<int> > dp(str.size(), vector<int>(str.size(), 0)), positions(str.size(), vector<int>(str.size(), 0));

    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j < str.size(); j++) {
            if (i == j) dp[i][j] = 1;
        }
    }

    for (int r = 0; r < (int)str.size(); r++) {
        for (int l = r; l >= 0; l--) {
            if (l == r) dp[l][r] = 1;
            else {
                minCount = -1;
                min = INF;
                bool isCorrBrackets1 = str[l] == '[' && str[r] == ']';
                bool isCorrBrackets2 = str[l] == '(' && str[r] == ')';
                bool isCorrBrackets3 = str[l] == '{' && str[r] == '}';

                if (isCorrBrackets1 || isCorrBrackets2 || isCorrBrackets3) {
                    min = dp[l + 1][r - 1];
                }
                for (int j = l; j < r; j++) {
                    if (min > dp[l][j] + dp[j + 1][r]) {
                        min = dp[l][j] + dp[j + 1][r];
                        minCount = j;
                    }
                }
                dp[l][r] = min;
                positions[l][r] = minCount;
            }
        }
    }
    maxCorrectString(dp, positions, 0, (int)(str.size()) - 1, str);
    return 0;
}