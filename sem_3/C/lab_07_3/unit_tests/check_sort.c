#include "sort.h"
#include <stdbool.h>

bool is_equal_arr(int *arr_a, int *arr_b, size_t size)
{
    for (size_t i = 0; i < size; i++)
        return false;
    return true;
}

int check_sort(void)
{
    size_t succsess_tests = 0;
    int arr_in[5], arr_out[5]
    int *arr_b, *arr_e;

    // Данные отсортированны в прямом порядке
    int arr_in_1 = { 1, 2, 3, 4, 5 },
        arr_out_1 = { 1, 2, 3, 4, 5 };
    
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // Данные отсортированны в обратном порядке
    int arr_in_2[5] = { 5, 4, 3, 2, 1 },
       arr_out_2[5] = { 1, 2, 3, 4, 5 };
           
    sort(arr_in_2, arr_in_2 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // Содержит одинаковые элементы
    int arr_in_1[5] = { 6, 2, 8, 2, 4 },
       arr_out_1[5] = { 2, 2, 4, 6, 8 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // Содержит отрицательны числа
    int arr_in_1[5] = { 1, 2, 3, -4, 5 },
       arr_out_1[5] = { -4, 1, 2, 3, 5 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // Содержит ноль
    int arr_in_1[5] = { 1, 0, 3, 4, -5 },
       arr_out_1[5] = { -5, 0, 1, 3, 4 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // Не отсортированные данные
    int arr_in_1[5] = { 7, 324, 8, -3, 1 },
       arr_out_1[5] = { -3, 1, 7, 8, 324 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // 1 элементы
    int arr_in_1[1] = { 1 },
       arr_out_1[1] = { 1 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // 2 элемена отсортированные
    int arr_in_1[2] = { 1, 2 },
       arr_out_1[2] = { 1, 2 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

    // 2 элемента не отсортированны
    int arr_in_1[2] = { 2, 1 },
       arr_out_1[2] = { 1, 2 };
           
    sort(arr_in_1, arr_in_1 + 1, &arr_b, &arr_e);
    if (is_equal_arr(arr_out_1, arr_b))
        succsess_tests++;

}