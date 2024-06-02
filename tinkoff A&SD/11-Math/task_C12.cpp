#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<bool> sieve (n, true);
    for (int i = 2; i <= n; i++) {
        if (sieve[i]) {
            for (int j = i * 2; j <= n; j += i){
                sieve[j] = false;
            }
        }
    }
    int i = 2;
    while (!(sieve[i] && sieve[n - i])) {
        i++;
    }
    cout << i << " " << n - i;

    return 0;
}