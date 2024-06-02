def BubbleSort(arr, n):
    arr2 = arr.copy()
    count = 0
    for iteration in range(n):
        had_swaps = False
        count += 1
        for i in range(n - 1):
            if arr2[i] > arr2[i + 1]:
                arr2[i], arr2[i + 1] = arr2[i + 1], arr2[i]
                had_swaps = True
                # print(count, arr2)
        if not had_swaps:
            count += 1
            # print(count - 1, arr2)
            break

    return count - 1


array = list(map(int, input().split()))
print(BubbleSort(array, len(array)))
# my_list = list(range(11))  # Создаем массив от 0 до 10
# print("Исходный массив:", my_list)
#
# # Запрос пользователя на ввод элемента для удаления
# element_to_remove = int(input("Введите элемент для удаления: "))
#
# # Преобразуем список во множество для быстрого поиска
# my_set = set(my_list)
#
# # Проверяем, есть ли введенный элемент в списке
# if element_to_remove in my_set:
#     my_list.remove(element_to_remove)  # Удаляем элемент из списка
#     print("Элемент успешно удален.")
#     print("Обновленный массив:", my_list)
# else:
#     print("Элемент не найден в массиве.")


