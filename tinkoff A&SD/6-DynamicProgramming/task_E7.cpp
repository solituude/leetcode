#include <iostream>
#include <vector>
#include <string>

using namespace std;
int INF = 1e9;

int getMin(string &s1, string &s2, int i, int j, int Xinsert, int Xdelete, int Xchange, int Xtransposition = INF) {
    int currMin = 1e9;
    Xinsert++; Xdelete++; i--; j--;
    if (s1[i] != s2[j]) Xchange++;

    if (j - 1 >= 0 && i - 1 >= 0 && s1[i] == s2[j - 1] && s1[i - 1] == s2[j]) Xtransposition++;
    else Xtransposition += INF;

    if (Xinsert < currMin) currMin = Xinsert;
    if (Xdelete < currMin) currMin = Xdelete;
    if (Xchange < currMin) currMin = Xchange;
    if (Xtransposition < currMin) currMin = Xtransposition;

    return currMin;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = (int)s1.size() + 1;
    int m = (int)s2.size() + 1;

    vector<vector<int> > matrix(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        matrix[i][0] = i;
    }
    for (int j = 0; j < m; j++) {
        matrix[0][j] = j;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (i < 2 || j < 2) {
                matrix[i][j] = getMin(s1, s2, i, j, matrix[i][j - 1],
                                      matrix[i - 1][j], matrix[i - 1][j - 1]);
            } else {
                matrix[i][j] = getMin(s1, s2, i, j, matrix[i][j - 1], matrix[i - 1][j],
                                      matrix[i - 1][j - 1], matrix[i - 2][j - 2]);
            }
        }
    }
    cout << matrix[n - 1][m - 1];

}

//meilenstein
//levenshtein

//altruism
//plasma

//abcdefg
//abcdefg