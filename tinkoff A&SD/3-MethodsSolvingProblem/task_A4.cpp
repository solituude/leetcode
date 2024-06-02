#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, number, q, l, r;
    vector<int> array;
    vector<long long>prefixSum;
    vector<int>prefixXor;
    prefixSum.push_back(0);
    prefixXor.push_back(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> number;
        array.push_back(number);
        prefixSum.push_back(prefixSum[i - 1] + number);
        prefixXor.push_back(prefixXor[i - 1] ^ number);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q >> l >> r;
        if (q == 1) {
            cout << prefixSum[r] - prefixSum[l - 1] << '\n';
        } else if (q == 2) {
            int res = prefixXor[r] ^ prefixXor[l - 1];
            cout << res << '\n';
        }
    }
    return 0;
}