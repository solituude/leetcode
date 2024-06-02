#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

vector<int> dijkstra(int start, vector<vector<pair<int, int> > > &matrix, int n) {
    vector<bool> visited(n, false);
    vector<int> destination(n, INF);
    destination[start] = 0;
    for (int i = 0; i < n; i++) {
        int currV = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (currV == -1 || destination[j] < destination[currV])) {
                currV = j;
            }
        }
        if (destination[currV] == INF) {
            break;
        }
        visited[currV] = true;
        for (int j = 0; j < matrix[currV].size(); j++) {
            int nextV = matrix[currV][j].first;
            int lenWay = matrix[currV][j].second;
            if (destination[currV] + lenWay < destination[nextV]) {
                destination[nextV] = destination[currV] + lenWay;
            }
        }
    }
    return destination;
}

int main() {
    int n, m, u, v, w, city,  minDestination = INF;
    cin >> n >> m;
    vector<vector<pair<int, int> > > matrix(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        u--; v--;
        matrix[u].push_back(make_pair(v, w));
        matrix[v].push_back(make_pair(u, w));
    }

    for (int i = 0; i < n; i++) {
        vector<int> currD = dijkstra(i, matrix, n);
        int sum = 0, currMaxDestination = -1;
        for (int j = 0; j < n; j++) {
            sum += currD[j];
            if (currD[j] > currMaxDestination) {
                currMaxDestination = currD[j];
            }
        }
        if (currMaxDestination < minDestination) {
            city = i + 1;
            minDestination = currMaxDestination;
        }
//        cout << i << " " << currMaxDestination << endl;
    }

    cout << city;

    return 0;
}


//6 8
//1 3 1
//1 6 2
//3 4 1
//6 4 6
//6 2 1
//6 5 4
//5 2 2
//2 4 4
