#include <iostream>
#include <array>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, y1, y2, x1, x2;
    cin >> n >> m >> k;
    int matrix[n][m];
    long long prefixSumMatrix[n + 1][m + 1];
    for (int i = 0; i < n + 1; i++) {
        prefixSumMatrix[i][0] = 0;
    }
    for (int i = 0; i < m + 1; i++) {
        prefixSumMatrix[0][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
            prefixSumMatrix[i + 1][j + 1] = matrix[i][j] + prefixSumMatrix[i][j + 1] + prefixSumMatrix[i + 1][j] - prefixSumMatrix[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        cin >> y1 >> x1 >> y2 >> x2;
        cout << prefixSumMatrix[y2][x2]- prefixSumMatrix[y2][x1-1] - prefixSumMatrix[y1-1][x2] + prefixSumMatrix[y1-1][x1-1] << '\n';
    }

    return 0;
}

