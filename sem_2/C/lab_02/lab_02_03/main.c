/*
Удалить из исходного массива все элементы, которые являются числами-палин-
дромами. Ситуацию, когда массив после операции не изменился, ошибочной не
считать.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 10 
#define INPUT_ERROR 1
#define INPUT_ERROR_MESSAGE "Input is invalide"
#define OUT_OF_RANGE 2
#define OUT_OF_RANGE_MESSAGE "Length is out of range (Valid range 1-10)"
#define EMPTY_ARRAY 3
#define EMPTY_ARRAY_MESSAGE "Empty array"

int is_palindrome(int num)
{
    if (num < 0)
    {
        return 0;
    }

    int len = (int)log10(num), degree = (int)pow(10, len);
    
    while (num) 
    {
        if (num % 10 == num / degree)
        {
            num %= degree;
            num /= 10;

            degree /= 100;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

int input_arr(int *arr, int l)
{
    int num;
    for (int i = 0; i < l; i++)
    {
        printf("Entry element: ");
        if (scanf("%d", &num) == 1)
        {
            arr[i] = num;
        }
        else
        {
            return INPUT_ERROR;
        } 
    }

    return 0;
}

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int remove_palindroms(int *arr, int len)
{
    int new_len = 0;
    for (int i = 0; i < len; i++)
    {
        if (!is_palindrome(arr[i]))
        {
            arr[new_len++] = arr[i];
        }
    }

    return new_len;
}

int main(void)
{
    int array[MAX_SIZE];
    int len; 
    
    // ввод длины массива
    // ввели число

    printf("Entry length: ");
    if (scanf("%d", &len) != 1)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (len < 1 || len > MAX_SIZE)
    {
        printf(OUT_OF_RANGE_MESSAGE);
        return OUT_OF_RANGE;
    }

    //заполнене массива
    if (input_arr(array, len) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    // удаление палиндромов
    int new_len = remove_palindroms(array, len);

    if (new_len == 0)
    {
        printf(EMPTY_ARRAY_MESSAGE);   
        return EMPTY_ARRAY;
    }

    print_array(array, new_len);

    return 0;
}
