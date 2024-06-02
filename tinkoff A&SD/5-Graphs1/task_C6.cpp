#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int> > &matrix, vector<bool> &exist, int currIndex) {
    for (int i = 0; i < matrix[currIndex].size(); i++) {
        if (!exist[matrix[currIndex][i]]) {
            cout << "NO";
            exit(0);
        }
    }
    exist[currIndex] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m;
    vector<vector<int> > matrix(n);
    vector<bool> exist(n, true);
    vector<int> arr;


    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--; b--;
        matrix[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
        cin >> a; a--;
        arr.push_back(a);
    }
    for (int i = 0; i < n; i++) {
        dfs(matrix, exist, arr[i]);
    }
    cout << "YES";

    return 0;
}

//5 6
//1 2
//1 3
//3 2
//2 5
//4 5
//3 4
//1 3 4 2 5


//9 7
//1 5
//1 8
//5 8
//5 9
//3 6
//3 7
//6 9
//2 4 1 3 5 6 7 8 9
// да
// 9 8 6 7 5 4 2 3 1
// нет


//3 2
//1 2
//2 3
//1 2 3
//YES