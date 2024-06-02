#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Node {
    int currInd, parentInd, maxSum;
    Node(int newCurrInd, int newParentInd, int newMaxSum): currInd(newCurrInd), parentInd(newParentInd), maxSum(newMaxSum){}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k, bottomDequeue, curr, currI, parentI, sum;
    cin >> n >> k;
    vector<int> initialArray, wayArray;
    vector<Node*> array;
    deque<pair<int, int> > deq;
    array.push_back(new Node(0, -1, 0));
    deq.push_back(make_pair(0, 0));
    initialArray.push_back(0);
    for (int i = 0; i < n - 2; i++) {
        cin >> curr;
        initialArray.push_back(curr);
    }
    initialArray.push_back(0);

    for (int i = 1; i < initialArray.size(); i++) {
        bottomDequeue = i - k - 1;
        if (bottomDequeue == deq.begin()->first) {
            deq.pop_front();
        }
        currI = i;
        sum = initialArray[currI] + deq.begin()->second;
        parentI = deq.begin()->first;
        array.push_back(new Node(currI, parentI, sum));

        while (!deq.empty() && sum > deq.back().second) {
            deq.pop_back();
        }
        deq.push_back(make_pair(currI, sum));
    }

    parentI = array[n - 1]->parentInd;
    wayArray.push_back(n - 1);
    while (parentI != -1) {
        wayArray.push_back(parentI);
        parentI = array[parentI]->parentInd;
    }
    reverse(wayArray.begin(), wayArray.end());
    cout << array[n - 1]->maxSum << '\n';
    cout << wayArray.size() - 1 << '\n';
    for (int i = 0; i < wayArray.size(); i++) {
        cout << wayArray[i] + 1 << " ";
    }
    return 0;
}

//8 3
//1 -1 1 -1 1 -1

//4 2
//1000 -1000

//12 5
//-1 -2 -3 -4 -5 -6 -7 -8 -9 -10

