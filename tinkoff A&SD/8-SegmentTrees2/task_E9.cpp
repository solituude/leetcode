#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>

typedef long long ll;
using namespace std;

struct segmentTree {
    ll n;
    vector<ll> segments;
    vector<ll> segmentsLen;
    vector<ll> add;

    segmentTree(vector<ll> &intervals) {
        n = (ll)intervals.size();
        segments.resize(4 * n, 0);
        segmentsLen.resize(4 * n, 0);
        add.resize(4 * n, 0);
        build(1, 0, n, intervals);
    }

    void build(ll node, ll left, ll right, vector<ll> &intervals) {
        if (left + 1 == right) {
            segmentsLen[node] = intervals[left];
        } else {
            ll m = (left + right) / 2;
            build(2 * node, left, m, intervals);
            build(2 * node + 1, m, right, intervals);
            segmentsLen[node] = segmentsLen[2 * node] + segmentsLen[2 * node + 1];
        }
    }

    void propagate(ll node) {
        add[2 * node] += add[node];
        segments[2 * node] += add[node];
        add[2 * node + 1] += add[node];
        segments[2 * node + 1] += add[node];
        add[node] = 0;
    }

    void update(ll node, ll left, ll right, ll tl, ll tr, ll val) {
        if (right <= tl || tr <= left) {
            return;
        }
        if (tl <= left && right <= tr) {
            add[node] += val;
            segments[node] += val;
            return;
        }

        propagate(node);
        ll mid = (left + right) / 2;
        update(2 * node, left, mid, tl, tr, val);
        update(2 * node + 1, mid, right, tl, tr, val);

        if (segments[2 * node] == segments[2 * node + 1]) {
            segments[node] = segments[2 * node];
            segmentsLen[node] = segmentsLen[2 * node] + segmentsLen[2 * node + 1];
        } else if (segments[2 * node] < segments[2 * node + 1]) {
            segments[node] = segments[2 * node];
            segmentsLen[node] = segmentsLen[2 * node];
        } else {
            segments[node] = segments[2 * node + 1];
            segmentsLen[node] = segmentsLen[2 * node + 1];
        }
    }

    void update(ll tl, ll tr, ll val) {
        update(1, 0, n, tl, tr, val);
    }

    ll query() {
        return (segments[1] ? 0 : segmentsLen[1]);
    }
};

struct Node {
    ll x;
    ll y1;
    ll y2;
    ll type;

    bool operator<(const Node &n) const {
        return make_pair(x, -type) < make_pair(n.x, -n.type);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    vector<Node> query(2 * n);
    set<ll> yy;
    ll x1, y1, x2, y2;
    for (ll i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2 || y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        x2++;
        y2++;
        yy.insert(y1);
        yy.insert(y2);
        query[2 * i] = {x1, y1, y2, 1};
        query[2 * i + 1] = {x2, y1, y2, -1};
    }
    sort(query.begin(), query.end());

    vector<ll> sortYY;
    sortYY.reserve(yy.size());
    for (ll i: yy) {
        sortYY.push_back(i);
    }

    map<ll, ll> coordinates;
    for (ll i = 0; i < sortYY.size(); ++i) {
        coordinates[sortYY[i]] = i;
    }

    vector<ll> counts(sortYY.size() - 1);
    for (ll i = 1; i < sortYY.size(); ++i) {
        counts[i - 1] = sortYY[i] - sortYY[i - 1];
    }
    ll sum_dist = accumulate(counts.begin(), counts.end(), 0);

    segmentTree t(counts);

    ll sum = 0;
    ll prev = query[0].x;
    for (Node currNode: query) {
        sum += (sum_dist - t.query()) * (currNode.x - prev);
        t.update(coordinates[currNode.y1], coordinates[currNode.y2], currNode.type);
        prev = currNode.x;
    }
    cout << sum;

    return 0;
}