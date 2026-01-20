#define _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit_code.h"
#include "item.h"

// char *input_str(char *msg)
// {
//     if (msg)
//         printf("%s", msg);

// }

void free_content_item(void *value)
{
    item_t *item = value;
    free(item->title);
}

error read_item(FILE *f, void *data)
{
    item_t *item = data;

    size_t len = 0;
    char *line = NULL;
    ssize_t s;

    // ------ title ------
    s = getline(&line, &len, f);
    if (s == -1)
        return INVALID_INPUT;

    if (s <= 1)
    {
        free(line);
        return EMPTY_STR;
    }

    if (line[s - 1] == '\n')
        line[s - 1] = '\0';

    item->title = strdup(line);

    s = getline(&line, &len, f);
    if (s == -1)
    {
        free(item->title);
        free(line);
        return INVALID_INPUT;
    }

    if (sscanf(line, "%d", &item->prise) != 1 || item->prise < 0)
    {
        free(item->title);
        free(line);
        return INVALID_INPUT;
    }

    s = getline(&line, &len, f);
    if (s == -1)
    {
        free(item->title);
        free(line);
        return INVALID_INPUT;
    }

    if (sscanf(line, "%f", &item->weight) != 1 || item->weight < 0)
    {
        free(item->title);
        free(line);
        return INVALID_INPUT;
    }

    free(line);
    return OK;
}

void write_item(FILE *f, void *data)
{
    item_t *item = data;
    fprintf(f, "%s\n%d\n%.2f\n", item->title, item->prise, item->weight);
}
