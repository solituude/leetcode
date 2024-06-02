#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N = 2e5 + 1;
vector<int> parent(N);
vector<int> depth(N, 1);

struct Node{
    int a, b, len;
    Node(int a, int b, int len): a(a), b(b), len(len){}
};

bool comp(Node* a, Node* b) {
    return a->len < b->len;
}

int getRoot(int node){
    if (parent[node] == node) {
        return node;
    }
    return parent[node] = getRoot(parent[node]);
}


bool checkEdge(Node* node) {
    int rootA = getRoot(node->a);
    int rootB = getRoot(node->b);
    if (rootA == rootB) {
        return false;
    } else {
        if (depth[rootA] < depth[rootB]) {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        if (depth[rootA] == depth[rootB]) {
            depth[rootA]++;
        }
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, b, e, w;
    long long ans = 0;
    cin >> n >> m;

    for (int i = 0; i < n + 1; i++) {
        parent[i] = i;
    }

    vector<Node*> ostTree;
    for (int i = 0; i < m; i++) {
        cin >> b >> e >> w;
        ostTree.push_back(new Node(b, e, w));
    }
    sort(ostTree.begin(), ostTree.end(), comp);

    for (int i = 0; i < m; i++) {
        if (checkEdge(ostTree[i])) {
            ans += (long long)ostTree[i]->len;
        }
    }
    cout << ans;

    return 0;
}