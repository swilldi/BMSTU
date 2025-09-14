#ifndef APP_FUNCS_H
#define APP_FUNCS_H

#define MAX_ROWS 10
#define MAX_COLUNMS 10

// Вывод одномерного массива
void print_array(const int *arr, size_t len);

// Вывод двухмерного массива
void print_matrix(int (*matrix)[MAX_COLUNMS], size_t, size_t);
#endif
