#include "exit_code.h"
#include "matrix_struct.h"
#include "dynamic_mem.h"
#include "stdio.h"
#include <string.h>
#include "input_func.h"

int input_command(int *cmd, command_t type)
{
    if (scanf("%d", cmd) != 1)
        return INVALID_INPUT;
    
    if (*cmd < 0)
        return CMD_RANGE_ERR;

    if (type == INPUT && *cmd > INPUT_CMD_MAX)
        return CMD_RANGE_ERR;
    else if (type == OUTPUT && *cmd > OUTPUT_CMD_MAX)
        return CMD_RANGE_ERR;

    return OK;
}


int input_size(size_m *num, FILE *f)
{
    long buff;
    int rc = fscanf(f, "%ld", &buff);
    
    if (rc == EOF)
        return END_INPUT;
    else if (rc != 1)
        return INVALID_INPUT;

    if (buff < 0)
        return NEGATIVE_SIZE;

    *num = (size_m)buff;
    return OK;
}

int input_num(int *num, FILE *f)
{    
    int rc = fscanf(f, "%d", num);
    
    if (rc == EOF)
        return END_INPUT;
    else if (rc != 1)
        return INVALID_INPUT;

    return OK;
}

int input_str(char *str, size_t max_len, FILE *f)
{
    char buff[BUFF_LEN];
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (!fgets(buff, BUFF_LEN - 2, f))
        return INVALID_INPUT;
    
    size_t l = strlen(buff);
    if (l >= max_len)
        return STR_OVERFLOW;
    
    if (l > 0 && buff[l - 1] == '\n')
        buff[--l] = '\0';
    
    strcpy(str, buff);

    return OK;
}

// ввод размерностей матрицы
int input_matrix_sizes(size_m *n, size_m *m, FILE *f)
{
    int rc;

    #ifndef FUNC_OUT
    if (f == stdin)
        printf("Введите n: ");
    #endif

    rc = input_size(n, f);
    if (rc != OK)
        return rc;
    if (*n == 0)
        return ZERO_SIZE;
    
    #ifndef FUNC_OUT
    if (f == stdin)
        printf("Введите m: ");
    #endif

    rc = input_size(m, f);
    if (rc != OK)
        return rc;
    if (*m == 0)
        return ZERO_SIZE;
    
    return OK;
}

int input_matrix(matrix_data_t *matrix, size_m *n, size_m *m, FILE *f, method_input_matrix input_func)
{
    int rc;
    rc = input_matrix_sizes(n, m, f);
    if (rc != OK)
        return rc;

    // ввод матрицы
    *matrix = create_matrix(*n, *m);
    if (!*matrix)
        return MEM_ERROR;
    
    rc = input_func(*matrix, *n, *m, f);
    if (rc != OK)
        return rc;
    
    return OK;
}

int input_matrix_classic(matrix_data_t matrix, size_m n, size_m m, FILE *f)
{
    int rc;
    
    #ifndef FUNC_OUT
    printf("Вводите матрицу: \n");
    #endif

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            rc = input_num(&matrix[i][j], f);
            if (rc != OK)
            {
                return rc;
            }
        }
    }

    return OK; 
}

#include <ctype.h>

int input_matrix_coord(matrix_data_t matrix, size_m n, size_m m, FILE *f)
{
    // int rc;
    char buff[BUFF_LEN];
    size_m i, j;
    int num;
    size_t count = 0, max_count = n * m;
    // вот это надо тестить реально
    // очистка stdin
    int c;
    while ((c = fgetc(f)) != '\n' && c != EOF);

    while (fgets(buff, sizeof(buff), f))
    {
        if (buff[0] == '\n')
            break;

        if (sscanf(buff, "%u %u %d", &i, &j, &num) != 3)
            return INVALID_INPUT;

        if (i > n || j > m || i <= 0 || j <= 0) 
            return MATR_RANGE_ERR;
        
        if (count >= max_count)
            return MATRIX_OVERFLOW;

        matrix[i - 1][j - 1] = num;
        count++;
    }

    return OK; 
}

