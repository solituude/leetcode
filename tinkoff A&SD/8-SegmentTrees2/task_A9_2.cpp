#include "vector"
#include "iostream"

using namespace std;

struct segmentTree {
    vector<long long> tree;
    vector<long long> changes;
    vector<long long> additions;

    segmentTree(int n) {
        int len = 1;
        while (len < n) {
            len *= 2;
        }
        tree = vector<long long>(2 * len - 1, 0);
        changes = vector<long long>(2 * len - 1, 0);
        additions = vector<long long>(2 * len - 1, 0);
    }

    void propagate(int v, int tl, int tr) {
        if (changes[v] != 0 && 2 * v + 1 < tree.size()) {
            changes[v * 2] = changes[v * 2 + 1] = changes[v];
            changes[v] = 0;
            additions[v * 2] = additions[v * 2 + 1] = 0;
            int tm = (tl + tr) / 2;
            tree[v * 2] = changes[v * 2] * (tm - tl + 1);
            tree[v * 2 + 1] = changes[v * 2 + 1] * (tr - tm);
        } else if (additions[v] != 0 && 2 * v + 1 < tree.size()) {
            additions[v * 2] = additions[v * 2 + 1] = additions[v];
            additions[v] = 0;
        }
    }

    long long get_sum(int l, int r, int v, int tl, int tr) {
        if (l <= tl && tr <= r) {
            return tree[v] + additions[v] * (tr - tl + 1);
        }
        if (tr < l || r < tl) {
            return 0;
        }
        propagate(v, tl, tr);
        int tm = (tl + tr) / 2;
        return get_sum(l, r, v * 2, tl, tm)
               + get_sum(l, r, v * 2 + 1, tm + 1, tr);
    }

    void change(int l, int r, int val, int v, int tl, int tr) {
        if (l <= tl && tr <= r) {
            changes[v] = val;
            additions[v] = 0;
            tree[v] = (tr - tl + 1) * changes[v];
            return;
        }
        if (tr < l || r < tl) {
            return;
        }
        propagate(v, tl, tr);
        int tm = (tl + tr) / 2;
        change(l, r, val, v * 2, tl, tm);
        change(l, r, val, v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void plus(int l, int r, int val, int v, int tl, int tr) {
        if (l <= tl && tr <= r) {
            if (changes[v] != 0) {
                changes[v] += val;
                additions[v] = 0;
                tree[v] = (tr - tl + 1) * changes[v];
            } else {
                additions[v] += val;
            }
            return;
        }
        if (tr < l || r < tl) {
            return;
        }
        propagate(v, tl, tr);
        int tm = (tl + tr) / 2;
        plus(l, r, val, v * 2, tl, tm);
        plus(l, r, val, v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    segmentTree tree(n);
    int type, l, r, v;
    for (int i = 0; i < m; i++) {
        cin >> type;
        if (type == 1) {
            cin >> l >> r >> v;
            tree.change(l, r - 1, v, 1, 0, n - 1);
        } else if (type == 2) {
            cin >> l >> r >> v;
            tree.plus(l, r - 1, v, 1, 0, n - 1);
        } else {
            cin >> l >> r;
            cout << tree.get_sum(l, r - 1, 1, 0, n - 1) << endl;
        }

    }
    return 0;
}