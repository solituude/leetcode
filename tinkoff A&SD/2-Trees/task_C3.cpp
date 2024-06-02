#include <iostream>
#include <unordered_map>

using namespace std;

//int main() {
//    int n, q, u, v, parent_u, parent_v;
//    cin >> n;
//    unordered_map<int, int> parent;
//    for (int i = 0; i < n - 1; i++) {
//        cin >> parent[i + 1];
//    }
//    cin >> q;
//    for (int i = 0; i < q; i++) {
//        cin >> u >> v;
//        bool find = false;
//        int ans;
//        parent_u = parent[u];
//        parent_v = parent[v];
//        while (!find) {
//            if (parent_v == parent_u) {
//                find = true;
//                ans = parent_v;
//            } else if (v == parent_u) {
//                find = true;
//                ans = v;
//            } else if (u == parent_v) {
//                find = true;
//                ans = u;
//            } else if (parent_v > parent_u) {
//                v = parent_v;
//                parent_v = parent[v];
//            } else if (parent_v < parent_u) {
//                u = parent_u;
//                parent_u = parent[u];
//            }
//        }
//        cout << ans << '\n';
//    }
//    return 0;
//}
class Myheap{
    vector<int> heap;
    void sift_up(int v) {
        while (v > 1 && heap[v] > heap[v / 2]) {
            swap(heap[v], heap[v / 2]);
            v /= 2;
        }
    }
    void sift_down(int v) {
        while (2 * v <= heap.size()-1) {
            int l = 2 * v;
            int r = 2 * v + 1;
            int u = (r <= heap.size()-1 && heap[r] > heap[l] ? r : l);
            if (heap[v] >= heap[u])
                break;
            swap(heap[v], heap[u]);
            v = u;
        }
    }

    void build_heap() {
        for (int i = heap.size()-1; i > 0; --i) {
            sift_down(i);
        }
    }
public:
    Myheap(vector <int>& array){
        heap = vector<int> (array.size() + 1);
        for (int i = 0; i < array.size(); i++){
            heap[i+1] = array[i];
        }
        build_heap();
    }
    Myheap(){
        heap.push_back(0);
    }
    int getMax(){
        return heap[1];
    }
    int extractMax(){
        int answer = heap[1];
        heap[1] = heap[heap.size()-1];
        heap.pop_back();
        sift_down(1);
        return answer;
    }
    int push(int x){
        heap.push_back(x);
        sift_up(heap.size()-1);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Myheap heap =  Myheap();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int codeOperation;
        cin >> codeOperation;
        if(codeOperation == 0){
            int newNumber;
            cin >> newNumber;
            heap.push(newNumber);
        }
        else{
            cout << heap.extractMax() << '\n';
        }
    }
    return 0;
}