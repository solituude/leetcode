//
// Created by Дарья Белоусова on 21.04.2024.
//
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

using namespace std;

ll getCount(int i, vector<ll> &tree) {
    ll answer = 0;
    for (; i; i -= i & -i) {
        answer += tree[i];
    }
    return answer;
}

void toTop(int i, vector<ll> &tree, int n) {
    for (; i <= n; i += i & -i) {
        ++tree[i];
    }
}

int main() {
    vector<pair<int, int>> arr(1e5 + 1);
    vector<int> indexes(1e5 + 1);
    vector<ll> tree(1e5 + 1);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> arr[i].first;
        arr[i].second = i;
    }

    sort(arr.begin() + 1, arr.begin() + n + 1, greater<pair<int, int>>());
    for (int i = 1; i <= n; i++) {
        indexes[arr[i].second] = i;
    }
    ll weakness = 0, countPeople;
    for (int i = 1; i <= n; i++) {
        countPeople = getCount(indexes[i], tree);
        weakness += countPeople * (n - i - indexes[i] + countPeople + 1);
        toTop(indexes[i], tree, n);
    }
    cout << weakness;
}