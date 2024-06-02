#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

struct Road{
    int to, time, maxCountCups;
    Road(int to, int time, int maxCountCups): to(to), time(time), maxCountCups(maxCountCups){}
};

int dijkstra(int cups, vector<vector<Road*>> &g) {
    vector<bool> visited(g.size(), false);
    set<pair<int, int>> q;
    q.insert({0, 0});
    while (!q.empty()){
        auto node = q.begin();
        int nodeTime = node->first;
        int nodeFrom = node->second;
        visited[nodeFrom] = true;
        q.erase(node);
        if (nodeTime > 1440) {
            return 0;
        }
        if (nodeFrom == g.size() - 1) {
            return nodeTime;
        }
        for (auto road: g[nodeFrom]){
            if (road->maxCountCups >= cups && !visited[road->to]) {
                if (nodeTime + road->time <= 1440) {
                    q.insert({nodeTime + road->time, road->to});
                }
            }
        }

    }
    return 0;
}

void binSearch(vector<int> &countCupArray, vector<vector<Road*>> &g) {
    int left = 0;
    int right = (int)countCupArray.size() - 1;
    int maxCountCups = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int ans = dijkstra(countCupArray[mid], g);
        if (ans == 0) {
            right = mid - 1;
        } else {
            maxCountCups = max(maxCountCups, countCupArray[mid]);
            left = mid + 1;
        }
    }
    cout << maxCountCups;
}

int main() {
    int n, m, from, to, time, weight;
    cin >> n >> m;
    vector<vector<Road*>> g(n);
    unordered_set<int> countCupSet;
    vector<int> countCupArray;

    if (n == 1) {
        cout << 10000000;
        return 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> from >> to >> time >> weight;
        if ((int)(weight - 3e6) / 100 <= 0){
            continue;
        }
        g[from - 1].push_back(new Road(to - 1, time, (int)(weight - 3e6) / 100));
        g[to - 1].push_back(new Road(from - 1, time, (int)(weight - 3e6) / 100));
        if (countCupSet.find((int)(weight - 3e6) / 100) == countCupSet.end()){
            countCupSet.insert((int)(weight - 3e6) / 100);
            countCupArray.push_back((int)(weight - 3e6) / 100);
        }
    }
    sort(countCupArray.begin(), countCupArray.end());
    binSearch(countCupArray, g);
    return 0;
}