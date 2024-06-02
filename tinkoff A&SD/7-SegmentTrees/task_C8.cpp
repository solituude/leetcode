////#include <iostream>
////#include <vector>
////
////using namespace std;
////
////void buildTree(int node, int treeLeft, int treeRight, vector<int> &tree, vector<int> &arr) {
////    if (treeLeft == treeRight) {
////        tree[node] = arr[treeLeft];
////    } else {
////        int tm = (treeLeft + treeRight) / 2;
////        buildTree(node * 2, treeLeft, tm, tree, arr);
////        buildTree(node * 2 + 1, tm + 1, treeRight, tree, arr);
////        tree[node] = tree[node * 2] + tree[node * 2 + 1];
////    }
////}
////
////int getIndexK (int node, int left, int right, int k, vector<int>& tree) {
////    if (left == right) {
////        return left;
////    }
////    int mid = (left + right) / 2;
////    if (k <= tree[2 * node]) {
////        return getIndexK(node * 2, left, mid, k, tree);
////    } else {
////        return getIndexK(node * 2 + 1, mid + 1, right, k - tree[2 * node], tree);
////    }
////}
////
////
////void updateTree(int index, int value, int node, int treeLeft, int treeRight, vector<int> &tree, vector<int> &arr) {
////    if (treeRight == treeLeft) {
////        tree[node] = value;
////    } else {
////        int mid = (treeLeft + treeRight) / 2;
////        if (index <= mid) {
////            updateTree(index, value, node * 2, treeLeft, mid, tree, arr);
////        } else {
////            updateTree(index, value, node * 2 + 1, mid + 1, treeRight, tree, arr);
////        }
////        tree[node] = tree[node * 2] + tree[node * 2 + 1];
////    }
////}
////
////int main() {
////    int n, m;
////    cin >> n >> m;
////    vector<int> a(n);
////    vector<int> tree(4 * n, 0);
////    for (int i = 0; i < n; i++) {
////        cin >> a[i];
////    }
////    buildTree(1, 0, n - 1, tree, a);
////    for (int i = 0; i < m; i++) {
////        int codeOperation;
////        cin >> codeOperation;
////        if (codeOperation == 1) {
////            int ind;
////            cin >> ind ;
////            if (a[ind] == 0) {
////                updateTree(ind, 1, 1, 0, n - 1, tree, a);
////                a[ind] = 1;
////            } else {
////                updateTree(ind, 0, 1, 0, n - 1, tree, a);
////                a[ind] = 0;
////            }
////        } else {
////            int k;
////            cin >> k;
////            cout << getIndexK(1, 0, n - 1, k + 1, tree) << '\n';
////        }
////    }
////    return 0;
////}
//
//
//#include <iostream>
//#include <vector>
//#include <set>
//#include <unordered_map>
//
//using namespace std;
//
//const int mod = 1000000000 + 7;
//struct bit_node {
//    int max_len;
//    int freq;
//};
//
//class FenwickTree {
//    vector<bit_node> bit;
//    int size;
//public:
//
//    explicit FenwickTree(int size) : size(size) {
//        bit.assign(size, {0, 0});
//    }
//
//    void update(int idx, bit_node node) {
//        while (idx < size) {
//            if (bit[idx].max_len < node.max_len) {
//                bit[idx] = node;
//            } else if (bit[idx].max_len == node.max_len) {
//                bit[idx].freq = (bit[idx].freq + node.freq) % mod;
//            }
//            idx = idx | (idx + 1);
//        }
//    }
//
//    struct bit_node query(int idx) {
//        struct bit_node range_max = {0, 1};
//        while (0 <= idx) {
//            if (range_max.max_len < bit[idx].max_len) {
//                range_max = bit[idx];
//            } else if (range_max.max_len == bit[idx].max_len) {
//                range_max.freq = (range_max.freq + bit[idx].freq) % mod;
//            }
//            idx = (idx & (idx + 1)) - 1;
//        }
//        return range_max;
//    }
//};
//
//int findNumberOfLIS(vector<int> &nums) {
//    set<int> sorted(nums.begin(), nums.end());
//
//    unordered_map<int, int> num2index;
//
//    int pos = 0;
//    for (auto &num: sorted) {
//        num2index[num] = pos++;
//    }
//
//
//    FenwickTree fwt((int) sorted.size() + 1);
//
//    for (auto &num: nums) {
//        int idx = num2index[num];
//        bit_node node = fwt.query(idx - 1);
//        fwt.update(idx, {node.max_len + 1, node.freq});
//    }
//    return fwt.query((int) sorted.size()).freq;
//}
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
//    int n;
//    cin >> n;
//    vector<int> nums(n);
//    for (int i = 0; i < n; ++i) cin >> nums[i];
//    cout << findNumberOfLIS(nums);
//    return 0;
//}

// C++ implementation of the above approach
#include <iostream>
using namespace std;

#define M 100000

// Stores the Segment tree
vector<pair<int, int> > tree(4 * M + 1);

// Function to update Segment tree, the root
// of which contains the length of the LIS
void update_tree(int start, int end,
                 int update_idx, int length_t,
                 int count_c, int idx)
{
    // If the intervals
    // are overlapping completely
    if (start == end
        && start == update_idx) {
        tree[idx].first
                = max(tree[idx].first, length_t);
        tree[idx].second = count_c;
        return;
    }

    // If intervals are not overlapping
    if (update_idx < start
        || end < update_idx) {
        return;
    }

    // If intervals are partially overlapping
    int mid = (start + end) / 2;

    update_tree(start, mid, update_idx,
                length_t, count_c,
                2 * idx);
    update_tree(mid + 1, end, update_idx,
                length_t, count_c,
                2 * idx + 1);

    // If length_t of left and
    // right child are equal
    if (tree[2 * idx].first
        == tree[2 * idx + 1].first) {
        tree[idx].first
                = tree[2 * idx].first;
        tree[idx].second
                = tree[2 * idx].second
                  + tree[2 * idx + 1].second;
    }

        // If length_t of left > length_t right child
    else if (tree[2 * idx].first
             > tree[2 * idx + 1].first) {
        tree[idx] = tree[2 * idx];
    }

        // If length_t of left < length_t right child
    else {
        tree[idx] = tree[2 * idx + 1];
    }
}

// Function to find the LIS length
// and count in the given range
pair<int, int> query(int start, int end,
                     int query_start,
                     int query_end, int idx)
{
    // If the intervals
    // are overlapping completely
    if (query_start <= start
        && end <= query_end) {
        return tree[idx];
    }

    // If intervals are not overlapping
    pair<int, int> temp({ INT32_MIN, 0 });
    if (end < query_start
        || query_end < start) {
        return temp;
    }

    // If intervals are partially overlapping
    int mid = (start + end) / 2;
    auto left_child
            = query(start, mid, query_start,
                    query_end, 2 * idx);
    auto right_child
            = query(mid + 1, end, query_start,
                    query_end, 2 * idx + 1);

    // If length_t of left child is greater
    // than length_t of right child
    if (left_child.first > right_child.first) {
        return left_child;
    }

    // If length_t of right child is
    // greater than length_t of left child
    if (right_child.first > left_child.first) {
        return right_child;
    }

    // If length_t of left
    // and right child are equal
    // return there sum
    return make_pair(left_child.first,
                     left_child.second
                     + right_child.second);
}

// Comparator function to sort an array of pairs
// in increasing order of their 1st element and
// thereafter in decreasing order of the 2nd
bool comp(pair<int, int> a, pair<int, int> b)
{
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

// Function to find count
// of LIS in the given array
int countLIS(int arr[], int n)
{
    // Generating value-index pair array
    vector<pair<int, int> > pair_array(n);
    for (int i = 0; i < n; i++) {
        pair_array[i].first = arr[i];
        pair_array[i].second = i;
    }

    // Sort array of pairs with increasing order
    // of value and decreasing order of index
    sort(pair_array.begin(),
         pair_array.end(), comp);

    // Traverse the array
    // and perform query updates
    for (int i = 0; i < n; i++) {

        int update_idx = pair_array[i].second;

        // If update index is the 1st index
        if (update_idx == 0) {
            update_tree(0, n - 1, 0, 1, 1, 1);
            continue;
        }

        // Query over the interval [0, update_idx -1]
        pair<int, int> temp
                = query(0, n - 1, 0,
                        update_idx - 1, 1);

        // Update the segment tree
        update_tree(0, n - 1, update_idx,
                    temp.first + 1,
                    max(1, temp.second), 1);
    }

    // Stores the final answer
    pair<int, int> ans
            = query(0, n - 1, 0, n - 1, 1);

    // Return answer
    return ans.second;
}

// Driver Code
int main()
{
    int arr[] = { 1, 3, 5, 4, 7 };
    int n = sizeof(arr) / sizeof(int);

    cout << countLIS(arr, n);

    return 0;
}
