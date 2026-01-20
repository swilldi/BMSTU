#include "file_func.h"
#include "errors_code.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 1000

// записать числа в файл
int get_number_by_pos(FILE *f, int n)
{
    int num;
    fseek(f, n * sizeof(int), SEEK_SET);
    fread(&num, sizeof(int), 1, f);

    return num;
}

// полчение числа из файла
void put_number_by_pos(FILE *f, int num, int i)
{
    fseek(f, i * sizeof(int), SEEK_SET);
    fwrite(&num, sizeof(int), 1, f);
}

// вывести содержимое файла
void print_content(FILE *f)
{
    fseek(f, 0, SEEK_END);
    int count = ftell(f) / sizeof(int);
    int num;
    // rewind(f);
    for (int i = 0; i < count; i++)
    {
        num = get_number_by_pos(f, i);
        printf("%d\n", num);
    }
}

// сортировать содержимое файла
void sort_file(FILE *f)
{
    fseek(f, 0, SEEK_END);
    size_t count = ftell(f) / sizeof(int);

    for (size_t i = 0; i < count - 1; i++)
    {
        int min = get_number_by_pos(f, i);
        size_t min_ind = i;
        for (size_t j = i + 1; j < count; j++)
        {
            int cur = get_number_by_pos(f, j);
            if (cur < min)
            {
                min = cur;
                min_ind = j;
            }
        }

        if (min_ind != i)
        {
            int memory_num = get_number_by_pos(f, i);
            put_number_by_pos(f, min, i);
            put_number_by_pos(f, memory_num, min_ind);
        }
    }
}

// создание файла со случайными числами от -1000 до 1000
void create_random_file(FILE *f, int n)
{
    int rand_num = 0;
    int is_negative = 0;
    for (int i = 0; i < n; i++)
    {
        rand_num = rand() % MAX_NUM;
        is_negative = rand() % 2;

        if (is_negative)
        {
            rand_num *= -1;
        }

        put_number_by_pos(f, rand_num, i);
    }
}

// перенос содержимого из bin файла в txt
void bin_to_txt(FILE *bin_f, FILE *txt_f)
{
    fseek(bin_f, 0, SEEK_END);
    int count = ftell(bin_f) / sizeof(int);

    for (int i = 0; i < count; i++)
    {
        fprintf(txt_f, "%d\n", get_number_by_pos(bin_f, i));
    }
}

// перенос содержимого из txt файла в bin
int txt_to_bin(FILE *txt_f, FILE *bin_f)
{
    int num, count = 0;
    int rc = fscanf(txt_f, "%d", &num);
    while (rc == 1)
    {
        // printf("%d (%d)\n", num, count);
        put_number_by_pos(bin_f, num, count);
        count++;
        rc = fscanf(txt_f, "%d", &num);
    }

    if (rc == EOF && feof(txt_f))
        return OK;
    else
        return INVALID_CONTENT;
}

int is_empty(FILE *f)
{
    fseek(f, 0, SEEK_END);

    // // printf("\n%ld\n", ftell(f));
    if (ftell(f) == 0)
    {
        return 1;
    }
    rewind(f);
    return OK;
}

int check_content(FILE *f)
{
    fseek(f, 0, SEEK_END);
    int k = ftell(f);
    rewind(f);
    // printf("%d\n", k);

    if (k % sizeof(int) == 0)
        return 0;
    else
        return 1;
}
