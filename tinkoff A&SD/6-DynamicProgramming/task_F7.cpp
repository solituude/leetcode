#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int INF = 1e9;

struct Ceil {
    pair<int, int> rightZero, bottomZero;
    int squareSize;
    Ceil(pair<int, int> newRightZero, pair<int, int> newBottomZero, int newSquareSize): rightZero(newRightZero),
    bottomZero(newBottomZero), squareSize(newSquareSize){};
    Ceil(): rightZero(make_pair(-1, -1)), bottomZero(make_pair(-1, -1)), squareSize(0){};
};

int getMin(vector<vector<Ceil> > &matrix, int i, int j, int n, int m) {
    int currMin = INF;
    if (i + 1 < n) currMin = min(currMin, matrix[i + 1][j].squareSize);
    else currMin = 0;
    if (j + 1 < m) currMin = min(currMin, matrix[i][j + 1].squareSize);
    else currMin = 0;
    if (i + 1 < n && j + 1 < m) currMin = min(currMin, matrix[i + 1][j + 1].squareSize);
    else currMin = 0;

    return currMin;
}

int main() {
    int n, m, squareSize, max = 0;
    pair<int, int> rightZero, bottomZero, coordMax;
    cin >> n >> m;
    vector<vector<int> > initialArray(n, vector<int>(m));
    vector<vector<Ceil> > matrix(n, vector<Ceil>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> initialArray[i][j];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (initialArray[i][j] == 0) {
                rightZero = make_pair(i , j);
                bottomZero = make_pair(i , j);
                squareSize = 0;
            } else {
                if (i + 1 == n) bottomZero = make_pair(i + 1, j);
                else bottomZero = matrix[i + 1][j].bottomZero;

                if (j + 1 == m) rightZero = make_pair(i, j + 1);
                else rightZero = matrix[i][j + 1].rightZero;
                squareSize = getMin(matrix, i, j, n, m) + 1;
            }
            matrix[i][j] = Ceil(rightZero, bottomZero, squareSize);
            if (squareSize > max) {
                max = squareSize;
                coordMax = make_pair(i , j);
            }
        }
    }
    cout << max << '\n' << coordMax.first + 1 << " " << coordMax.second + 1;
    return 0;
}

//3 5
//1 1 0 0 0
//1 1 1 1 1
//0 0 0 1 1

//1 1
//1

//4 8
//1 1 1 1 1 1 1 1
//0 0 1 1 1 1 0 0
//1 0 0 1 1 1 0 1
//1 0 1 0 0 0 0 1

//1 5
//0 1 1 1 0

//3 3
//1 1 1
//1 1 1
//1 1 0

//5 6
//1 1 1 1 1 1
//1 0 0 0 0 1
//1 0 0 1 0 1
//1 0 0 0 0 1
//1 1 1 1 1 1