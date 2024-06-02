#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

int bfs(vector<vector<int> > &matrix, int& indexA, int& indexB, queue<int> &q, vector<bool> &visited) {
    q.push(indexA);
    vector<int> destination(matrix.size(), -1);
    destination[indexA] = 0;
    visited[indexA] = true;
    while(!q.empty()) {
        int currV = q.front();
        q.pop();
        for (int i = 0; i < matrix[currV].size(); i++){
            if (!visited[matrix[currV][i]]) {
                destination[matrix[currV][i]] = destination[currV] + 1;
                visited[matrix[currV][i]] = true;
                q.push(matrix[currV][i]);
            }
        }
    }
    return destination[indexB];
}

int main() {
    int n, countSubstance = 0, indexA, indexB;
    string a, b, arrow;
    unordered_map<string, int> dict;
    vector<vector<int> > matrix;
    queue<int> q;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a >> arrow >> b;
        auto searchA = dict.find(a);
        if (searchA == dict.end()) {
            dict[a] = countSubstance;
            countSubstance++;
        }
        if (matrix.size() < dict[a] + 1) {
            matrix.push_back(vector<int>());
        }
        auto searchB = dict.find(b);
        if (searchB == dict.end()) {
            dict[b] = countSubstance;
            countSubstance++;
        }
        if (matrix.size() < dict[b] + 1) {
            matrix.push_back(vector<int>());
        }
        matrix[dict[a]].push_back(dict[b]);
    }

    vector<bool> visited(matrix.size(), false);

    cin >> a >> b;
    if (n > 0 && dict.find(a) != dict.end() && dict.find(b) != dict.end()) {
        indexA = dict[a];
        indexB = dict[b];
        int res = bfs(matrix, indexA, indexB, q, visited);
        cout << res;
    } else {
        cout << -1;
    }

    return 0;
}

//
//5
//Aqua -> AquaVita
//        AquaVita -> PhilosopherStone
//        AquaVita -> Argentum
//        Argentum -> Aurum
//        AquaVita -> Aurum
//        Aqua
//Aqua

//7
//a -> d
//        a -> e
//        b -> a
//        b -> c
//        c -> e
//        e -> b
//        d -> b