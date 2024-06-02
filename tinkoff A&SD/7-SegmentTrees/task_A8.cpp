#include <iostream>
#include <vector>

using namespace std;

void buildTree(int node, int treeLeft, int treeRight, vector<int> &tree, vector<int> &arr) {
    if (treeLeft == treeRight) {
        tree[node] = arr[treeLeft];
    } else {
        int tm = (treeLeft + treeRight) / 2;
        buildTree(node * 2, treeLeft, tm, tree, arr);
        buildTree(node * 2 + 1, tm + 1, treeRight, tree, arr);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

long long getSum(int left, int right, int node, int treeLeft, int treeRight, vector<int> &tree) {
    if (left <= treeLeft && treeRight <= right) {
        return tree[node];
    }
    if (treeRight < left || right < treeLeft) {
        return 0;
    }
    int tm = (treeLeft + treeRight) / 2;
    return getSum(left, right, node * 2, treeLeft, tm, tree) + getSum(left, right, node * 2 + 1, tm + 1, treeRight, tree);
}


void updateTree(int index, int value, int node, int treeLeft, int treeRight, vector<int> &tree, vector<int> &arr) {
    if (index <= treeLeft && treeRight <= index) {
        arr[index] = value;
        tree[node] = value;
        return;
    }
    if (treeRight < index || index < treeLeft) {
        return;
    }
    int tm = (treeLeft + treeRight) / 2;
    updateTree(index, value, node * 2, treeLeft, tm, tree, arr);
    updateTree(index, value, node * 2 + 1, tm + 1, treeRight, tree, arr);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> tree(4 * n, 1e9);
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
            updateTree(ind, v, 1, 0, n - 1, tree, a);
        } else {
            int l, r;
            cin >> l >> r;
            cout << getSum(l, r - 1, 1, 0, n - 1, tree) << '\n';
        }
    }
    return 0;
}