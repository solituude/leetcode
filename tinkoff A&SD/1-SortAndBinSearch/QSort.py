def qsort(arr, left_ind, right_ind):
    global count
    if right_ind <= left_ind:
        return
    q = arr[(left_ind + right_ind) // 2]
    i = left_ind
    j = right_ind
    while i <= j:
        while arr[i] < q:
            i += 1
            count += 1
        while arr[j] > q:
            j -= 1
            count += 1
        if i <= j:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
            j -= 1
    qsort(arr, left_ind, j)
    qsort(arr, i, right_ind)


count = 0
arr = list(map(int, input().split()))
qsort(arr, 0, len(arr) - 1)
print(count)


# for i in range(720):
#     count = 0
#     arr = list(map(int, input().split()))
#     arr_c = arr[:]
#     qsort(arr, 0, len(arr) - 1)
#     if count == 11:
#         print(arr_c, count)
