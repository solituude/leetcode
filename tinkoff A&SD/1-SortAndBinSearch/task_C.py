import datetime
class Node:
    def __init__(self, n=1, seg=1, s=0, left=0, right=0, u=False):
        self.sum_len = n
        self.count_segments = seg
        self.set = s
        self.l = left
        self.r = right
        self.up = u


def build(v, tl, tr, t):
    if tl == tr:
        t[v] = Node(0, 0, 0, tl, tr, False)
    else:
        mid = (tl + tr) // 2
        build(v * 2, tl, mid, t)
        build(v * 2 + 1, mid + 1, tr, t)
        t[v] = Node(0, 0, 0, tl, tr, False)


def push(t, v):
    if not t[v].up:
        return

    t[v].sum_len = t[v].set * (t[v].r - t[v].l + 1)
    t[v].count_segments = 1 * t[v].set
    t[v].up = False

    if t[v].l == t[v].r:
        return
    t[v * 2].up = True
    t[v * 2 + 1].up = True
    t[v * 2].set = t[v].set
    t[v * 2 + 1].set = t[v].set


def left_node_is_black(t, v):
    push(t, v)

    if t[v].l == t[v].r:
        return t[v].sum_len == 1

    return left_node_is_black(t, v * 2)


def right_node_is_black(t, v):
    push(t, v)

    if t[v].l == t[v].r:
        return t[v].sum_len == 1

    return right_node_is_black(t, v * 2 + 1)


def update(t, v, value, l, r):
    if t[v].r < l or t[v].l > r:
        return

    if t[v].r <= r and t[v].l >= l:
        push(t, v)
        t[v].set = value
        t[v].up = True
        return

    push(t, v)
    update(t, v * 2, value, l, r)
    update(t, v * 2 + 1, value, l, r)

    right_is_black = right_node_is_black(t, v * 2)
    left_is_black = left_node_is_black(t, v * 2 + 1)

    t[v].sum_len = t[v * 2].sum_len + t[v * 2 + 1].sum_len
    t[v].count_segments = t[v * 2 + 1].count_segments + t[v * 2].count_segments

    if left_is_black and right_is_black:
        t[v].count_segments -= 1


if __name__ == "__main__":
    n = int(input())
    max_delta = 0
    segment = 0
    max_right = 10 ** 6
    x = []
    l = []
    colors = []

    for _ in range(n):
        color, x_val, l_val = input().split()
        x_val = int(x_val)
        l_val = int(l_val)
        l_val = l_val - 1 if l_val > 0 else l_val + 1
        segment = x_val + l_val
        if segment > max_right:
            max_right = segment
        if max_delta > x_val:
            max_delta = x_val
        x.append(x_val)
        l.append(l_val)
        colors.append(color)
    start = datetime.datetime.now()
    len_tree = max_right - max_delta + 1 if max_delta < 0 else max_right + 1
    t = [Node() for _ in range(4 * len_tree)]
    build(1, 0, len_tree, t)

    for i in range(n):
        if colors[i] == 'W':
            update(t, 1, 0, x[i] - max_delta, x[i] + l[i] - max_delta)
        elif colors[i] == 'B':
            update(t, 1, 1, x[i] - max_delta, x[i] + l[i] - max_delta)
        print(t[1].count_segments, t[1].sum_len)
    finish = datetime.datetime.now()
    print('Время работы: ' + str(finish - start))
