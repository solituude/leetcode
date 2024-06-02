def is_find_num(arr, curr_elem):
    right = len(arr) - 1
    left = 0
    while right - left >= 0:
        mid = (right + left) // 2
        if arr[mid] == curr_elem:
            return "YES"
        if curr_elem < arr[mid]:
            right = mid - 1
        else:
            left = mid + 1
    return "NO"


n, k = list(map(int, input().split()))
num_list = list(map(int, input().split()))
find_list = list(map(int, input().split()))
for i in range(k):
    print(is_find_num(num_list, find_list[i]))
