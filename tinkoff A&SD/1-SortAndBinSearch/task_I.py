n = int(input())
change_position = list(map(int, input().split()))
zeroes_index_set = set([i for i in range(n)])
count_zeroes = n
left_border_index = n - 1
ans_array = [1]
buffer = set()
ones_index_set = set()
find_last = False
for i in range(n):
    curr_index_change = change_position[i] - 1

    if curr_index_change < n - 1 and not find_last:

        if left_border_index - 1 == curr_index_change:
            left_border_index = curr_index_change
            while left_border_index - 1 in buffer:
                buffer.remove(left_border_index - 1)
                left_border_index -= 1
        else:
            buffer.add(curr_index_change)
        zeroes_index_set.remove(curr_index_change)
        ones_index_set.add(curr_index_change)
        ans_array.append(len(ones_index_set) + 1)
    else:
        find_last = True
        if left_border_index - 1 == curr_index_change:
            left_border_index = curr_index_change
            while left_border_index - 1 in buffer:
                buffer.remove(left_border_index - 1)
                left_border_index -= 1
        elif curr_index_change != n - 1:
            buffer.add(curr_index_change)

        zeroes_index_set.remove(curr_index_change)
        ones_index_set.add(curr_index_change)
        ans_array.append(len(ones_index_set) - n + left_border_index + 1)
print(*ans_array)
#
# # ones_index_arr = []
# zeroes_index_array = [i for i in range(n)]
# count_zeroes = n
# zeroes_index_set = set(zeroes_index_array)
# max_index_zeroes = n - 1
# max_change_index = -1
# find_last = False
# left_border_index = n - 1
#
# ans_array = [1]
# for i in range(n - 1):
#     curr_index_change = change_position[i] - 1
#
#     if curr_index_change < n - 1 and not find_last:
#         zeroes_index_set.remove(curr_index_change)
#         count_zeroes -= 1
#         # ans_array.append(n - len(zeroes_index_array) + 1)
#         ans_array.append(n - count_zeroes + 1)
#         if curr_index_change > max_change_index:
#             max_change_index = curr_index_change
#     else:
#         find_last = True
#         zeroes_index_set.remove(curr_index_change)
#         count_zeroes -= 1
#         # ans_array.append(n - len(zeroes_index_array) - (n - 1 - zeroes_index_array[-1]) + 1)
#         ans_array.append(n - count_zeroes - (n - left_border_index) + 1)
#
#
# ans_array.append(1)
# print(*ans_array)
