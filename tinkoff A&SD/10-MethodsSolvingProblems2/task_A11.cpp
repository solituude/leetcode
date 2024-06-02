#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct LCAAlgorithm {
private:
    vector<vector<int>> graph;
    vector<vector<int>> up;
    vector<int> in;
    vector<int> out;
    int timer = 0;
    int len = 1;
public:
    void generateGraph(int n) {
        while ((1<<len) <= n)  ++len;
        graph.assign(n, vector<int>());
        up.assign(n, vector<int>(len + 1));
        in.resize(n);
        out.resize(n);
        for (int i = 1; i <= n - 1; i++) {
            int p;
            cin >> p;
            graph[p].push_back(i);
        }
    }

    void dfs(int node, int parent) {
        in[node] = ++timer;
        up[node][0] = parent;
        for (int i = 1; i <= len; i++) {
            up[node][i] = up[up[node][i - 1]][i - 1];
        }
        for (int i = 0; i < graph[node].size(); i++) {
            int to = graph[node][i];
            if (to != parent) {
                dfs(to, node);
            }
        }
        out[node] = ++timer;
    }

    bool isParent(int u, int v){
        return in[u] <= in[v] && out[u] >= out[v];
    }

    int lca(int u, int v) {
        if (isParent(u, v)) return u;
        if (isParent(v, u)) return v;

        for (int i = len; i >= 0; i--){
            if (!isParent(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
};

int main() {
    int n, m, v, u;
    cin >> n;
    LCAAlgorithm solve;
    solve.generateGraph(n);
    solve.dfs(0, 0);
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cout << solve.lca(u, v) << '\n';
    }

    return 0;
}