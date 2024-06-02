#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int count;
    int segments;
    int set;
    int left, right;
    bool up;

    Node() {
        count = 1; segments = 1; set = 0; up = false; left = 0; right = 0;
    }
    Node(int count, int segments, int s, int left, int right, bool u):
    count(count), segments(segments), set(s), left(left), right(right), up(u) {}
};

vector<Node> t;


void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = Node(0, 0, 0, tl, tr, false);
    } else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        t[v] = Node(0, 0, 0, tl, tr, false);
    }
}

void push(int v) {
    if (!t[v].up)
        return;

    t[v].count = t[v].set * (t[v].right - t[v].left + 1);
    t[v].segments = 1 * t[v].set;
    t[v].up = false;

    if (t[v].left == t[v].right)
        return;
    t[v * 2].up = true;
    t[v * 2 + 1].up = true;
    t[v * 2].set = t[v].set;
    t[v * 2 + 1].set = t[v].set;

}

bool leftBlack(int v) {
    push(v);

    if (t[v].left == t[v].right)
        return t[v].count == 1;

    return leftBlack(v * 2);
}

bool rightBlack(int v) {
    push(v);
    if (t[v].left == t[v].right)
        return t[v].count == 1;

    return rightBlack(v * 2 + 1);
}

void update(int v, int x, int l, int r) {
    if (t[v].right < l || t[v].left > r)
        return;

    if (t[v].right <= r && t[v].left >= l) {
        push(v);
        t[v].set = x;
        t[v].up = true;
        return;
    }

    push(v);
    update(v * 2, x, l, r);
    update(v * 2 + 1, x, l, r);
    bool right = rightBlack(v * 2);
    bool left = leftBlack(v * 2 + 1);
    t[v].count = t[v * 2].count + t[v * 2 + 1].count;
    t[v].segments = t[v * 2].segments + t[v * 2 + 1].segments;
    if(left && right) {
        t[v].segments--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, maxDelta = 0, segment, maxRight = 1e6, N;
    cin >> n;
    vector<char> c(n);
    vector<int> x(n), l(n);

    for (int i = 0; i < n; i++) {
        cin >> c[i] >> x[i] >> l[i];
        if (l[i] > 0) {
            l[i]--;
        } else {
            l[i]++;
        }
        segment = x[i] + l[i];
        if (segment > maxRight)
            maxRight = segment;
        if (maxDelta > x[i])
            maxDelta = x[i];
    }

    maxDelta < 0 ? N = maxRight - maxDelta + 1 : N = maxRight + 1;

    t.assign(4 * N, Node());

    build(1, 0, N);

    for (int i = 0; i < n; i++) {
        if (c[i] == 'W') {
            update(1, 0, x[i] - maxDelta, x[i] + l[i] - maxDelta);
            cout << t[1].segments << " " << t[1].count << '\n';
        } else {
            update(1, 1, x[i] - maxDelta, x[i] + l[i] - maxDelta);
            cout << t[1].segments << " " << t[1].count << '\n';

        }
    }
    return 0;
}
