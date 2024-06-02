#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;

void getPow(vector<ull>&pow, int lenT, int k) {
    pow.push_back(1);
    for (int i = 0; i < lenT; i++) {
        pow.push_back(pow[i] * (ull)k);

    }
}

void getPolyHash(string str, vector<ull> &hash, vector<ull> pow) {
    hash.push_back(0);
    for (int i = 0; i < str.size(); i++) {
        ull currHash = hash[i] + pow[i] * (str[i] - 'a' + 1);
        hash.push_back(currHash);
    }
}

void getPolyHashSet(int lenStr, unordered_set<ull> &hashSet, vector<ull> hash, vector<ull> pow, int maxPow) {
    for (int i = 0; i < lenStr; i++) {
        ull hashWindow = (hash[i + lenStr] - hash[i]) * pow[maxPow - (i + lenStr - 1)];
        hashSet.insert(hashWindow);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string a, b, copyB;
    cin >> a >> b;
    int k = 131, count = 0;
    copyB = b + b;
    vector<ull> pow, hashA, hashCopyB;
    unordered_set<ull> hashSetB;
    int maxPow = max(a.size(), copyB.size() * 2);

    getPow(pow, maxPow * 2, k);
    getPolyHash(a, hashA, pow);
    getPolyHash(copyB, hashCopyB, pow);
    getPolyHashSet((int)b.size(), hashSetB, hashCopyB, pow, maxPow);

    for (int i = 0; i <= a.size() - b.size(); i++){
        ull hashSubA = (hashA[i + b.size()] - hashA[i]) * pow[maxPow - (i + b.size() - 1)];
        auto search = hashSetB.find(hashSubA);
        if (search != hashSetB.end()) {
            count++;
        }
    }

    cout << count;
    return 0;
}