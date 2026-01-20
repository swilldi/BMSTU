#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#include <stdio.h>

// записать числа в файл
int get_number_by_pos(FILE *f, int n);
// полчение числа из файла
void put_number_by_pos(FILE *f, int num, int i);
// вывести содержимое файла
void print_content(FILE *f);
// сортировать содержимое файла
void sort_file(FILE *f);
// создание файла со случайными числами от -1000 до 1000
void create_random_file(FILE *f, int n);
// перенос содержимого из bin файла в txt
void bin_to_txt(FILE *bin_f, FILE *txt_f);
// перенос содержимого из txt файла в bin
int txt_to_bin(FILE *txt_f, FILE *bin_f);

// проверка файла на пустоту
int is_empty(FILE *f);
// проверка файла на содрежимое
int check_content(FILE *f);

#endif
