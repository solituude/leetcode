#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void getConnectivity(int& count, vector<vector<int> >& matrix, int index, vector<bool>& visited, vector<int>& connectArr) {
    for (int i = 0; i < matrix[index].size(); i++) {
        if (!matrix[index].empty() && !visited[matrix[index][i]]) {
            count++;
            connectArr.push_back(matrix[index][i]);
            visited[matrix[index][i]] = true;
            getConnectivity(count, matrix, matrix[index][i], visited, connectArr);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, b, count = 0;
    cin >> n >> m;
    vector<vector<int> > graph(n);
    vector<bool> visited(n, false);
    vector<int> connectArr;
    vector<vector<int> > ans;

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (count > 0) {
                ans.push_back(connectArr);
            }

            count = 1;
            connectArr = vector<int>();
            connectArr.push_back(i);
            visited[i] = true;

            getConnectivity(count, graph, i, visited, connectArr);
        }
    }
    ans.push_back(connectArr);

    cout << ans.size();
    for (int i = 0; i < ans.size(); i++) {
        cout << '\n' << ans[i].size() << '\n';
        sort(ans[i].begin(), ans[i].end());
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] + 1 << " ";
        }
    }

    return 0;
}


//6 7
//1 3
//2 1
//3 2
//2 6
//3 4
//5 4
//5 3

//10 0

//4 3
//1 2
//3 2
//3 4

//11 10
//1 2
//2 5
//6 2
//7 3
//4 9
//8 4
//11 10
//10 4
//3 1
//1 4