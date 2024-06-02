#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;

typedef unsigned long long ull;

void getHash(vector<ull> &hash, vector<int> &arr, int n) {
    hash.push_back(0);
    ull res;
    for (int i = 0; i < n; i++) {
        res = hash[i] + (ull)arr[i] * (ull)arr[i] * (ull)arr[i] * (ull)(200003 - arr[i]);
        hash.push_back(res);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, currNum, maxLen = 0;
    vector<int> firstArr, secondArr;
    vector<ull> firstHash, secondHash;
    unordered_map<int, ull> randomMap;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> currNum;
        firstArr.push_back(currNum);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> currNum;
        secondArr.push_back(currNum);
    }

    getHash(firstHash, firstArr, n);
    getHash(secondHash, secondArr, m);

    for (int l1 = 0; l1 <= n; l1++) {
        for(int r1 = l1 + 1; r1 <= n; r1++) {
            ull hash1 = (firstHash[r1] - firstHash[l1]);
            for (int k = r1 - l1; k <= m; k++) {
                ull hash2 = (secondHash[k] - secondHash[k - (r1 - l1)]);
                if (hash1 == hash2) {
                    maxLen = max(maxLen, r1 - l1);
                }
            }
        }
    }

    cout << maxLen;
    return 0;
}



//3
//1 2 3
//4
//1 4 3 2

//5
//1 1 1 1 1
//4
//3 3 3 1


//7
//1 2 3 4 5 6 7
//7
//2 7 6 1 5 3 4

//3
//2 1 2
//2
//2 2

//5
//1 1 1 1 1
//4
//3 3 1 1


//10
//1 1 1 1 1 1 1 1 1 1
//10
//5 5 5 5 5 5 5 5 5 5

//3
//4 1 1
//3
//1 2 3