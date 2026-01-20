#include "io_func.h"
#include "matrix_func.h"
#include "stdio.h"

#include "matrix_func.h"
#include <stdbool.h>
#include <string.h>

void print_err_msg(error rc)
{
    switch (rc)
    {
        case ZERO_MATRIX:
            printf("Матрица вырожденная\n");
            break;
        case IO_ERR:
            printf("Ошибка ввода\n");
            break;
        case RANGE_ERR:
            printf("Неверный размер матриц\n");
            break;
        case FEW_ARGS_ERR:
            printf("Слишком мало арументов\n");
            break;
        case MANY_ARGS_ERR:
            printf("Слишком много аргументов\n");
            break;
        case INVALID_ACTION:
            printf("Некоректное действие\n");
            break;
        case NOT_REV_MATRIX:
            printf("Для матрцы не существует обратной\n");
            break;
        case FILE_OPEN_ERR:
            printf("Ошибка открытия файла\n");
            break;
        case FILE_EMPTY_ERR:
            printf("Файл пустой\n");
            break;
        case INVALID_SIZE:
            printf("Матрицы невозможно умножить/сложить\n");
            break;
        default:
            break;
    }
}
