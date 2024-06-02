#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct LCAAlgorithm {
private:
    vector<vector<int>> graph;
    vector<vector<int>> initialW;
    vector<vector<int>> up;
    vector<vector<int>> w;
    vector<int> in;
    vector<int> out;
    int timer = 0;
    int len = 1;
public:
    void generateGraph(int n) {
        while ((1<<len) <= n)  ++len;
        graph.assign(n, vector<int>());
        initialW.assign(n, vector<int>());
        up.assign(n, vector<int>(len + 1));
        w.assign(n, vector<int>(len + 1));
        in.resize(n);
        out.resize(n);
        for (int i = 1; i <= n - 1; i++) {
            int p, weight;
            cin >> p >> weight;
            graph[p].push_back(i);
            initialW[p].push_back(weight);
        }
    }

    void dfs(int node, int parent = 0, int weight = 1e9 + 7) {
        in[node] = ++timer;
        up[node][0] = parent;
        w[node][0] = weight;
        for (int i = 1; i <= len; i++) {
            up[node][i] = up[up[node][i - 1]][i - 1];
            w[node][i] = min(w[node][i - 1], w[up[node][i - 1]][i - 1]);
        }
        for (int i = 0; i < graph[node].size(); i++) {
            int to = graph[node][i];
            if (to != parent) {
                dfs(to, node, initialW[node][i]);
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

    int getMin(int u, int v) {
        int ans = 1e9 + 7;
        for (int i = len; i >= 0; i--) {
            if (!isParent(up[u][i], v)) {
                ans = min(ans, w[u][i]);
                u = up[u][i];
            }
        }

        if (!isParent(u, v)) ans = min(ans, w[u][0]);

        for (int i = len; i >= 0; i--) {
            if (!isParent(up[v][i], u)) {
                ans = min(ans, w[v][i]);
                v = up[v][i];
            }
        }
        if (!isParent(v, u)) ans = min(ans, w[v][0]);

        return ans;
    }
};

int main() {
    int n, m, v, u;
    cin >> n;
    LCAAlgorithm solve;
    solve.generateGraph(n);
    solve.dfs(0);
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cout << solve.getMin(u, v) << '\n';
    }
    return 0;
}