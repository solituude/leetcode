class SegmentTree:
    def __init__(self, length):
        self.n = len(length)
        self.seg = [0] * (4 * self.n)
        self.seg_len = [0] * (4 * self.n)
        self.add = [0] * (4 * self.n)
        self.build(length)

    def build(self, length):
        def _build(v, l, r):
            if l + 1 == r:
                self.seg_len[v] = length[l]
            else:
                m = (l + r) // 2
                _build(2 * v, l, m)
                _build(2 * v + 1, m, r)
                self.seg_len[v] = self.seg_len[2 * v] + self.seg_len[2 * v + 1]

        _build(1, 0, self.n)

    def propagation(self, v):
        self.add[2 * v] += self.add[v]
        self.seg[2 * v] += self.add[v]
        self.add[2 * v + 1] += self.add[v]
        self.seg[2 * v + 1] += self.add[v]
        self.add[v] = 0

    def update(self, v, l, r, lx, rx, val):
        if r <= lx or rx <= l:
            return
        if lx <= l and r <= rx:
            self.add[v] += val
            self.seg[v] += val
            return

        self.propagation(v)
        m = (l + r) // 2
        self.update(2 * v, l, m, lx, rx, val)
        self.update(2 * v + 1, m, r, lx, rx, val)

        if self.seg[2 * v] == self.seg[2 * v + 1]:
            self.seg[v] = self.seg[2 * v]
            self.seg_len[v] = self.seg_len[2 * v] + self.seg_len[2 * v + 1]
        elif self.seg[2 * v] < self.seg[2 * v + 1]:
            self.seg[v] = self.seg[2 * v]
            self.seg_len[v] = self.seg_len[2 * v]
        else:
            self.seg[v] = self.seg[2 * v + 1]
            self.seg_len[v] = self.seg_len[2 * v + 1]

    def update_range(self, lx, rx, val):
        self.update(1, 0, self.n, lx, rx, val)

    def query(self):
        return 0 if self.seg[1] else self.seg_len[1]


class Query:
    def __init__(self, x, y1, y2, type):
        self.x = x
        self.y1 = y1
        self.y2 = y2
        self.type = type

    def __lt__(self, other):
        return (self.x, -self.type) < (other.x, -other.type)


def main():
    n = int(input())

    queries = []
    y_set = set()
    for _ in range(n):
        x1, y1, x2, y2 = map(int, input().split())
        if x1 > x2 or y1 > y2:
            x1, x2 = x2, x1
            y1, y2 = y2, y1
        x2 += 1
        y2 += 1
        y_set.add(y1)
        y_set.add(y2)
        queries.append(Query(x1, y1, y2, 1))
        queries.append(Query(x2, y1, y2, -1))
    queries.sort()

    sorted_yy = sorted(y_set)
    y_coord_index = {y: i for i, y in enumerate(sorted_yy)}

    length = [sorted_yy[i + 1] - sorted_yy[i] for i in range(len(sorted_yy) - 1)]
    sum_seg = sum(length)

    seg_tree = SegmentTree(length)

    ans = 0
    prev_x = queries[0].x
    for q in queries:
        ans += (sum_seg - seg_tree.query()) * (q.x - prev_x)
        seg_tree.update_range(y_coord_index[q.y1], y_coord_index[q.y2], q.type)
        prev_x = q.x
    print(ans)


if __name__ == "__main__":
    main()
