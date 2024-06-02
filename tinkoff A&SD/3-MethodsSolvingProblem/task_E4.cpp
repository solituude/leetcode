#include <iostream>

using namespace std;

//3 2
//150 500 10

//3 2
//1 12 2

//4 3
//1 1 1 1

//10 4
//1 3 2 4 10 8 4 2 5 3

//5 2
//1 1 1 543 5342

//1 1
//6

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n, k, left, right, mid, maxSum, maxElem = 0;
    cin >> n >> k;
    int arr[n], countSection, indexFirstElement;
    long long prefixSum[n + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        prefixSum[i + 1] = prefixSum[i] + arr[i];
        if (arr[i] > maxElem) {
            maxElem = arr[i];
        }
//        maxElem = max(arr[i], maxElem);
//        cout << prefixSum[i + 1] << " ";
    }
//    cout << endl;
    left = maxElem - 1;
    right = prefixSum[n];
    maxSum = prefixSum[n];
    while (right - left > 1) {
        long long localMaxSum = 0;
        mid = (left + right) / 2;
        countSection = 0;
        indexFirstElement = 0;

        for (int i = 0; i < n; i++) {
            if (prefixSum[i + 1] - prefixSum[indexFirstElement] >= mid) {
                countSection++;
                if (prefixSum[i] - prefixSum[indexFirstElement] > localMaxSum) {
                    localMaxSum = prefixSum[i] - prefixSum[indexFirstElement];
                }
                indexFirstElement = i;
            }
        }

        if (indexFirstElement < n) {
            countSection++;
            if (prefixSum[n] - prefixSum[indexFirstElement] > localMaxSum) {
                localMaxSum = prefixSum[n] - prefixSum[indexFirstElement];
            }
        }

        if (countSection <= k) {
            right = mid;
        } else {
            left = mid;
        }

//        cout << endl << left << " " << right << endl;
//        cout << mid << " " << localMaxSum << " " << countSection << endl;
        if (countSection <= k) {
            if (localMaxSum < maxSum) {
                maxSum = localMaxSum;
            }
        }
    }
//    cout << endl << right << endl;
    cout << maxSum;

    return 0;
}
