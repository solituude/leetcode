#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point{
    int parentInd, currInd, len;
    Point(int parentInd, int currInd, int len): parentInd(parentInd), currInd(currInd), len(len){}
};

int main() {
    int n, maxLen = 0, indMaxLen;
    cin >> n;
    vector<int> arr(n);
    vector<int> ans;
    vector<Point*> maxLenArray;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        int currNum = arr[i];
        int j = (int)maxLenArray.size() - 1;
        int bestInd = -1;
        int bestLen;
        if (j < 0) {
            bestLen = -1;
        } else {
            bestLen = 0;
        }

        while (j >= 0) {
            if (arr[j] < arr[i] && maxLenArray[j]->len > bestLen) {
                bestLen = maxLenArray[j]->len;
                bestInd = j;
            }
            j--;
        }


        if (bestInd >= 0) {
            maxLenArray.push_back(new Point(bestInd, i, bestLen + 1));
        } else {
            maxLenArray.push_back(new Point(bestInd, i, 1));
        }
        if (maxLenArray[i]->len > maxLen) {
            maxLen = maxLenArray[i]->len;
            indMaxLen = i;
        }
    }

    cout << maxLen << '\n';
    for (int i = 0; i < maxLen; i++) {
        ans.push_back(arr[maxLenArray[indMaxLen]->currInd]);
        indMaxLen = maxLenArray[indMaxLen]->parentInd;
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < maxLen; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}

//5
//-10 -9 10 8 9

//5
//-10 1 -2 4 -5