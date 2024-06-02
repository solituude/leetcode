
def find_minimal_difference(n, m):
    general_sum = (1 + n * m) / 2 * n * m
    for separator in range(1, m):
        sum_before_separator = (separator * ((1 + separator) / 2 + ((n - 1) * m + 1 + (n - 1) * m + separator) / 2)
                                / 2 * n)
        print(f"V sep={separator + 1} left={sum_before_separator} right={general_sum - sum_before_separator} "
              f"diff={abs(sum_before_separator - (general_sum - sum_before_separator))}")

    for separator in range(1, n):
        sum_before_separator = (1 + m * separator) / 2 * m * separator
        print(f"H sep={separator + 1} left={sum_before_separator} right={general_sum - sum_before_separator} "
              f"diff={abs(sum_before_separator - (general_sum - sum_before_separator))}")


# for n in range(10, 20):
#     for m in range(1, 10):
#         if n == 1 and m == 1:
#             pass
#         else:
#             print(f"{n = } {m = }")
#             find_minimal_difference(n, m)
#             print('\n\n')

n, m = list(map(int, input().split()))
matrix = []
general_sum = (1 + n * m) / 2 * n * m
for i in range(1, n + 1):
    row = []
    for j in range(1, m + 1):
        row.append(j + (i - 1) * m)
    matrix.append(row)


print(matrix)
find_minimal_difference(n, m)


# def bin_search(low_ind, high_ind, is_vertical_sep):
#     min_diff = 1e10
#     min_diff_index = -1
#     while high_ind >= low_ind:
#         separator = (high_ind + low_ind) // 2
#         if is_vertical_sep:
#             sum_before_separator = (separator * ((1 + separator) / 2 + ((n - 1) * m + 1 + (n - 1) * m + separator) / 2)
#                                     / 2 * n)
#         else:
#             sum_before_separator = (1 + m * separator) / 2 * m * separator
#         sum_after_separator = general_sum - sum_before_separator
#         current_diff = abs(sum_before_separator - sum_after_separator)
#
#         if current_diff < min_diff or (min_diff == current_diff and separator < min_diff_index):
#             min_diff = current_diff
#             min_diff_index = separator
#
#         if sum_before_separator <= sum_after_separator:
#             low_ind = separator + 1
#         else:
#             high_ind = separator - 1
#     return min_diff, min_diff_index + 1
#
#
# t = int(input())
# answer = ""
# for i in range(t):
#     n, m = list(map(int, input().split()))
#     general_sum = (1 + n * m) / 2 * n * m
#
#     vertical_min_diff, vertical_min_diff_index = bin_search(1, m, True)
#     horizontal_min_diff, horizontal_min_diff_index = bin_search(1, n, False)
#
#     if vertical_min_diff <= horizontal_min_diff:
#         answer += f"V {vertical_min_diff_index}\n"
#         # print("V", vertical_min_diff_index)
#     else:
#         answer += f"H {vertical_min_diff_index}\n"
#         # print("H", horizontal_min_diff_index)
# print(answer[:-1])