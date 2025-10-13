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
#include "enums.h"
#include "test.h"

#include <stdio.h>


int main(void)
{
    size_m n = 0, m, p = 0, q;
    int cmd;
    
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    matrix_t m_csr = { 0 }, m_csc = { 0 }, res = { 0 };
    method_input_matrix input_method = NULL;
    

    int rc;
    char path[PATH_LEN];
    FILE *f = NULL;
    
    #ifndef FUNC_OUT
    print_input_cmd_list();
    printf("Введите номер команды: ");
    #endif 

    rc = input_command(&cmd, INPUT);
    if (rc != OK)
        return rc;

    // Ввод классическим способом илил координатным
    if (cmd == CLASSIC_INPUT || cmd == CLASSIC_FILE)
        input_method = input_matrix_classic;
    else if (cmd == COORD_INPUT || cmd == COORD_FILE)
        input_method = input_matrix_coord;
    
    // Ввод из файла или из консоли
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


    if (cmd == COMPARE)
    {
        start_testa();
        return rc;
    }
    
    // ввод матриц
    rc = input_matrix(&m_1, &n, &m, f, input_method);
    if (rc != OK)
        return rc;
    
    // print_matrix(m_1, n, m);
    
    rc = input_matrix(&m_2, &p, &q, f, input_method);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        return rc;
    }

    // преобразование матриц к сжатому виду
    rc = matrix_to_csr(&m_csr, m_1, n, m);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        return rc;
    }

    rc = matrix_to_csc(&m_csc, m_2, p, q);
    if (rc != OK)
    {
        free_matrix_razr(&m_csr);
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        return rc;
    }

    // умножение матриц
    rc = mult_csr_by_csc(&res, &m_csr, &m_csc);
    if (rc != OK)
    {
        free_matrix_razr(&m_csr);
        free_matrix_razr(&m_csc);
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        return rc;
    }

    // Ввод для типа выводма матрицы
    #ifndef FUNC_OUT 
    print_output_cmd_list();
    #endif

    rc = input_command(&cmd, OUTPUT);
    if (rc != OK)
    {
        free_matrix_razr(&res);
        free_matrix_razr(&m_csr);
        free_matrix_razr(&m_csc);
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        return rc;
    }

    // вывод матрицы
    switch (cmd)
    {
        case MATRIX:
            print_csr_matrix(&res);
            break;
        case COORD:
            print_csr_coord(&res);
            break;
        case CSR:
            print_razr_debug(&res);
            break;
    }
    
    free_matrix_razr(&res);
    free_matrix_razr(&m_csr);
    free_matrix_razr(&m_csc);
    free_matrix(&m_1, n);
    free_matrix(&m_2, p);

    return OK;
}
