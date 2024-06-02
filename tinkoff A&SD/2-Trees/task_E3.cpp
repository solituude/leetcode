#include <iostream>
#include <vector>

using namespace std;

struct Heap {
    vector<int> array;

    Heap() {
        array.push_back(0);
    }

    void heapify(int index) {
        int leftChild = index * 2;
        int rightChild = index * 2 + 1;
        int currChild;
        if (leftChild < array.size()) {
            if (rightChild < array.size() && array[leftChild] > array[rightChild]) {
                currChild = rightChild;
            } else {
                currChild = leftChild;
            }
            if (array[currChild] < array[index]) {
                int temp = array[currChild];
                array[currChild] = array[index];
                array[index] = temp;
                heapify(currChild);
            }
        }
    }

    void insert(int newNum) {
        array.push_back(newNum);
        int i = array.size() - 1;
        int parentIndex = i / 2;
        while (parentIndex > 0 && i > 1) {
            if (array[i] < array[parentIndex]) {
                int temp = array[i];
                array[i] = array[parentIndex];
                array[parentIndex] = temp;
            }
            i = parentIndex;
            parentIndex = i / 2;
        }
    }

    void extract() {
        cout << array[1] << " ";
        array[1] = array[array.size() - 1];
        array.pop_back();
        if (array.size() > 1) {
            heapify(1);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, currNum;
    cin >> n;
    Heap heap = Heap();
    for (int i = 0; i < n; i++) {
        cin >> currNum;
        heap.insert(currNum);
    }
    for (int i = 0; i < n; i++) {
        heap.extract();
    }
    return 0;
}
