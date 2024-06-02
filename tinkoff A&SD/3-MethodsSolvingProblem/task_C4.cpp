#include <iostream>

using namespace std;

int main() {
    int n, k, countAlreadyStand;
    cin >> n >> k;
    int cows[n];
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    int leftCow = 0;
    int rightCow = cows[n - 1] - cows[0] + 1;
    while (rightCow - leftCow > 1) {
        int mid = (rightCow + leftCow) / 2;
        countAlreadyStand = 1;
        int lastCow = cows[0];
        for (int i = 0; i < n; i++) {
            if (cows[i] - lastCow >= mid) {
                countAlreadyStand++;
                lastCow = cows[i];
            }
        }
        if (countAlreadyStand >= k) {
            leftCow = mid;
        } else {
            rightCow = mid;
        }
    }
    cout << leftCow << '\n';
    return 0;
}