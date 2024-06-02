#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string str;
    cin >> str;
    string p = "";
    int n = (int)str.size();
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int shift = 0; shift < n; shift++) {
        for (int i = 0; i < n; i++) {
            int j = i + shift;
            if (i == j) matrix[i][j] = 1;
            else if (i > j) matrix[i][j] = 0;
            else if (j < n && i + 1 < n && str[i] == str[j])
                matrix[i][j] = matrix[i + 1][j - 1] + 2;
            else if (j < n && i + 1 < n && str[i] != str[j])
                matrix[i][j] = max(matrix[i][j - 1], matrix[i + 1][j]);
        }
    }

    int i = 0;
    int j = n - 1;
    while (i < n && j >= 0 && matrix[i][j] > 0) {
        if (str[i] == str[j]) {
            p += str[i];
            i++;
            j--;
        } else if (matrix[i + 1][j] > matrix[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }
    cout << matrix[0][n - 1] << '\n';
    cout << p;
    i = (int)p.size() - 1 - matrix[0][n - 1] % 2 ;
    for (; i >= 0; i--) {
        cout << p[i];
    }

    return 0;
}
