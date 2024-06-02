#include <iostream>

using namespace std;

int main() {
    int n;
    long long k, left, right, mid, countLessMid;
    cin >> n >> k;
    left = 1;
    right = k + 1;
    while (right > left) {
        countLessMid = 0;
        mid = (right + left) / 2;
        for (int i = 1; i <= n; i++) {
            if ((mid - 1) / i < n) {
                countLessMid += (mid - 1) / i;
            } else {
                countLessMid += n;
            }
        }
        if (countLessMid >= k) {
            right = mid;
        } else  {
            left = mid + 1;
        }
    }

    cout << left - 1 << '\n';
    return 0;
}
