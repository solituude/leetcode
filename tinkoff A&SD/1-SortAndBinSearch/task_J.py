def bin_search(n, m, high_ind, is_vertical_sep):
    low_ind = 1
    general_sum = (1 + n * m) / 2 * n * m
    while high_ind >= low_ind:
        separator = (high_ind + low_ind) // 2
        separator_minus = separator - 1
        separator_plus = separator + 1
        if is_vertical_sep:
            sum_before_separator = (separator * ((1 + separator) / 2 + ((n - 1) * m + 1 + (n - 1) * m + separator) / 2) / 2 * n)
            sum_before_separator_minus = (
                        separator_minus * ((1 + separator_minus) / 2 + ((n - 1) * m + 1 + (n - 1) * m + separator_minus) / 2) / 2 * n)
            sum_before_separator_plus = (
                        separator_plus * ((1 + separator_plus) / 2 + ((n - 1) * m + 1 + (n - 1) * m + separator_plus) / 2) / 2 * n)

        else:
            sum_before_separator = (1 + m * separator) / 2 * m * separator
            sum_before_separator_minus = (1 + m * separator_minus) / 2 * m * separator_minus
            sum_before_separator_plus = (1 + m * separator_plus) / 2 * m * separator_plus
        sum_after_separator = general_sum - sum_before_separator
        sum_after_separator_minus = general_sum - sum_before_separator_minus
        sum_after_separator_plus = general_sum - sum_before_separator_plus

        current_diff = abs(sum_before_separator - sum_after_separator)
        current_diff_minus = abs(sum_before_separator_minus - sum_after_separator_minus)
        current_diff_plus = abs(sum_before_separator_plus - sum_after_separator_plus)

        if current_diff_minus > current_diff > current_diff_plus:
            low_ind = separator + 1
        elif current_diff_minus < current_diff < current_diff_plus:
            high_ind = separator - 1
        elif current_diff < current_diff_minus and current_diff < current_diff_plus:
            return current_diff, separator + 1
        elif high_ind == low_ind:
            return current_diff, separator + 1


t = int(input())
query_arr = [[0, 0] for _ in range(t)]
answer = ""
for i in range(t):
    query_arr[i] = list(map(int, input().split()))

for i in range(t):
    vertical_min_diff, vertical_min_diff_index = bin_search(query_arr[i][0], query_arr[i][1], query_arr[i][1], True)
    horizontal_min_diff, horizontal_min_diff_index = bin_search(query_arr[i][0], query_arr[i][1], query_arr[i][0], False)

    if vertical_min_diff <= horizontal_min_diff:
        print("V", vertical_min_diff_index)
    else:
        print("H", horizontal_min_diff_index)
