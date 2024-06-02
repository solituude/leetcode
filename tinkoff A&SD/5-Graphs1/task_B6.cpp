#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int> > &matrix, vector<bool> &visited, int currIndex) {
    if (visited[currIndex]) {
        cout << 1;
        exit(0);
    }
    visited[currIndex] = true;
    for(int i = 0; i < matrix[currIndex].size(); i++) {
        dfs(matrix, visited, matrix[currIndex][i]);
    }
    visited[currIndex] = false;
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    vector<vector<int> > matrix(n);
    vector<bool> visited(n);

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--; b--;
        matrix[a].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(matrix, visited, i);
        }
    }
    cout << 0;

    return 0;

}

//7 9
//1 2
//2 3
//3 4
//7 3
//4 7
//5 3
//7 5
//7 6
//6 2
//1


//5 6
//1 2
//1 3
//3 2
//2 5
//4 5
//3 4
//0


//8 8
//1 2
//2 4
//5 2
//7 8
//8 5
//3 6
//3 7
//1 3
//0

//8 9
//1 2
//2 4
//5 2
//7 8
//8 5
//3 6
//3 7
//1 3
//2 3
//1