#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void solve(int n) {
    int lastInd = -1;
    int sqrtN = ::ceil(::sqrt(n));

    vector<int> primeParts(sqrtN + 1, 0);
    for (int i = 2; i <= sqrtN; i++) {
        while (n % i == 0) {
            n /= i;
            primeParts[i]++;
            lastInd = i;
        }
    }
    for (int i = 2; i <= lastInd; i++) {
        if (primeParts[i] > 1) {
            cout << i << "^" << primeParts[i];
            if (i != lastInd) {
                cout << "*";
            }
        }
        else if (primeParts[i] == 1) {
            cout << i;
            if (i != lastInd) {
                cout << "*";
            }
        }
    }
    if (n > 2 && lastInd > 0) {
        cout << "*" << n;
    } else if (n > 2) {
        cout << n;
    }
}

int main() {
    int n;
    cin >> n;
    solve(n);
//    for (int i = 100; i < 200; i++) {
//        cout << i << " ";
//        solve(i);
//        cout << endl;
//    }


    return 0;
}