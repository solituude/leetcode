#include <iostream>
#include <vector>


using namespace std;

struct Heap {
    vector<int> array;

    Heap() {
        array.push_back(-1);
    }

    void heapify(int index) {
        int leftChild = index * 2;
        int rightChild = index * 2 + 1;
        if (leftChild < array.size()) {
            if (array[leftChild] > array[index]) {
                int temp = array[index];
                array[index] = array[leftChild];
                array[leftChild] = temp;
                heapify(leftChild);
            }
        }
        if (rightChild < array.size()) {
            if (array[rightChild] > array[index]) {
                int temp = array[index];
                array[index] = array[rightChild];
                array[rightChild] = temp;
                heapify(rightChild);
            }
        }
    }

    void insert(int newNum) {
        array.push_back(newNum);
        int i = array.size() - 1;
        int parentIndex = i / 2;
        while (parentIndex > 0 && i > 1) {
            if (array[i] > array[parentIndex]) {
                int temp = array[i];
                array[i] = array[parentIndex];
                array[parentIndex] = temp;
            }
            i = parentIndex;
            parentIndex = i / 2;
        }
    }

    void extract() {
        cout << array[1] << endl;
        array[1] = array[array.size() - 1];
        array.pop_back();
        if (array.size() > 1) {
            heapify(1);
        }
    }
};

int main() {
    int n, typeAction, addedNum;
    cin >> n;
    Heap heap;
    for (int i = 0; i < n; i++) {
        cin >> typeAction;
        if (typeAction == 0) {
            cin >> addedNum;
            heap.insert(addedNum);
        } else {
            heap.extract();
        }
    }

    return 0;
}
