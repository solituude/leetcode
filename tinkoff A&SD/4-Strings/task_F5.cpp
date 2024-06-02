#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

ll manacherOdd(string &s){
    int n = (int)s.size();
    vector<int> palICenter(n, 1);
    ll count = 0;
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i < right) {
            palICenter[i] = palICenter[left + right - i] < right - i + 1 ? palICenter[left + right - i] : right - i + 1;
        }
        while (i - palICenter[i] >= 0 && i + palICenter[i] < n && s[i - palICenter[i]] == s[i + palICenter[i]]) {
            palICenter[i]++;
        }
        if (i + palICenter[i] - 1 > right) {
            left = i - palICenter[i] + 1;
            right = i + palICenter[i] - 1;
        }
//        count += 1ll * palICenter[i];
    }
    for (int i = 0; i < n; i++) {
        count += 1ll * palICenter[i];
    }

    return count;
}

ll manacherEven(string &s) {
    int n = (int)s.size();
    vector<int> palICenter(n, 0);
    ll count = 0;
    int left = -1, right = -1;
    for (int i = 0; i < n - 1; i++) {
        if (i < right) {
            palICenter[i] = right - i < palICenter[left + right - i - 1] ? right - i : palICenter[left + right - i - 1];
        }
        while (i - palICenter[i] >= 0 && i + palICenter[i] + 1 < n && s[i - palICenter[i]] == s[i + palICenter[i] + 1]){
            palICenter[i]++;
        }
        if (i + palICenter[i] > right) {
            left = i - palICenter[i] + 1;
            right = i + palICenter[i];
        }
//        count += 1ll * palICenter[i];
    }
    for (int i = 0; i < n; i++) {
        count += 1ll * palICenter[i];
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin >> s;
    ll countOdd = manacherOdd(s);
    ll countEven = manacherEven(s);
    cout << countOdd + countEven;

    return 0;
}