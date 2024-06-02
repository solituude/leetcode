#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

const int mod = 1e9 + 7;

void buildTree(int index, pair<int, int> node, vector<pair<int, int>> &tree) {
    while (index < tree.size()) {
        if (tree[index].first < node.first) {
            tree[index] = node;
        } else if (tree[index].first == node.first) {
            tree[index].second = (tree[index].second + node.second) % mod;
        }
        index = index | (index + 1);
    }
}

pair<int, int> dfs(int index, vector<pair<int, int>> &tree) {
    pair<int, int> range_max = {0, 1};
    while (0 <= index) {
        if (range_max.first < tree[index].first) {
            range_max = tree[index];
        } else if (range_max.first == tree[index].first) {
            range_max.second = (range_max.second + tree[index].second) % mod;
        }
        index = (index & (index + 1)) - 1;
    }
    return range_max;
}

int findNumberOfLIS(vector<int> &arr) {
    set<int> sortedArr(arr.begin(), arr.end());

    unordered_map<int, int> map;

    int pos = 0;
    for (auto &num: sortedArr) {
        map[num] = pos++;
    }

    vector<pair<int, int>> tree(arr.size() + 1, {0, 0});

    for (auto &a: arr) {
        int index = map[a];
        pair<int, int> node = dfs(index - 1, tree);
        buildTree(index, {node.first + 1, node.second}, tree);
    }
    return dfs((int)sortedArr.size(), tree).second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << findNumberOfLIS(arr);
    return 0;
}