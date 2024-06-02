#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    int depth;
    int height;
    Node* parent;
    vector<Node*> children;
    Node(int new_value, Node* curr_parent): value(new_value), parent(curr_parent) {};
};

int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int maxHeight = 0;
    for (int i = 0; i < node->children.size(); i++){
        maxHeight = max(maxHeight, getHeight(node->children[i]));
    }
    node->height = maxHeight + 1;
    return maxHeight + 1;
 }

int getDiameter(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int firstMaxHeight = 0, secondMaxHeigth = 0, maxDiameter = 0;
    for (int i = 0; i < node->children.size(); i++) {
        int currHeight = node->children[i]->height;
        if (currHeight > firstMaxHeight) {
            secondMaxHeigth = firstMaxHeight;
            firstMaxHeight = currHeight;
        } else if (currHeight > secondMaxHeigth) {
            secondMaxHeigth = currHeight;
        }
    }
    for (int i = 0; i < node->children.size(); i++) {
        maxDiameter = max(maxDiameter, getDiameter(node->children[i]));
    }
    return max(maxDiameter, firstMaxHeight + secondMaxHeigth);
}


int main() {
    int n, diameter, height = 0;
    cin >> n;
    vector<int> parents(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> parents[i];
    }

    vector<Node*> tree(n);
    tree[0] = new Node(0, nullptr);
    tree[0]->depth = 0;
    for (int i = 1; i < n; i++) {
        tree[i] = new Node(i, tree[parents[i - 1]]);
        tree[i]->depth = tree[parents[i - 1]]->depth + 1;
        tree[parents[i - 1]]->children.push_back(tree[i]);
        if (tree[parents[i - 1]]->depth + 1 > height) {
            height = tree[parents[i - 1]]->depth + 1;
        }
    }

    getHeight(tree[0]);
    diameter = getDiameter(tree[0]);

    cout << height << " " << diameter << '\n';
    for (int i = 0; i < n; i++){
        cout << tree[i]->depth << ' ';
    }
    return 0;
}
