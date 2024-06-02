#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
typedef long long ll;

int N = 3e5;
ll INF = 1e15 + 9;


vector<vector<pair<int, int>>> g(N, vector<pair<int, int>>());
vector<ll> dist;

int main() {
    int n, m, a, b, len;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> len;
        g[a - 1].push_back({b - 1, len});
        g[b - 1].push_back({a - 1, len});
    }
    dist.assign(n, INF);
    dist[0] = 0;
    set<pair<ll, int>> q;
    q.insert({0, 0});
    while(!q.empty()){
        auto top = q.begin();
        ll currDist = top->first;
        int currChild = top->second;
        q.erase(top);

        for (auto child: g[currChild]){
            int v = child.first;
            int dst = child.second;
            if (dist[v] > dist[currChild] + dst){
                if (q.find({dist[v], v}) != q.end()) {
                    q.erase(q.find({dist[v], v}));
                }
                dist[v] = dist[currChild] + dst;
                q.insert({dist[v], v});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dist[i] << " ";
    }
    return 0;
}