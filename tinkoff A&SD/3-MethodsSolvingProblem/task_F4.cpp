#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, type;
    Point (int newX, int newType) : x(newX), type(newType) {};
};

bool comp (Point* a, Point* b) {
    return (a->x < b->x || (a->x == b->x && a->type > b->type));
}

int main() {
    long long sum = 0;
    int n, left, right, typeSum = 0;
    vector<Point*> points;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> left >> right;
        points.push_back(new Point(left, 1));
        points.push_back(new Point(right, -1));
    }

    sort(points.begin(), points.end(), comp);

    for (int i = 0; i < points.size(); i++) {
        if (typeSum >= 1) {
            sum += points[i]->x - points[i - 1]->x;
        }
        typeSum += points[i]->type;
    }
    cout << sum << endl;
    return 0;
}