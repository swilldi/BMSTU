#ifndef APP_FUNCS_H__
#define APP_FUNCS_H__

#define MAX_ROWS 10
#define MAX_COLUNMS 10

// Ввод одномерного массива
int input_array(int *arr, size_t len);

// Вывод одномерного массива
void print_array(const int *arr, size_t len);

// Ввод двухмерного массива
int input_matrix(int (*matrix)[MAX_COLUNMS], size_t, size_t);

// Вывод двухмерного массива
void print_matrix(int (*matrix)[MAX_COLUNMS], size_t, size_t);
#endif
