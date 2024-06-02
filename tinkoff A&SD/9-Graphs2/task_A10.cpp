#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N = 3e5 + 1;
vector<int> parents(N);
vector<int> counts(N, 1);
vector<int> minSet(N);
vector<int> maxSet(N);
vector<int> depth(N, 0);

int getRoot(int node){
    if (parents[node] == node) {
        return node;
    }
    return parents[node] = getRoot(parents[node]);
}

void unionSet(int x, int y) {
    int rootX = getRoot(x);
    int rootY = getRoot(y);
    if (rootX == rootY){
        return;
    }
    if (depth[rootX] < depth[rootY]) {
        swap(rootY, rootX);
    }
    parents[rootY] = rootX;
    if (depth[rootX] == depth[rootY]) {
        depth[rootX]++;
    }
    minSet[rootX] = min(minSet[rootX], minSet[rootY]);
    maxSet[rootX] = max(maxSet[rootX], maxSet[rootY]);
    counts[rootX] += counts[rootY];
}

void getSet(int x) {
    int rootX = getRoot(x);
    cout << minSet[rootX] << " " << maxSet[rootX] << " " << counts[rootX] << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, x, y;
    string opType;
    cin >> n >> m;
    for (int i = 0; i < n + 1; i++) {
        parents[i] = i;
        minSet[i] = i;
        maxSet[i] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> opType;
        if (opType == "union") {
            cin >> x >> y;
            unionSet(x, y);
        } else {
            cin >> x;
            getSet(x);
        }
    }
    return 0;
}