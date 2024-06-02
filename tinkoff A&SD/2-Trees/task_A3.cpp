#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int value;
    int depth;
    Node* parent;
    vector<Node*> children;
    Node(int new_value, Node* curr_parent): value(new_value), parent(curr_parent) {};
};

int main() {
    int n, diameter = 0, height = 0, curr_diameter, first_many_child_ind = -1;
    cin >> n;
    vector<int> parents(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> parents[i];
    }
    Node* first_many_child = nullptr;
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

    // Находим узел с максимальной глубиной
    Node* max_depth_node = tree[0];
    for (int i = 1; i < n; i++) {
        if (tree[i]->depth > max_depth_node->depth) {
            max_depth_node = tree[i];
        }
    }

    // Первый обход BFS для нахождения вершины, наиболее удалённой от max_depth_node
    queue<Node*> q;
    vector<bool> visited(n, false);
    q.push(екуу);
    visited[max_depth_node->value] = true;
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        for (Node* child : curr->children) {
            if (!visited[child->value]) {
                q.push(child);
                visited[child->value] = true;
                child->parent = curr; // Запоминаем родителя для восстановления пути
            }
        }
    }

    // Второй обход BFS для определения длины диаметра
    Node* end_of_diameter = max_depth_node; // Начнём отсюда, потому что это уже найденная вершина
    diameter = 0;
    q.push(end_of_diameter);
    visited.assign(n, false);
    visited[end_of_diameter->value] = true;
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        for (Node* child : curr->children) {
            if (!visited[child->value]) {
                q.push(child);
                visited[child->value] = true;
                child->parent = curr;
                diameter = child->depth; // Обновляем диаметр
                end_of_diameter = child; // Обновляем конец диаметра
            }
        }
    }

    // Восстановление пути для нахождения длины диаметра
    Node* start_of_diameter = end_of_diameter;
    while (start_of_diameter != max_depth_node) {
        start_of_diameter = start_of_diameter->parent;
        diameter++;
    }

    cout << height << " " << diameter << '\n';
    for (int i = 0; i < n; i++){
        cout << tree[i]->depth << ' ';
    }
    return 0;
}
