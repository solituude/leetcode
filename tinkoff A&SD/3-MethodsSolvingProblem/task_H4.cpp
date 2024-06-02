#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    long long taskNumber, start, end;
    Interval(long long newTaskNumber, long long newStart, long long newEnd):
        taskNumber(newTaskNumber),
        start(newStart), end(newEnd) {};
};

bool comp(Interval* a, Interval* b) {
    return (a->end < b->end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n, c, s, t, count = 1, currInterval = 0;
    cin >> n >> c;
    vector<Interval*> intervals;
    vector<long long> tasks;
    for (int i = 1; i <= n; i++) {
        cin >> s >> t;
        intervals.push_back(new Interval(i, s, s + t));
    }
    sort(intervals.begin(), intervals.end(), comp);
    tasks.push_back(intervals[0]->taskNumber);
    for (int i = 0; i < n; i++) {
        if (intervals[currInterval]->end <= intervals[i]->start) {
            count++;
            currInterval = i;
            tasks.push_back(intervals[i]->taskNumber);
        }
    }

    cout << count * c << endl;
    cout << count << endl;
    for (int i = 0; i < tasks.size(); i++) {
        cout << tasks[i] << " ";
    }

    return 0;
}