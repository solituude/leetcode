#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
    Node(int value): value(value), height(0), left(nullptr), right(nullptr){};
};

int getHeight(Node* currNode) {
    if (currNode == nullptr) {
        return -1;
    } else {
        return currNode->height;
    }
}

void updateHeight(Node* currNode) {
    currNode->height = max(getHeight(currNode->right), getHeight(currNode->left)) + 1;
}

int getBalanceValue(Node* currNode) {
    if (currNode == nullptr) {
        return 0;
    } else {
        return getHeight(currNode->right) - getHeight(currNode->left);
    }
}

void swapNodes(Node* firstNode, Node* secondNode) {
    int tempValue = firstNode->value;
    firstNode->value = secondNode->value;
    secondNode->value = tempValue;
}

void rightRotation(Node* currNode) {
    swapNodes(currNode, currNode->left);
    Node* buff = currNode->right;
    currNode->right = currNode->left;
    currNode->left = currNode->right->left;
    currNode->right->left = currNode->right->right;
    currNode->right->right = buff;
    updateHeight(currNode->right);
    updateHeight(currNode);
}

void leftRotation(Node* currNode) {
    swapNodes(currNode, currNode->right);
    Node* buff = currNode->left;
    currNode->left = currNode->right;
    currNode->right = currNode->left->right;
    currNode->left->right = currNode->left->left;
    currNode->left->left = buff;
    updateHeight(currNode->left);
    updateHeight(currNode);
}

void balanceTree(Node* currNode) {
    int currBalance = getBalanceValue(currNode);
    if (currBalance == -2) {
        if (getBalanceValue(currNode->left) == 1) {
            leftRotation(currNode->left);
        }
        rightRotation(currNode);
    }
    else if (currBalance == 2) {
        if(getBalanceValue(currNode->right) == -1) {
            rightRotation(currNode->right);
        }
        leftRotation(currNode);
    }
}

void insert(Node* currNode, int value) {
    if (value < currNode->value) {
        if (currNode->left == nullptr) {
            currNode->left = new Node(value);
        } else {
            insert(currNode->left, value);
        }
    } else {
        if (currNode->right == nullptr) {
            currNode->right = new Node(value);
        } else {
            insert(currNode->right, value);
        }
    }
    updateHeight(currNode);
    balanceTree(currNode);
}

int ans = -1;

void searchNext(Node* node, int searchValue) {
    if (node == nullptr) {
        return;
    }
    if (searchValue > node->value) {
        searchNext(node->right, searchValue);
        return;
    } else {
        if (ans == -1 || ans != -1 && ans > node->value) {
            ans = node->value;
            searchNext(node->left, searchValue);
        } else {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unordered_map<int, int> dictionary;
    Node* node = nullptr;
    char typeOperation, lastOperation = ' ';
    int n, number, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> typeOperation;
        if (typeOperation == '+') {
            cin >> number;
            if (lastOperation == '?') {
                number = (number + y) % 1000000000;
            }
            if (!dictionary[number]) {
                if (node == nullptr) {
                    node = new Node(number);
                } else {
                    insert(node, number);
                }
                dictionary[number] = 1;
            }
        } else if (typeOperation == '?') {
            cin >> number;
            searchNext(node, number);
            y = ans;
            ans = -1;
            cout << y << '\n';
        }
        lastOperation = typeOperation;
    }
    return 0;
}
