#include "dynamic_matrix.h"
#include "exit_code.h"
#include "input_func.h"
#include "matrix_func.h"
#include <stdio.h>



void print_err_msg(int rc)
{
    switch (rc)
    {
        case INVALID_SIZE:
            printf("Введен недопустимый размер матрицы\n");
            break;
        case NEGATIVE_NUM: 
            printf("Введена отрицательная размерность матрицы\n");
            break;
        case INVALID_NUM:
            printf("Введен недопустимый символ для содержимого матрицы\n");
            break;
        case MEM_ERROR:
            printf("Ошибка выделения памяти\n"); 
            break;
    }
}

int min_size(size_t a, size_t b)
{
    if (a > b)
        return a;
    else
        return b;
}

int main(void)
{
    size_t m, n, p, q;
    matrix_t m_1, m_2;
    int rc;

    printf("Вветиде размерность матрицы 1: ");
    rc = input_matrix_size(&n, &m);
    if (rc != OK)
    {
        print_err_msg(rc);
    }

    m_1 = create_matrix(n, m);
    if (!m_1)
    {
        print_err_msg(MEM_ERROR);
        return MEM_ERROR;
    }

    printf("Ввод матрицы 1:\n");
    rc = input_matrix(m_1, n, m);
    if (rc != OK)
    {
        print_err_msg(MEM_ERROR);
        free_matrix(m_1);
        return rc;
    }

    printf("Вветиде размерность матрицы 2: ");
    rc = input_matrix_size(&p, &q);
    if (rc != OK)
    {
        print_err_msg(rc);
        free_matrix(m_1);
    }
    
    m_2 = create_matrix(p, q);
    if (!m_2)
    {
        print_err_msg(MEM_ERROR);
        free_matrix(m_1);
        return MEM_ERROR;
    }

    printf("Ввод матрицы 2:\n")
    rc = input_matrix(p, q);
    if (rc != OK)
    {
        print_err_msg(MEM_ERROR);
        free_matrix(m_1);
    }

    
    // приводим матрицы к квадратному виду
    size_t k = min_size(n, m), s = min_size(p, q);

    free_matrix(m_1);
    free_matrix(m_2);
    // приводим матрицы к единому размеру
    size_t z = min_size(k, s)

    // получаем степени для возведения матриц
    unsigned int degree_1, degree_2;
    printf("Введите степень для матрицы 1: ");
    rc = input_ulong(&degree_1);
    if (rc != OK)
    {
        print_err_msg(rc);
        return rc;
    }
    printf("Введите степень для матрицы 2: ")
    rc = input_ulong(&degree_2);
    if (rc != OK)
    {
        print_err_msg(rc);
        return rc;
    }

    

}
