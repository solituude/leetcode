class Tree:
    def __init__(self, length):
        self.n = len(length)
        self.mn = [0] * (4 * self.n)
        self.mn_len = [0] * (4 * self.n)
        self.add = [0] * (4 * self.n)
        self.build_tree(length)

    def build_tree(self, length):
        def _build_tree(node, left, right):
            if left + 1 == right:
                self.mn_len[node] = length[left]
            else:
                mid = (left + right) // 2
                _build_tree(2 * node, left, mid)
                _build_tree(2 * node + 1, mid, right)
                self.mn_len[node] = self.mn_len[2 * node] + self.mn_len[2 * node + 1]

        _build_tree(1, 0, self.n)

    def push_elements(self, node):
        self.add[2 * node] += self.add[node]
        self.mn[2 * node] += self.add[node]
        self.add[2 * node + 1] += self.add[node]
        self.mn[2 * node + 1] += self.add[node]
        self.add[node] = 0

    def update_tree(self, node, left, right, tree_left, tree_right, x):
        if right <= tree_left or tree_right <= left:
            return
        if tree_left <= left and right <= tree_right:
            self.add[node] += x
            self.mn[node] += x
            return

        self.push_elements(node)
        mid = (left + right) // 2
        self.update_tree(2 * node, left, mid, tree_left, tree_right, x)
        self.update_tree(2 * node + 1, mid, right, tree_left, tree_right, x)

        if self.mn[2 * node] == self.mn[2 * node + 1]:
            self.mn[node] = self.mn[2 * node]
            self.mn_len[node] = self.mn_len[2 * node] + self.mn_len[2 * node + 1]
        elif self.mn[2 * node] < self.mn[2 * node + 1]:
            self.mn[node] = self.mn[2 * node]
            self.mn_len[node] = self.mn_len[2 * node]
        else:
            self.mn[node] = self.mn[2 * node + 1]
            self.mn_len[node] = self.mn_len[2 * node + 1]

    def update_sequence(self, tree_left, tree_right, x):
        self.update_tree(1, 0, self.n, tree_left, tree_right, x)

    def query(self):
        return 0 if self.mn[1] else self.mn_len[1]


class Node:
    def __init__(self, x, y1, y2, type):
        self.x = x
        self.y1 = y1
        self.y2 = y2
        self.type = type

    def __lt__(self, v):
        return (self.x, -self.type) < (v.x, -v.type)


def main():
    n = int(input())

    q = []
    coord_set = set()
    for _ in range(n):
        x1, y1, x2, y2 = map(int, input().split())
        if x1 > x2 or y1 > y2:
            x1, x2 = x2, x1
            y1, y2 = y2, y1
        x2 += 1
        y2 += 1
        coord_set.add(y1)
        coord_set.add(y2)
        q.append(Node(x1, y1, y2, 1))
        q.append(Node(x2, y1, y2, -1))
    q.sort()

    sort_coord = sorted(coord_set)
    coordinates = {y: i for i, y in enumerate(sort_coord)}

    count = [sort_coord[i + 1] - sort_coord[i] for i in range(len(sort_coord) - 1)]
    sum_seg = sum(count)

    t = Tree(count)

    summa = 0
    prev = q[0].x
    for curr_q in q:
        summa += (sum_seg - t.query()) * (curr_q.x - prev)
        t.update_sequence(coordinates[curr_q.y1], coordinates[curr_q.y2], curr_q.type)
        prev = curr_q.x
    print(summa)


if __name__ == "__main__":
    main()
