#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

struct Coordinate {
    ll x, y;
    int i;
};

void addFew(int i, ll v, vector<ll> &tree) {
    for(; i < (int)tree.size(); i = i | (i + 1)){
        tree[i] += v;
    }
}
void addRange(int first, int second, ll v, vector<ll>&tree) {
    addFew(first, v, tree);
    addFew(second, -v, tree);
}


ll get(int i, vector<ll> &tree) {
    ll ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

bool comparator(Coordinate left, Coordinate right){
    return left.x < right.x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll wh;
    int n;
    cin >> wh >> wh >> n;
    vector<Coordinate> t(n);
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        double newX, newY;
        cin >> newX >> newY;
        t[i] = Coordinate{(ll)(newX * 2), (ll) (newY * 2), i};
    }
    vector<ll> yy(n);
    for (int i = 0; i < n; i++) {
        yy[i] = t[i].y;
    }
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    sort(t.begin(), t.end(), comparator);
    vector<ll> xx(yy.size(), 0);
    for (Coordinate node: t) {
        auto iter = lower_bound(yy.begin(), yy.end(), node.y);
        assert(iter != yy.end() && *iter == node.y);
        int i = (int)(iter - yy.begin());
        ll segm = node.x - get(i, xx);
        assert(segm > 0);
        assert(arr[node.i] == 0);
        arr[node.i] = segm;
        iter = upper_bound(yy.begin(), yy.end(), node.y - segm);
        int start = (int) (iter - yy.begin());
        iter = upper_bound(yy.begin(), yy.end(), node.y + segm);
        int finish = (int)(iter - yy.begin());
        addRange(start, finish, segm * 2, xx);

    }
    for (ll elem: arr) {
        assert(elem != 0);
        cout << elem << ' ';
    }
    return 0;
}
