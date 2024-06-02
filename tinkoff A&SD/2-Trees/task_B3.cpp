#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > inputArray;
bool isEqualTree = true;
bool isCorrectBinaryTree = true;

struct Node {
    int value;
    int height;
    int maxElemInSubtree;
    int minElemInSubtree;
    Node* left;
    Node* right;
    Node(int new_value): value(new_value), height(0), left(nullptr), right(nullptr), maxElemInSubtree(-1), minElemInSubtree(1e5 + 1) {};
};

int getHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    } else {
        return node->height;
    }
}

int getMaxElemSubtree(Node* node) {
    if (node == nullptr) {
        return -1;
    } else {
        return node->maxElemInSubtree;
    }
}

int getMinElemSubtree(Node* node) {
    if (node == nullptr) {
        return 1e5 + 1;
    } else {
        return node->minElemInSubtree;
    }
}

void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    node->maxElemInSubtree = max(getMaxElemSubtree(node->right), getMaxElemSubtree(node->right));
    if (node->right != nullptr) {
        node->maxElemInSubtree = max(node->maxElemInSubtree, node->right->value);
    }
    if (node->left != nullptr) {
        node->maxElemInSubtree = max(node->maxElemInSubtree, node->left->value);
    }

    node->minElemInSubtree = min(getMinElemSubtree(node->right), getMinElemSubtree(node->left));
    if (node->right != nullptr) {
        node->minElemInSubtree = min(node->minElemInSubtree, node->right->value);
    }
    if (node->left != nullptr) {
        node->minElemInSubtree = min(node->minElemInSubtree, node->left->value);
    }
}

int getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return getHeight(node->right) - getHeight(node->left);
    }
}

bool isBalance(Node* node) {
    int balance = getBalance(node);
    if (abs(balance) <= 1) {
        return true;
    }
    return false;
}

void insert(Node* node, int leftChild, int rightChild, int parent) {
    if (leftChild < node->value && leftChild != -1) {
        if (node->left == nullptr) {
            node->left = new Node(leftChild);
            insert(node->left, inputArray[leftChild][0], inputArray[leftChild][1], leftChild);
        } else {
            insert(node->left, leftChild, rightChild, parent);
        }
    }
    if (rightChild > node->value && rightChild != -1) {
        if (node->right == nullptr) {
            node->right = new Node(rightChild);
            insert(node->right, inputArray[rightChild][0], inputArray[rightChild][1], rightChild);
        } else {
            insert(node->right,  leftChild, rightChild, parent);
        }
    }
    updateHeight(node);
}

void isEqual(Node* node) {
    if (node == nullptr) return;

    if (node->left != nullptr && node->left->value == inputArray[node->value][0]) {
        isEqual(node->left);
    } else if (node->left == nullptr && inputArray[node->value][0] == -1) {
        return;
    } else {
        isEqualTree = false;
        return;
    }

    if (node->right != nullptr && node->right->value == inputArray[node->value][1]) {
        isEqual(node->right);
    } else if (node->right == nullptr && inputArray[node->value][1] == -1) {
        return;
    } else {
        isEqualTree = false;
//        cout << "ERROR right" << endl;
        return;
    }
}

void isCorrect(Node* node) {
    if (node == nullptr) return;
    isCorrect(node->left);
    isCorrect(node->right);
    if (node->left != nullptr && node->left->maxElemInSubtree > node->value) {
        isCorrectBinaryTree = false;
        return;
    }
    if (node->right != nullptr && node->right->minElemInSubtree < node->value) {
        isCorrectBinaryTree = false;
        return;
    }
}

int main(){
    int n, r;
    cin >> n >> r;
    Node* tree = new Node(r);
    for (int i = 0; i < n; i++) {
        vector<int> currChildren (2);
        cin >> currChildren[0] >> currChildren[1];
        inputArray.push_back(currChildren);
    }

    insert(tree, inputArray[r][0], inputArray[r][1], r);
    isEqual(tree);
    isCorrect(tree);
    if (isBalance(tree)) {
        if(isEqualTree) {
            if (isCorrectBinaryTree){
                cout << 1 << endl;
                return 0;
            }
        }
    }
    cout << 0;
    return 0;
}
