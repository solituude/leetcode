#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

struct Monster{
    int id, attack, def, prev, next;
    Monster(int id, int attack, int def, int prev, int next): id(id), attack(attack), def(def), prev(prev), next(next){}
};

void solve(){
    int n, attack, def, hit;
    cin >> n;
    vector<Monster*> monsters;
    set<int> alive;
    for (int i = 0; i < n; i++) {
        cin >> attack;
        monsters.push_back(new Monster(i, attack, 0, i - 1, i + 1));
    }
    monsters[n - 1]->next = -1;
    for (int i = 0; i < n; i++) {
        cin >> def;
        monsters[i]->def = def;
        alive.insert(i);
    }

    for (int round = 0; round < n; round++) {
        unordered_set<int> died;
        int countDied = 0;
        for (auto a: alive) {
            hit = 0;
            int prevInd = monsters[a]->prev;
            int nextInd = monsters[a]->next;
            if (prevInd >= 0) {
                hit += monsters[prevInd]->attack;
            }
            if (nextInd >= 0) {
                hit += monsters[nextInd]->attack;
            }
            if (hit > monsters[a]->def) {
                countDied++;
                died.insert(a);
            }
        }
        cout << died.size() << " ";
        alive = set<int>();

        for (int d: died) {
            int prevInd = monsters[d]->prev;
            int nextInd = monsters[d]->next;
            if (prevInd >= 0) {
                monsters[prevInd]->next = monsters[d]->next;
                if (died.find(prevInd) == died.end()){
                    alive.insert(prevInd);
                }
            }
            if (nextInd >= 0) {
                monsters[nextInd]->prev = prevInd;
                if (died.find(nextInd) == died.end()){
                    alive.insert(nextInd);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();

    return 0;
}