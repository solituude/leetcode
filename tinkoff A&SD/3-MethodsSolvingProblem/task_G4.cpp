#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, type;

    Point(int newX, int newType): x(newX), type(newType) {};
};

bool comp (Point* a, Point* b) {
    return (a->x < b->x || (a->x == b->x && a->type > b->type));
}

int main() {
    int n, minOpen = 0, maxOpen = 86400,
    hoursStart, minutesStart, secondsStart, hoursFinish, minutesFinish, secondsFinish, countSection = 0, sumSeconds = 0;
    cin >> n;
    vector<Point*> points;
    for (int i = 0; i < n; i++) {
        cin >> hoursStart >> minutesStart >> secondsStart >> hoursFinish >> minutesFinish >> secondsFinish;
        int start = hoursStart * 3600 + minutesStart * 60 + secondsStart;
        int finish = hoursFinish * 3600 + minutesFinish * 60 + secondsFinish;
        if (finish == start) {
            points.push_back(new Point(minOpen, 1));
            points.push_back(new Point(maxOpen, -1));
        } else if (finish < start) {
            points.push_back(new Point(minOpen, 1));
            points.push_back(new Point(finish, -1));
            points.push_back(new Point(start, 1));
            points.push_back(new Point(maxOpen, -1));
        } else {
            points.push_back(new Point(start, 1));
            points.push_back(new Point(finish, -1));
        }
    }
    sort(points.begin(), points.end(), comp);

    for (int i = 0; i < points.size(); i++) {
        if (countSection == n) {
            sumSeconds += points[i]->x - points[i - 1]->x;
        }
        countSection += points[i]->type;
    }
    cout << sumSeconds << endl;
    return 0;
}