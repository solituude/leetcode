#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

typedef long long ll;
vector<ll> t, sumHelp, setHelp;

void pushSet(int v, int tl, int tr) {
    if (setHelp[v] == LONG_LONG_MAX) {
        return;
    }
    t[v] = setHelp[v] * (tr - tl + 1);
    if (tr != tl) {
        setHelp[2 * v] = setHelp[v];
        setHelp[2 * v + 1] = setHelp[v];
        sumHelp[2 * v] = 0;
        sumHelp[2 * v + 1] = 0;
    }
    setHelp[v] = LONG_LONG_MAX;
}

void pushSum(int v, int tl, int tr) {
    if (sumHelp[v] == 0) {
        return;
    }
    t[v] += sumHelp[v] * (tr - tl + 1);
    if (tr != tl) {
        sumHelp[v * 2] += sumHelp[v];
        sumHelp[v * 2 + 1] += sumHelp[v];
        int mid = (tl + tr) / 2;
        pushSet(v * 2, tl , mid);
        pushSet(v * 2 + 1, mid + 1, tr);
        setHelp[v * 2] = LONG_LONG_MAX;
        setHelp[v * 2 + 1] = LONG_LONG_MAX;
    }
    sumHelp[v] = 0;
}


void add(int tl, int tr, int v, int l, int r, int x) {
    sumHelp[v] == 0 ? pushSet( v, tl, tr) : pushSum(v, tl, tr);

    if (l > tr || tl > r)
        return;
    if (tl >= l && tr <= r) {
        sumHelp[v] = x;
        sumHelp[v] == 0 ? pushSet( v, tl, tr) : pushSum(v, tl, tr);
        return;
    }

    int mid = (tl + tr) / 2;
    add(tl, mid, v * 2, l, r, x);
    add(mid + 1, tr, v * 2 + 1, l, r, x);
    t[v] = t[2 * v] + t[v * 2 + 1];
    setHelp[v] = LONG_LONG_MAX;
    sumHelp[v] = 0;
}

void set(int tl, int tr, int v, int l, int r, int x) {
    sumHelp[v] == 0 ? pushSet( v, tl, tr) : pushSum(v, tl, tr);
    if (l > tr || tl > r)
        return;
    if (tl >= l && tr <= r) {
        setHelp[v] = x;
        sumHelp[v] == 0 ? pushSet( v, tl, tr) : pushSum(v, tl, tr);
        return;
    }
    int mid = (tl + tr) / 2;
    set(tl, mid, v * 2, l, r, x);
    set(mid + 1, tr, v * 2 + 1, l, r, x);
    t[v] = t[v * 2] + t[v * 2 + 1];
    setHelp[v] = LONG_LONG_MAX;
    sumHelp[v] = 0;
}

ll getSum(int tl, int tr, int v, int l, int r) {
    sumHelp[v] == 0 ? pushSet( v, tl, tr) : pushSum(v, tl, tr);
    if (l > tr || tl > r)
        return 0;
    if (tl >= l && tr <= r){
        return t[v];
    }
    int mid = (tl + tr) / 2;
    return getSum(tl, mid, v * 2, l, r) + getSum(mid + 1, tr, v * 2 + 1, l, r);;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int N = pow(2, ::ceil(::log2(n)));
    t.assign(N * 2, 0);
    sumHelp.assign(N * 2, 0);
    setHelp.assign(N * 2, LONG_LONG_MAX);
    int type;
    for (int i = 0; i < m; i++) {
        cin >> type;
        if (type == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            set(0, N - 1, 1, l, r - 1, v);
        } else if (type == 2) {
            int l, r, v;
            cin >> l >> r >> v;
            add(0, N - 1, 1, l, r - 1, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << getSum(0, N - 1, 1, l, r - 1) << '\n';
        }
    }
    return 0;
}
