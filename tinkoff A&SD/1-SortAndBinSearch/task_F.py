count = 0

def merge_sort(array):
    if len(array) <= 1:
        return array

    middle = len(array) // 2
    left = merge_sort(array[:middle])
    right = merge_sort(array[middle:])
    array = merge(left, right)
    return array


def merge(left, right):
    global count
    sorted_list = []
    pointer_left = 0
    pointer_right = 0
    while pointer_right < len(right) and pointer_left < len(left):
        if left[pointer_left] <= right[pointer_right]:
            sorted_list.append(left[pointer_left])
            pointer_left += 1
        else:
            sorted_list.append(right[pointer_right])
            pointer_right += 1
            count += len(left) - pointer_left

    while pointer_right < len(right):
        sorted_list.append(right[pointer_right])
        pointer_right += 1

    while pointer_left < len(left):
        sorted_list.append(left[pointer_left])
        pointer_left += 1
    return sorted_list


n = int(input())
arr = list(map(int, input().split()))
arr = merge_sort(arr)
print(count)
print(*arr)
