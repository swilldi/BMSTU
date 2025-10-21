#include "matrix_struct.h"
#include <stdio.h>
#include "output_func.h"
#include "exit_code.h"

#include <stdbool.h>

void print_matrix(matrix_data_t matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_razr_debug(matrix_t *mtr)
{
    size_t elem_count, dim_len;
    if (mtr->type == TYPE_CSR)
    {
        elem_count = mtr->dim[mtr->n - 1];
        dim_len = mtr->n;
    }
    else
    {
        elem_count = mtr->dim[mtr->m - 1];
        dim_len = mtr->m;
    }

    printf("Индекс в строке: ");
    for (size_t i = 0; i < elem_count; i++)
    {
        printf("%3d ", mtr->ind[i]);
    }
    printf("\n");

    printf("       Значение: ");
    for (size_t i = 0; i < elem_count; i++)
    {
        printf("%3d ", mtr->values[i]);
    }
    printf("\n");

    
    printf("кол-во в строке: ");
    for (size_t i = 0; i < dim_len; i++)
    {
        printf("%3d ", mtr->dim[i]);
    }
    printf("\n");

}

void print_csr_matrix(matrix_t *mtr)
{
    size_t ind = 0, len;
    for (size_t i = 0; i < mtr->n; i++)
    {
        if (i != 0)
            len = mtr->dim[i] - mtr->dim[i - 1];
        else
            len = mtr->dim[i];

        size_t i_in_row = mtr->ind[ind];
        for (size_t j = 0; j < mtr->m; j++)
        {
            if (len && i_in_row == j)
            {
                printf("%5d", mtr->values[ind]);
                ind++;
                len--;
                if(len) i_in_row = mtr->ind[ind]; // добавить проверку
            }
            else
            {
                printf("%5d", 0);
            }
        }
        ind = mtr->dim[i];
        printf("\n");
    }
}

void print_csr_coord(matrix_t *mtr)
{
    printf(
        "\nВывод в формате i j v\n"
        "i – строка\n"
        "j - колонка\n"
        "v – значение\n"
    );
    size_t shift = 0, len;
    for (size_t i = 0; i < mtr->n; i++)
    {
        if (i != 0)
            len = mtr->dim[i] - mtr->dim[i - 1];
        else
            len = mtr->dim[i];

        
        for (size_t j = 0; j < len; j++)
        {
            printf("%zu %u %d\n", i + 1, mtr->ind[shift + j] + 1, mtr->values[shift + j]);
        }
        shift = mtr->dim[i];
    }
}


void print_input_cmd_list(void)
{
    printf(
        "Программы выполняет умножение матриц AxB\n"
        "При координатном вводе/выводе индексы матрицы начинаются с 1\n\n"
        "Тип ввода:\n"
        "1. Классический ввод\n"
        "2. Координатный ввод\n"
        "3. Классический файл\n"
        "4. Координатный файл\n"
        "5. Сравнение\n"
    );
}

void print_output_cmd_list(void)
{
    printf(
        "\nТип вывода:\n"
        "1. Матричный вывод\n"
        "2. Координатный вывод\n"
        "3. CSR файл\n"
        "0. Выход\n"
    );
}


void print_err_msg(int code)
{
    #ifdef FUNC_OUT
    code = OK;
    #endif

    switch (code)
    {
        case INVALID_INPUT:
            printf("Некоректный ввод\n");
            break;
        case NEGATIVE_SIZE:
            printf("Отрицательная размерность\n");
            break;
        case MATR_RANGE_ERR:
            printf("Индекс вне диапазона матрицы\n");
            break;
        case MATRIX_OVERFLOW:
            printf("Указано слишком много элеменов для матрицы\n");
            break;
        case CMD_RANGE_ERR:
            printf("Неизвестный номер команды\n");
            break;
        case STR_OVERFLOW:
            printf("Слишком длинная строка\n");
            break;
        case OPEN_FILE_ERR:
            printf("Ошибка открытия файла\n");
            break;
        case ZERO_SIZE:
            printf("Размерность нулевая\n");
            break;
        case NO_MULT_MATRIXES:
            printf("Матрицы не умножаются\n");
            break;
        case MEM_ERROR:
            printf("Ошибка выделения памяти");
            break;
    }
}
