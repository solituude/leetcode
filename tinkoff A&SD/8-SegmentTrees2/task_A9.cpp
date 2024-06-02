#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

typedef long long ll;

void propagate(vector<ll> &tree, vector<ll> &lazy, int node) {
    tree[node * 2 + 1] += lazy[node];
    lazy[node * 2 + 1] += lazy[node];
    tree[node * 2 + 2] += lazy[node];
    lazy[node * 2 + 2] += lazy[node];
    lazy[node] = 0;

}

void add(vector<ll> &tree, int tl, int tr, int node, int l, int r, int value, vector<ll> &lazy) {
    if (l >= tr || tl >= r) return;
    if (tl >= l && tr <= r) {
        lazy[node] += value;
        tree[node] += value;
        return;
    }
    if (lazy[node] != 0) {
        propagate(tree, lazy, node);
    }
    int mid = (tl + tr) / 2;
    add(tree, tl, mid, node * 2 + 1, l, r, value, lazy);
    add(tree, mid, tr, node * 2 + 2, l, r, value, lazy);
    tree[node] = min(tree[2 * node + 1], tree[node * 2 + 2]);
}

ll getMin(vector<ll> &tree, int tl, int tr, int node, int l, int r, vector<ll> &lazy) {
    if (l >= tr || tl >= r)
        return LONG_LONG_MAX;
    if (tl >= l && tr <= r){
        return tree[node];
    }
    propagate(tree, lazy, node);
    int mid = (tl + tr) / 2;
    ll leftChild = getMin(tree, tl, mid, node * 2 + 1, l, r, lazy);
    ll rightChild = getMin(tree, mid, tr, node * 2 + 2, l, r, lazy);
    return min(leftChild, rightChild);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, typeOperation, l, r, v;
    cin >> n >> m;
    int len = 1;
    while (len < n) {
        len *= 2;
    }
    n = len * 2 - 1;
    vector<ll> tree(n * 2, 0);
    vector<ll> lazy(n * 2, 0);
    for (int i = 0; i < m; i++) {
        cin >> typeOperation;
        if (typeOperation == 1) {
            cin >> l >> r >> v;
            add(tree, 0, n, 0, l, r, v, lazy);
        } else {
            cin >> l >> r;
            cout << getMin(tree, 0, n, 0, l, r, lazy) << '\n';
        }
    }
    return 0;
}
//
//11 20
//1 0 11 1
//1 3 8 3
//2 8 11
//2 7 9
//2 5 8


