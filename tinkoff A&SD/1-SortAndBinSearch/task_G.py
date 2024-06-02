def reverse_qsort(sorted_arr):
    for j in range(2, len(sorted_arr)):
        sorted_arr[j], sorted_arr[j // 2] = sorted_arr[j // 2], sorted_arr[j]
    return sorted_arr


n = int(input())
sort_arr = []
for i in range(1, n + 1):
    sort_arr.append(i)
print(*reverse_qsort(sort_arr))
