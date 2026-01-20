#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#define GNU_SOURCE_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "exit_code.h"

typedef error (*read_func_ptr)(FILE *, void *);
typedef void (*free_content_ptr)(void *);

typedef struct
{
    size_t len;
    void *data;
} file_data_t;

error read_file_data(FILE *f, file_data_t **fdata, read_func_ptr read_func, size_t data_size);
bool is_empty_file(FILE *f);
size_t count_line_in_file(FILE *f);

file_data_t *create_file_data(size_t n, size_t data_size);
void destroy_file_data(file_data_t *fdata, size_t data_size, free_content_ptr free_content);

#endif
