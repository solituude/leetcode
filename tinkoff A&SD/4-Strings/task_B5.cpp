#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ull;

void getPow(vector<ull>&pow, int lenT, ull mod, int k) {
    pow.push_back(1);
    for (int i = 0; i < lenT; i++) {
        pow.push_back((1ll * pow[i] * k));
    }
}

void getPolyHash(string str, ull mod, vector<ull> &hash, vector<ull> pow) {
    hash.push_back(0);
    for (int i = 0; i < str.size(); i++) {
        ull currHash = (hash[i] + pow[i] * (str[i] - 'a' + 1));
        hash.push_back(currHash);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q, k = 31;
    string T, s;
    cin >> T;
    cin >> q;
    ull mod = 1e19 + 3;
    vector<ull> powString, hashString;

    getPow(powString, (int)T.size(), mod, k);
    getPolyHash(T, mod, hashString, powString);

    for (int i = 0; i < q; i++) {
        cin >> s;
        vector<int> ansArr;
        vector<ull> hashSubstring;
        int count = 0;
        getPolyHash(s, mod, hashSubstring, powString);
        for (int j = s.size(); j <= T.size(); j++) {
            ull hSub = powString[j] * hashSubstring[hashSubstring.size() - 1];
            ull hStr = powString[s.size()] * (hashString[j] - hashString[j - s.size()]);
            if (hStr == hSub) {
                count++;
                ansArr.push_back(j - s.size());
            }
        }
        cout << count << " ";
        for (int j = 0; j < ansArr.size(); j++) {
            cout << ansArr[j] << " ";
        }
        cout << '\n';
    }

    return 0;
}