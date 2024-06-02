#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ull;

void getPow(vector<ull>&pow, int lenT, int k) {
    pow.push_back(1);
    for (int i = 0; i < lenT; i++) {
        pow.push_back(pow[i] * (ull)k);

    }
}

void getPolyHash(string &str, vector<ull> &hash, vector<ull> &pow) {
    hash.push_back(0);
    for (int i = 0; i < str.size(); i++) {
        ull currHash = hash[i] + pow[i] * (ull)(str[i] - 'a' + 1);
        hash.push_back(currHash);
    }
}

int main() {
    string s;
    int k = 31, lenS;
    cin >> s;
    lenS = s.size();
    s += s;
    vector<ull> pow, hash;
    getPow(pow, s.size() + 1, k);
    getPolyHash(s, hash, pow);
    int minShiftInd = 0, currLenSubstring = 0;
    for (int i = 1; i < lenS; i++) {
        int l = 0, r = lenS - 1;
        while (r >= l) {
            int mid = (r + l) / 2;
            ull hashMinShift = (hash[minShiftInd + mid] - hash[minShiftInd]) * pow[s.size() - minShiftInd];
            ull hashCurr = (hash[i + mid] - hash[i]) * pow[s.size() - i];
            if (hashCurr == hashMinShift) {
                currLenSubstring = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (s[i + currLenSubstring] < s[minShiftInd + currLenSubstring]) {
            minShiftInd = i;
        }
    }
//    cout << minShiftInd << endl;
    for (int i = minShiftInd; i < lenS; i++) {
        cout << s[i];
    }
    for (int i = 0; i < minShiftInd; i++) {
        cout << s[i];
    }
    return 0;
}