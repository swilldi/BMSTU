/*
Вывести на экран массив, упорядочив по возрастанию с помощью сортировки
выбором (англ. Selection Sort).
*/

#include <stdio.h>
#define OVERFLOW_EXIT_CODE 100
#define EMPTY_ARRAY 2
#define INPUT_ERROR_MESSAGE "Error: not a number entered\n"
#define EMPTY_ARRAY_MESSAGE "Error: array is empty"

void swap(int arr[], size_t i_1, size_t i_2)
{
    int memory_element = arr[i_1];
    arr[i_1] = arr[i_2];
    arr[i_2] = memory_element;
}

void selection_sort(int arr[], size_t length)
{
    if (!length)
    {
        return;
    }

    for (size_t i = 0; i < length - 1; i++)
    {
        // ищем минимальный элемент в неотсортированной части
        int min_element = arr[i], index_min_element = i;
        for (size_t j = i + 1; j < length; j++)
        {
            if (arr[j] < min_element)
            {
                min_element = arr[j];
                index_min_element = j;
            }
        }
        
        // совершаем свап
        swap(arr, i, index_min_element);
    }
}

// Заполнение массива
int input_arr(int arr[], size_t *index)
{
    int num;
    printf("Entry number: ");
    while (scanf("%d", &num) == 1)
    {
        if (*index < 10)
        {
            arr[*index] = num;
            *index += 1;
        }
        else
        {
            return OVERFLOW_EXIT_CODE;
        }
        
        // printf("%lu\n", *index);
        printf("Entry number: ");
    }
    return 0;
}

// Вывод массива
void print_arr(int arr[], size_t length)
{
    if (!length)
    {
        printf("Array is empty\n");
        return;
    }

    printf("|");
    for (size_t i = 0; i < length; i++)
    {
        printf(" %d |", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    size_t length = 0;
    int exit_code = 0;
    int arr[10];

    // заполнение массива и получение длины 
    exit_code = input_arr(arr, &length);
    // printf("%d", exit_code);

    if (!length)
    {
        printf(EMPTY_ARRAY_MESSAGE);
        return EMPTY_ARRAY;
    }

    // сортировака
    selection_sort(arr, length);

    // вывод массива
    print_arr(arr, length);
    
    return exit_code;
}
