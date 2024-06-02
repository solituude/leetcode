#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, price;
    cin >> n;
    vector<int> ladder(n);
    for (int i = 0; i < n; i++) {
        cin >> price;
        if (i < 2) {
            ladder[i] = price;
        } else {
            ladder[i] = min(ladder[i - 1], ladder[i - 2]) + price;
        }
    }
    cout << ladder[n - 1];

    return 0;
}