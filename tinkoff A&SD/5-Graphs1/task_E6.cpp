#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;
const int INF = 1e9;

void bfs(int start, int n, vector<int> &destination, vector<int> &parent) {
    queue<int> q;
    destination[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int j = 0; j <= 9; ++j) {
            int to = (v * 10 + j) % n;
            if (destination[to] > destination[v] + j || to == 0 && destination[0] == 0) {
                destination[to] = destination[v] + j;
                parent[to] = v;
                q.push(to);
            }
        }
    }
}

int main() {
    int k;
    cin >> k;
    vector<int> destination(k, INF), parent(k, -1);
    bfs(0, k, destination, parent);
    cout << destination[0];

    return 0;
}