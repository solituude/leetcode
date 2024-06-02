#include <iostream>
#include <string>
#include <vector>


using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string p, t;
    vector<int> indexes;
    cin >> p >> t;

    if ((int)t.size() - (int)p.size() >= 0) {
        for (int i = 0; i < t.size() - p.size() + 1; i++) {
            int countEqual = 0;
            for (int j = 0; j < p.size(); j++){
                if(t[i + j] == p[j]) {
                    countEqual++;
                }
            }
            if (countEqual >= p.size() - 1) {
                indexes.push_back(i + 1);
            }
        }
    }

    cout << indexes.size() << '\n';
    for (int i = 0; i < indexes.size(); i++) {
        cout << indexes[i] << " ";
    }

    return 0;
}
