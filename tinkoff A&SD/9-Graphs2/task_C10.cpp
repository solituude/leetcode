#include <iostream>
#include <vector>

using namespace std;

vector<int> parents(1e4 + 1, -1);
vector<int> depth(1e4 + 1, 0);

struct Node {
    int a, b, len;
    Node(int a, int b, int len): a(a), b(b), len(len){}
};

int getRoot(int node){
    if (parents[node] < 0) {
        return node;
    }
    return parents[node] = getRoot(parents[node]);
}

bool checkEdge(int a, int b) {
    int rootA = getRoot(a);
    int rootB = getRoot(b);
    if (rootA == rootB) {
        return false;
    } else {
        if (parents[rootA] < parents[rootB]) {
            parents[rootA] += parents[rootB];
            parents[rootB] = rootA;
        } else {
            parents[rootB] += parents[rootA];
            parents[rootA] = rootB;
        }
        return true;
    }
}

int main() {
    int n, m, num;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> num;
            if (num == 1 || num == 3) {
                if ((i - 1) * m + j <= n * m && i * m + j <= n * m){
                    checkEdge((i - 1) * m + j, i * m + j);
                }
            }
            if (num == 2 || num == 3) {
                if ((i - 1) * m + j + 1 <= n * m) {
                    checkEdge((i - 1) * m + j, (i - 1) * m + j + 1);
                }
            }
        }
    }

    vector<Node*> tree;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i - 1) * m + j <= n * m && i * m + j <= n * m && checkEdge((i - 1) * m + j, i * m + j)) {
                tree.push_back(new Node(i, j, 1));
                ans += 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i - 1) * m + j <= n * m && (i - 1) * m + j + 1 <= n * m && checkEdge((i - 1) * m + j, (i - 1) * m + j + 1)) {
                tree.push_back(new Node(i, j, 2));
                ans += 2;
            }
        }
    }
    cout << tree.size() << " " << ans << '\n';
    for (int i = 0; i < tree.size(); i++) {
        cout << tree[i]->a << " " << tree[i]->b << " " << tree[i]->len << '\n';
    }
    return 0;
}

