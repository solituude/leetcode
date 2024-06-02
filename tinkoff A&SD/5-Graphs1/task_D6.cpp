#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Step{
    int prevX, prevY, stepNumber;
    Step(): prevX(-1), prevY(-1), stepNumber(-1) {}
    Step(int newPrevX, int newPrevY, int newStepNumber): prevX(newPrevX), prevY(newPrevY), stepNumber(newStepNumber){}
};

bool addNewStepsOnBoard(int n, vector<vector<Step> > &board, int x1, int y1, int x2, int y2, int stepNumber,
                        vector<pair<int, int> > &nLayer) {
    if (x1 - 1 >= 0 && y1 - 2 >= 0 && board[y1 - 2][x1 - 1].stepNumber == -1) {
        board[y1 - 2][x1 - 1] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 - 2, x1 - 1));
        if (y1 - 2 == y2 && x1 - 1 == x2) {
            return true;
        }
    }

    if (x1 + 1 < n && y1 - 2 >= 0 && board[y1 - 2][x1 + 1].stepNumber == -1) {
        board[y1 - 2][x1 + 1] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 - 2, x1 + 1));
        if (y1 - 2 == y2 && x1 + 1 == x2) {
            return true;
        }
    }

    if (x1 + 2 < n && y1 - 1 >= 0 && board[y1 - 1][x1 + 2].stepNumber == -1) {
        board[y1 - 1][x1 + 2] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 - 1, x1 + 2));
        if (y1 - 1 == y2 && x1 + 2 == x2) {
            return true;
        }
    }

    if (x1 + 2 < n && y1 + 1 < n && board[y1 + 1][x1 + 2].stepNumber == -1) {
        board[y1 + 1][x1 + 2] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 + 1, x1 + 2));
        if (y1 + 1 == y2 && x1 + 2 == x2) {
            return true;
        }
    }

    if (x1 + 1 < n && y1 + 2 < n && board[y1 + 2][x1 + 1].stepNumber == -1) {
        board[y1 + 2][x1 + 1] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 + 2, x1 + 1));
        if (y1 + 2 == y2 && x1 + 1 == x2) {
            return true;
        }
    }
    if (x1 - 1 >= 0 && y1 + 2 < n && board[y1 + 2][x1 - 1].stepNumber == -1) {
        board[y1 + 2][x1 - 1] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 + 2, x1 - 1));
        if (y1 + 2 == y2 && x1 - 1 == x2) {
            return true;
        }
    }
    if (x1 - 2 >= 0 && y1 + 1 < n && board[y1 + 1][x1 - 2].stepNumber == -1) {
        board[y1 + 1][x1 - 2] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 + 1, x1 - 2));
        if (y1 + 1 == y2 && x1 - 2 == x2) {
            return true;
        }
    }
    if (x1 - 2 >= 0 && y1 - 1 >= 0 && board[y1 - 1][x1 - 2].stepNumber == -1) {
        board[y1 - 1][x1 - 2] = Step(x1, y1, stepNumber);
        nLayer.push_back(make_pair(y1 - 1, x1 - 2));
        if (y1 - 1 == y2 && x1 - 2 == x2) {
            return true;
        }
    }
    return false;
}

void getWay(int x, int y, vector<vector<Step> > &board, vector<pair<int, int> > &way) {
    while (x >= 0) {
        int copyX = x, copyY = y;
        way.push_back(make_pair(y, x));
        y = board[copyY][copyX].prevY;
        x = board[copyY][copyX].prevX;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int x1, y1, x2, y2, n, stepNumber = 0, isFind = false;
    cin >> n;
    vector<vector<Step> > board(n, vector<Step>(n));
    vector<vector<pair<int, int> > > layers(1);
    vector<pair<int, int> > nLayer;
    vector<pair<int, int> > way;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;
    layers[0].push_back(make_pair(y1, x1));
    board[y1][x1] = Step(-1, -1, 0);
    while (!isFind) {
        int i = 0;
        int nextStep = stepNumber + 1;
        while (i < layers[stepNumber].size() && !isFind) {
            isFind = addNewStepsOnBoard(n, board, layers[stepNumber][i].second, layers[stepNumber][i].first, x2, y2, nextStep, nLayer);
            i++;
        }
        layers.push_back(nLayer);
        nLayer = vector<pair<int, int> >();
        stepNumber++;
    }
    getWay(x2, y2, board, way);
    reverse(way.begin(), way.end());

    cout << way.size() - 1 << '\n';
    for (int i = 0; i < way.size(); i++) {
        cout << way[i].second + 1 << " " << way[i].first + 1 << '\n';
    }

    return 0;
}