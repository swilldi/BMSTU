#include <stdio.h>

#define N 20

#define OK 0
#define IO_ERROR 1
#define RANGE_ERROR 2

int find_row(int matr[][N], size_t n, size_t m, size_t k)
{
    int zero;
    for (size_t r = 0; r < n; r++)
    {
        zero = 0;
        for (size_t c = 0; c < m; c++)
        {
            if (matr[r][c] == 0)
            {
                zero++;
                if (zero == k)
                {
                    return r;
                }
            }
            else
            {
                zero = 0;
            }
        }
    }
    
    return -1;
}

int input_matr(int matr[][N], size_t n, size_t m)
{
    for (size_t r = 0; r < n; r++)
    {
        for (size_t c = 0; c < m; c++)
        {
            if (scanf("%d", &matr[r][c]) != 1)
            {
                return IO_ERROR;
            }
            if (!(matr[r][c] == 0 || matr[r][c] == 1))
            {
                return RANGE_ERROR;
            }
        }
    }
    return OK;
}

int main(void)
{
    size_t n, m;
    
    // ввод n
    if (scanf("%lu", &n) != 1)
    {
        printf("IO");
        return IO_ERROR;
    }
    if (n > N || n == 0)
    {
        printf("RANGE");
        return RANGE_ERROR;
    }
    
    // ввод m
    if (scanf("%lu", &m) != 1)
    {
        printf("IO");
        return IO_ERROR;
    }
    if (m > N || m == 0)
    {
        printf("RANGE");
        return RANGE_ERROR;
    }
    
    // ввод matr
    int matr[N][N];
    int rc = input_matr(matr, n, m);
    if (rc == IO_ERROR)
    {
        printf("IO");
        return IO_ERROR;
    }
    if (rc == RANGE_ERROR)
    {
        printf("RANGE");
        return RANGE_ERROR;
    }
    
    // ввод количества мест
    size_t k;
    if (scanf("%lu", &k) != 1)
    {
        printf("IO");
        return IO_ERROR;
    }
    if (k > m)
    {
        printf("RANGE");
        return RANGE_ERROR;
    }
    
    
    // поиск строки с местами
    int row = find_row(matr, n, m, k);
    if (row != -1)
    {
        printf("%d", row + 1);
    }
    else
    {
        printf("NOT FOUND");
    }
}

