#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit_code.h"
#include "file_func.h"

#define FIELDS_IN_ITEM_T 3

bool is_empty_file(FILE *f)
{
    size_t pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t end = ftell(f);
    fseek(f, pos, SEEK_SET);
    return end == 0;
}

size_t count_line_in_file(FILE *f)
{
    // начальное положение в файле
    size_t pos = ftell(f);

    fseek(f, 0, SEEK_SET);
    size_t count = 0;

    // чтение всех строк в файле
    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        count += 1;
        s = getline(&str, &len, f);
    }
    free(str);

    // возвращение к начальному положению в файле
    fseek(f, pos, SEEK_SET);
    return count;
}

file_data_t *create_file_data(size_t n, size_t data_size)
{
    file_data_t *fdata = malloc(sizeof(file_data_t));
    if (fdata)
    {
        fdata->len = 0;
        fdata->data = malloc(n * data_size);
        if (!fdata->data)
        {
            free(fdata);
            fdata = NULL;
        }
    }

    return fdata;
}

void destroy_file_data(file_data_t *fdata, size_t data_size, free_content_ptr free_content)
{
    if (!fdata)
        return;
    for (size_t i = 0; i < fdata->len; i++)
    {
        free_content((char *)fdata->data + i * data_size);
    }
    free(fdata->data);
    free(fdata);
}

error read_file_data(FILE *f, file_data_t **fdata, read_func_ptr read_func, size_t data_size)
{
    error rc = OK;

    // количество структур в файле
    size_t line_count = count_line_in_file(f);
    if (line_count % FIELDS_IN_ITEM_T != 0)
        return INVALID_DATA;
    size_t values_count = line_count / FIELDS_IN_ITEM_T;

    // выделение памтия для хранения структур из файла
    *fdata = create_file_data(values_count, data_size);
    if (!fdata)
    {
        return MEMORY_ERR;
    }
    (*fdata)->len = 0;

    // чтение структур из файла
    for (size_t i = 0; i < values_count; i++)
    {
        rc = read_func(f, (char *)(*fdata)->data + i * data_size);
        if (rc != OK)
        {
            return rc;
        }
        (*fdata)->len += 1;
    }

    return rc;
}
