#include <iostream>
#include <vector>


using namespace std;

void buildTree(int node, int treeLeft, int treeRight, vector<pair<int, int>> &tree, vector<int> &arr) {
    if (treeLeft == treeRight) {
        tree[node] = {arr[treeLeft], 1};
    } else {
        int tm = (treeLeft + treeRight) / 2;
        buildTree(node * 2, treeLeft, tm, tree, arr);
        buildTree(node * 2 + 1, tm + 1, treeRight, tree, arr);

        if (tree[node * 2].first < tree[node * 2 + 1].first) {
            tree[node] = tree[node * 2];
        } else if (tree[node * 2 + 1].first < tree[node * 2].first) {
            tree[node] = tree[node * 2 + 1];
        } else {
            tree[node] = {tree[node * 2].first, tree[node * 2].second + tree[node * 2 + 1].second};
        }
    }
}

pair<int, int> getMin(int left, int right, int node, int treeLeft, int treeRight, vector<pair<int, int>> &tree) {
    if (left == treeLeft && treeRight == right) {
        return tree[node];
    }
    if (treeRight < left || right < treeLeft) {
        return {1e9, 0};
    }
    int treeMid = (treeLeft + treeRight) / 2;
    pair<int, int> leftChild = getMin(left, min(treeMid, right), node * 2, treeLeft, treeMid, tree);
    pair<int, int> rightChild = getMin(max(treeMid + 1, left), right, node * 2 + 1, treeMid + 1, treeRight, tree);

    if (leftChild.first < rightChild.first) {
        return leftChild;
    } else if (leftChild.first > rightChild.first) {
        return rightChild;
    } else {
        return {leftChild.first, rightChild.second + leftChild.second};
    }
}


void updateTree(int index, int value, int node, int treeLeft, int treeRight, vector<pair<int, int>> &tree) {
    if (treeLeft == treeRight) {
        tree[node] = {value, 1};
    } else {
        int tm = (treeLeft + treeRight) / 2;
        if (index <= tm) {
            updateTree(index, value, node * 2, treeLeft, tm, tree);
        } else {
            updateTree(index, value, node * 2 + 1, tm + 1, treeRight, tree);
        }
        if (tree[node * 2].first < tree[node * 2 + 1].first) {
            tree[node] = tree[node * 2];
        } else if (tree[node * 2 + 1].first < tree[node * 2].first) {
            tree[node] = tree[node * 2 + 1];
        } else {
            tree[node] = {tree[node * 2].first, tree[node * 2].second + tree[node * 2 + 1].second};
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    pair<int, int> ans;
    vector<pair<int, int>> tree(4 * n, {1e9, 0});
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    buildTree(1, 0, n - 1, tree, a);
    for (int i = 0; i < k; i++) {
        int codeOperation;
        cin >> codeOperation;
        if (codeOperation == 1) {
            int ind, v;
            cin >> ind >> v;
            updateTree(ind, v, 1, 0, n - 1, tree);
        } else {
            int l, r;
            cin >> l >> r;
            ans = getMin(l, r - 1, 1, 0, n - 1, tree);
            cout << ans.first <<  " " << ans.second << '\n';
        }
    }
    return 0;
}