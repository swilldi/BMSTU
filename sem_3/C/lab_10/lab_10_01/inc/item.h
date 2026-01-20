#ifndef ITEM_H__
#define ITEM_H__

#include <stdio.h>

#include "exit_code.h"

#define FIELDS_IN_ITEM_T 3
typedef struct
{
    char *title;
    int prise;
    float weight;
} item_t;

error read_item(FILE *f, void *data);
void write_item(FILE *f, void *data);
void free_content_item(void *value);

#endif
