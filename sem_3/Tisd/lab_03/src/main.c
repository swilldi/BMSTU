/* 
- координатный ввод матрицы
- классический ввод матрицы

- матрица в файле класическое
- матрица в файле координатный

- классический вывод матрицы
- CSR/CSС вывод матрицы

- Умножение матриц 

*/

#include "input_func.h"
#include "output_func.h"
#include "dynamic_mem.h"
#include "matrix_struct.h"
#include "exit_code.h"
#include "matrix_func.h"

#include <stdio.h>

typedef enum
{
    CLASSIC_INPUT = 1,
    COORD_INPUT,
    CLASSIC_FILE,
    COORD_FILE,
    COMPARE
} command_t;
#define COMMAND_MAX COMPARE

void print_command_list(void)
{
    printf(
        "1. Классический ввод\n"
        "2. Координатный ввод\n"
        "3. Классический файл\n"
        "4. Координатный файл\n"
        "5. Сравнение\n"
    );
}

int input_command(command_t *cmd)
{
    if (scanf("%d", cmd) != 1)
        return INVALID_INPUT;
    
    if (*cmd < 0 || *cmd > COMMAND_MAX)
        return CMD_RANGE_ERR;

    return OK;
}

int main(void)
{
    // size_m n, m, p, q;
    size_m n = 0, m, p = 0, q;
    command_t cmd;
    
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    matrix_t m_csr, m_csc, res;
    method_input_matrix input_method = NULL;
    

    int rc;
    char path[PATH_LEN];
    FILE *f = NULL;
    
    #ifndef FUNC_OUT
    print_command_list();
    printf("Введите номер команды: ");
    #endif 

    rc = input_command(&cmd);
    if (rc != OK)
        return rc;

    if (cmd == CLASSIC_INPUT || cmd == CLASSIC_FILE)
        input_method = input_matrix_classic;
    else if (cmd == COORD_INPUT || cmd == COORD_FILE)
        input_method = input_matrix_coord;
    
    if (cmd == CLASSIC_INPUT || cmd == COORD_INPUT)
    {
        f = stdin;
    }
    else if (cmd == CLASSIC_FILE || cmd == COORD_FILE)
    {
        #ifndef FUNC_OUT
        printf("Введите путь к файлу: ");
        #endif
        rc = input_str(path, PATH_LEN, stdin);
        if (rc != OK)
            return rc;
     
        // открытие файла
        f = fopen(path, "r");
        if (!f)
        {
            rc = OPEN_FILE_ERR;
            return rc;
        }
    }


    switch (cmd)
    {
        case COMPARE:
            // будут выполняться замеры времени и памяти
            break;
        default:
            // ввод первой матрицы
            rc = input_matrix(&m_1, &n, &m, f, input_method);
            if (rc != OK)
                break;

            // printf("M_1:\n");
            // print_matrix(m_1, n, m);
            // printf("\n");
            
            rc = matrix_to_csr(&m_csr, m_1, n, m);
            if (rc != OK)
                break;
            
            // ввод второй матрицы
            rc = input_matrix(&m_2, &p, &q, f, input_method);
            if (rc != OK)
                break;
            
            // printf("M_2:\n");
            // print_matrix(m_2, p, q);
            // printf("\n");

            rc = matrix_to_csc(&m_csc, m_2, p, q);
            if (rc != OK)
                break;
            
            rc = mult_csr_by_csc(&res, &m_csr, &m_csc); 
            if (rc != OK)
                break;
            
            // print_razr_debug(&m_csr);
            // printf("\n");
            // print_razr_debug(&m_csc);
            // printf("\n");
            // print_razr_debug(&res);
            
            // print_csr_matrix(&res);
            // printf("\n");
            print_csr_coord(&res);
            // printf("\n");
            // print_razr_debug(&res);
            break;
    }    

    free_matrix_razr(&res);
    free_matrix_razr(&m_csr);
    free_matrix_razr(&m_csc);

    free_matrix(&m_1, n);
    free_matrix(&m_2, p);
    if (f != stdin && f)
        fclose(f); // норм реагирует на NULL???
    
    return rc;
}
