#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct window {
    int x, y1, y2;
    bool isOpen;
    window(int x, int y1, int y2, bool isOpen): x(x), y1(y1), y2(y2), isOpen(isOpen) {}
};

void updateTree(int treeLeft, int treeRight, int node, int left, int right, int value, vector<int> &tree, vector<int> &ind, vector<int> &add) {
    if (treeRight <= left || right <= treeLeft) {
        return;
    }
    if (left >= treeLeft && right <= treeRight) {
        add[node] += value;
        tree[node] += value;
        return;
    }
    tree[2 * node + 1] += add[node];
    tree[2 * node + 2] += add[node];
    add[2 * node + 1] += add[node];
    add[2 * node + 2] += add[node];
    add[node] = 0;
    int mid = (left + right) / 2;
    updateTree(treeLeft, treeRight, 2 * node + 1, left, mid, value, tree, ind, add);
    updateTree(treeLeft, treeRight, 2 * node + 2, mid, right, value, tree, ind, add);

    if (tree[node * 2 + 1] > tree[node * 2 + 2]){
        ind[node] = ind[node * 2 + 1];
        tree[node] = tree[node * 2 + 1];
    } else {
        ind[node] = ind[node * 2 + 2];
        tree[node] = tree[node * 2 + 2];
    }
}

int comp(window* a, window* b) {
    if (a->x == b->x) {
        return a->isOpen > b->isOpen;
    } else {
        return a->x < b->x;
    }
}

int main() {
    int n, x1, x2, y1, y2, maxN = ::pow(2, 19), xAns = 0, yAns = 0, maxCountWindows = 0;
    vector<window*> windows;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        windows.push_back(new window(x1 + 2e5, y1 + 2e5, y2 + 2e5, true));
        windows.push_back(new window(x2 + 2e5, y2 + 2e5, y1 + 2e5, false));
    }
    sort(windows.begin(), windows.end(), comp);
    vector<int> tree (2 * maxN - 1, 0);
    vector<int> ind (2 * maxN - 1);
    vector<int> add(2 * maxN - 1, 0);

    int currN = maxN - 1;
    while (currN < 2 * maxN - 1) {
        ind[currN]  = currN - maxN + 1;
        currN++;
    }
    currN = maxN - 2;
    while (currN > 0) {
        ind[currN]  = ind[currN * 2 + 1];
        currN--;
    }

    for (int i = 0; i < windows.size(); i++) {
        if (windows[i]->isOpen) {
            updateTree(windows[i]->y1 + maxN - 1, windows[i]->y2 + maxN, 0, maxN - 1, 2 * maxN - 1, 1, tree, ind, add);
        } else {
            updateTree(windows[i]->y2 + maxN - 1, windows[i]->y1 + maxN, 0, maxN - 1, 2 * maxN - 1, -1, tree, ind, add);
        }

        if (tree[0] > maxCountWindows) {
            maxCountWindows = tree[0];
            yAns = ind[0];
            xAns = windows[i]->x;
        }
    }
    cout << maxCountWindows << '\n';
    cout << xAns - 2e5 << " " << yAns - 2e5 << '\n';
    return 0;
}

