#include "file_func.h"

// подсчет количества чисел
int count_nums(FILE *f, size_t *count)
{
    // переход к началу файла
    fseek(f, 0, SEEK_SET);
    
    int buff, rc;
    *count = 0;
    // подсчет цифр
    while ((rc = fscanf(f, "%d", &buff)) == 1)
        (*count)++;
    
    if (rc != EOF)
        return INVALID_FILE_CONTENT;
    else if (*count == 0)
        return EMPTY_ARR;

    return OK;
}

// чтение массива из файла
int read_array(FILE *f, int *pb, int *pe)
{
    // переход к началу файла
    fseek(f, 0, SEEK_SET);
    
    int rc = OK;
    for (int *pcur = pb; pcur != pe; pcur++)
    {
        rc = fscanf(f, "%d", pcur);
        if (rc != 1)
            break;
    }
    
    if (rc != EOF && rc != 1)
        return INVALID_FILE_CONTENT;
    
    return OK;
}

// запись массива в файл
void write_array(FILE *f, int *pb, int *pe)
{
    // переход к началу файла
    fseek(f, 0, SEEK_CUR);
    
    for (int *pcur = pb; pcur != pe; pcur++)
        fprintf(f, "%d ", *pcur);
}

bool file_is_empty(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    long start = ftell(f);

    fseek(f, 0, SEEK_END);

    return start != ftell(f);
}
