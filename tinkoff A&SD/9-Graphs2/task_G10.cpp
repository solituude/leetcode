#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

ll ans = 1e15+7;

bool dijkstra(vector<vector<pair<int, int>>> &g, int start, int a, int b, int c) {
    vector<ll> d(g.size(), 1e15);
    map<int, ll> q;
    d[start] = 0;
    q[start] = 0;
    while(!q.empty()) {
        auto node = q.begin();
        for (auto v: g[node->first]){
            if (d[v.first] > node->second + v.second) {
                d[v.first] = node->second + v.second;
                q[v.first] = d[v.first];
            }
        }
        q.erase(node);
    }
    if (d[a] >= 1e15 || d[b] >= 1e15 || d[c] >= 1e15) {
        return false;
    } else {
        ans = min(ans, d[a] + d[b] + d[c]);
        return true;
    }
}

int main() {
    int n, m, a, b, c, u, v, w;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u - 1].push_back({v - 1, w});
        g[v - 1].push_back({u - 1, w});
    }

    cin >> a >> b >> c;
    a--; b--; c--;
    if (!dijkstra(g, a, a, b, c)) {
        cout << -1;
    } else{
        dijkstra(g, b, a, b, c);
        dijkstra(g, c, a, b, c);
        cout << ans;
    }

    return 0;
}
