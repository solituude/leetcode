#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m, currX, currY;
    pair<int, int> curr;
    cin >> n >> m;
    vector<vector<int> > dask(n, vector<int>(m, 0));
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        curr = q.front();
        currX = curr.second;
        currY = curr.first;
        q.pop();
        if (currX + 2 < m && currY - 1 >= 0) {
            dask[currY - 1][currX + 2]++;
            q.push(make_pair(currY - 1, currX + 2));
        }
        if (currX + 2 < m && currY + 1 < n) {
            dask[currY + 1][currX + 2]++;
            q.push(make_pair(currY + 1, currX + 2));
        }
        if (currX + 1 < m && currY + 2 < n) {
            dask[currY + 2][currX + 1]++;
            q.push(make_pair(currY + 2, currX + 1));
        }
        if (currX - 1 >= 0 && currY + 2 < n) {
            dask[currY + 2][currX - 1]++;
            q.push(make_pair(currY + 2, currX - 1));
        }
    }
    cout << dask[n - 1][m - 1];
    return 0;
}