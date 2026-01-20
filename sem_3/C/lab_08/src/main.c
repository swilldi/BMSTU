#include "dynamic_matrix.h"
#include "exit_code.h"
#include "file_func.h"
#include "input_func.h"
#include "io_func.h"
#include "matrix_func.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    MULT,
    SUM,
    INVERS
} action_t;

int main(int argc, char **argv)
{
    FILE *f;
    size_t m, n, p, q;
    matrix_t mtr_1 = NULL;
    matrix_t mtr_2 = NULL;
    matrix_t res_mtr = NULL;
    int rc;

    if (argc < 2)
    {
        rc = FEW_ARGS_ERR;
        print_err_msg(rc);
        return rc;
    }

    action_t cmd;
    if (strcmp(argv[1], "o") == 0)
    {
        cmd = INVERS;
    }
    else if (strcmp(argv[1], "a") == 0)
    {
        cmd = SUM;
    }
    else if (strcmp(argv[1], "m") == 0)
    {
        cmd = MULT;
    }
    else
    {
        rc = INVALID_ACTION;
        print_err_msg(rc);
        return rc;
    }

    if (((cmd == SUM || cmd == MULT) && argc < 5) || (cmd == INVERS && argc < 4))
    {
        rc = FEW_ARGS_ERR;
        print_err_msg(rc);
        return rc;
    }
    if (((cmd == SUM || cmd == MULT) && argc > 5) || (cmd == INVERS && argc > 4))
    {
        rc = MANY_ARGS_ERR;
        print_err_msg(rc);
        return rc;
    }

    if (cmd == INVERS)
    {
        // открытие файла с матрицей
        f = fopen(argv[2], "r");
        rc = check_file(f);
        if (rc != OK)
        {
            if (rc != FILE_OPEN_ERR)
            {
                fclose(f);
            }
            print_err_msg(rc);
            return rc;
        }

        // чтение матрицы из файла
        rc = read_full_matrix(f, &mtr_1, &n, &m);
        if (rc != OK)
        {
            fclose(f);
            print_err_msg(rc);
            return rc;
        }

        fclose(f);
        
        if (n != m)
        {
            rc = NOT_REV_MATRIX;
            free_matrix(mtr_1);
            print_err_msg(rc);

            return rc;
        }

        // получение обратной матрицы
        rc = inverse_matrix(&res_mtr, mtr_1, n);
        if (rc != OK)
        {
            print_err_msg(rc);
            free_matrix(mtr_1);
            return rc;
        }

        // запись результата в файл
        f = fopen(argv[3], "w");
        if (!f)
        {
            rc = FILE_OPEN_ERR;

            print_err_msg(rc);
            free_matrix(mtr_1);
            free_matrix(res_mtr);
            return rc;
        }

        write_matrix(f, res_mtr, n, m);
        free_matrix(mtr_1);
        free_matrix(res_mtr);
        fclose(f);
    }
    else
    {
        // заполнение 1-й матрицы
        f = fopen(argv[2], "r");
        rc = check_file(f);
        if (rc != OK)
        {
            if (rc != FILE_OPEN_ERR)
            {
                fclose(f);
            }

            print_err_msg(rc);
            return rc;
        }

        rc = read_full_matrix(f, &mtr_1, &n, &m);
        if (rc != OK)
        {
            print_err_msg(rc);
            fclose(f);
            return rc;
        }

        fclose(f);

        // заполнение 2-й матрицы
        f = fopen(argv[3], "r");
        rc = check_file(f);
        if (rc != OK)
        {
            if (rc != FILE_OPEN_ERR)
            {
                fclose(f);
            }

            free_matrix(mtr_1);
            print_err_msg(rc);
            return rc;
        }

        rc = read_full_matrix(f, &mtr_2, &p, &q);
        if (rc != OK)
        {
            fclose(f);
            free_matrix(mtr_1);
            print_err_msg(rc);
            return rc;
        }

        fclose(f);

        // выполнение операции
        if (cmd == SUM)
        {
            if (n != p || m != q)
            {
                rc = INVALID_SIZE;
                print_err_msg(rc);
                free_matrix(mtr_1);
                free_matrix(mtr_2);
                return rc;
            }

            rc = sum_matrix(&res_mtr, mtr_1, mtr_2, n, m);
            if (rc != OK)
            {
                print_err_msg(rc);
                free_matrix(mtr_1);
                free_matrix(mtr_2);
                return rc;
            }
        }
        else if (cmd == MULT)
        {
            if (m != p)
            {
                rc = INVALID_SIZE;
                print_err_msg(rc);
                free_matrix(mtr_1);
                free_matrix(mtr_2);
                return rc;
            }

            rc = mult_matrix(&res_mtr, mtr_1, mtr_2, n, m, q);
            if (rc != OK)
            {
                print_err_msg(rc);
                free_matrix(mtr_1);
                free_matrix(mtr_2);
                return rc;
            }
        }

        f = fopen(argv[4], "w");
        if (!f)
        {
            rc = FILE_OPEN_ERR;
            print_err_msg(rc);
            free_matrix(mtr_1);
            free_matrix(mtr_2);
            free_matrix(res_mtr);
            return rc;
        }

        write_matrix(f, res_mtr, n, q);
        free_matrix(mtr_1);
        free_matrix(mtr_2);
        free_matrix(res_mtr);
        fclose(f);
    }
}
