#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void buildTree(int node, int treeLeft, int treeRight, vector<int> &tree, vector<int> &arr) {
    if (treeLeft == treeRight) {
        tree[node] = arr[treeLeft];
    } else {
        int mid = (treeLeft + treeRight) / 2;
        buildTree(node * 2, treeLeft, mid, tree, arr);
        buildTree(node * 2 + 1, mid + 1, treeRight, tree, arr);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
}

int getMinIndex (int indLeft, int indRight, int treeLeft, int treeRight, int node, int x, vector<int>& tree) {
    if (indLeft > indRight)
        return 1e9;
    int mid = (treeRight + treeLeft) / 2;

    if (treeLeft == treeRight) {
        if (tree[node] >= x) return treeRight;
        else return 1e9;
    }
    if (indLeft > treeLeft) {
        int leftChild = getMinIndex(indLeft, min(indRight, mid), treeLeft, mid, node * 2, x, tree);
        int rightChild = getMinIndex(max(indLeft, mid + 1), indRight, mid + 1, treeRight, node * 2 + 1, x, tree);
        return min(leftChild, rightChild);
    }

    if (tree[node * 2] >= x) {
        return getMinIndex(indLeft, min(indRight, mid), treeLeft, mid, node * 2, x, tree);
    } else {
        return getMinIndex(max(indLeft, mid + 1), indRight, mid + 1, treeRight, node * 2 + 1, x, tree);
    }
}


void updateTree(int index, int value, int node, int treeLeft, int treeRight, vector<int> &tree, vector<int> &arr) {
    if (treeRight == treeLeft) {
        tree[node] = value;
    } else {
        int mid = (treeLeft + treeRight) / 2;
        if (index <= mid) {
            updateTree(index, value, node * 2, treeLeft, mid, tree, arr);
        } else {
            updateTree(index, value, node * 2 + 1, mid + 1, treeRight, tree, arr);
        }
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> tree(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    buildTree(1, 0, n - 1, tree, a);
    for (int i = 0; i < m; i++) {
        int codeOperation;
        cin >> codeOperation;
        if (codeOperation == 1) {
            int ind, v;
            cin >> ind >> v;
            updateTree(ind, v, 1, 0, n - 1, tree, a);
        } else {
            int x, l;
            cin >> x >> l;
            int ans = getMinIndex(l, n - 1, 0, n - 1, 1, x, tree);
            if (ans == 1e9) {
                cout << -1 << '\n';
            } else {
                cout << ans << '\n';
            }
        }
    }
    return 0;
}