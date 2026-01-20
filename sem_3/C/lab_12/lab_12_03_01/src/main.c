#include "arr_func.h"
#include "exit_code.h"
#include "file_func.h"
#include "io_func.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>


typedef int (*key_ptr)(const int*, const int*, int*, int*);
typedef int* (*find_elem_ptr)(const int*, const int*);
typedef void (*rename_arr_ptr)(int **p_oab, int **p_oae, int **p_nab, int **p_nae);
typedef bool (*arr_check_ptr)(const int*, const int*);
typedef int (*arr_create_ptr)(size_t, int**, int**);


void print_arr(int *pb, int *pe)
{
    for (; pb < pe; pb++)
        printf("%d ", *pb);
    printf("\n");
}


bool validate_key(char *key)
{
    return strlen(key) == 1 && *key == 'f';
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return TOO_FEW_ARGS;
    else if (argc > 4)
        return TOO_MUCH_ARGS;

    bool key_is_valid = false;
    if (argc == 4)
    {
        key_is_valid = validate_key(argv[3]);
    }
    if (argc == 4 && !key_is_valid)
    {
        print_err_msg(INVALID_ARGS);
        return INVALID_ARGS;
    }

    // открывам файл и считаем кол-во чисел
    int rc;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        print_err_msg(OPEN_FILE_ERROR);
        return OPEN_FILE_ERROR;
    }

    size_t count;
    rc = count_nums(f, &count);
    if (rc != OK)
    {
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    if (count == 0)
    {
        fclose(f);
        print_err_msg(EMPTY_ARR);
        return EMPTY_ARR;
    }

    // Включений функций из библиотеки
    void *arr_lib = dlopen("./lib/libarr_func.so", RTLD_NOW);
    if (!arr_lib)
    {
        printf("Cannot open library. %s\n", dlerror());
        fclose(f);
        return LIB_OPEN_ERR;
    }

    arr_create_ptr create_arr = (arr_create_ptr)dlsym(arr_lib, "create_arr");
    if (!create_arr)
    {
        printf("Can not load function. %s\n", dlerror());
        fclose(f);
        dlclose(arr_lib);
        return LOAD_FUNC_ERR;
    }
    

    int *arr_b = NULL, *arr_e;
    rc = create_arr(count, &arr_b, &arr_e);
    if (rc != OK)
    {
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    // читаем данные в файл
    rc = read_array(f, arr_b, arr_e);
    if (rc != OK)
    {
        free(arr_b);
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    fclose(f);

    print_arr(arr_b, arr_e);

    // если есть ключ, выполнить фильтрацию
    if (argc > 3 && key_is_valid)
    {        
        // Загрузка функций
        find_elem_ptr arr_last_neg = (find_elem_ptr)dlsym(arr_lib, "arr_last_neg");
        if (!arr_last_neg)
        {
            printf("Can not load function. %s\n", dlerror());
            free(arr_b);
            dlclose(arr_lib);
            return LOAD_FUNC_ERR;
        }
        key_ptr key = (key_ptr)dlsym(arr_lib, "key");
        if (!key)
        {
            printf("Can not load function. %s\n", dlerror());
            free(arr_b);
            dlclose(arr_lib);
            return LOAD_FUNC_ERR;
        }
        rename_arr_ptr rename_arr = (rename_arr_ptr)dlsym(arr_lib, "rename_arr");
        if (!rename_arr)
        {
            printf("Can not load function. %s\n", dlerror());
            free(arr_b);
            dlclose(arr_lib);
            return LOAD_FUNC_ERR;
        }

        // Выделение памяти для отфильтрованного массива
        int *p_fab = NULL, *p_fae = NULL;
        const int* last_neg = arr_last_neg(arr_b, arr_e);
        printf("%d\n", *last_neg);
        size_t len = last_neg - arr_b;
        rc = create_arr(len, &p_fab, &p_fae);
        if (rc != OK)
        {
            free(arr_b);
            arr_b = NULL;
            print_err_msg(rc);
            return rc;
        }

        // запись отфильтрованного массива
        rc = key(arr_b, arr_e, p_fab, p_fae);
        if (rc != OK)
        {
            free(arr_b);
            free(p_fab);
            arr_b = NULL;
            print_err_msg(rc);
            return rc;
        }

        rename_arr(&arr_b, &arr_e, &p_fab, &p_fae);
        count = arr_e - arr_b;
    }

    print_arr(arr_b, arr_e);

    // закрытие библиотеки
    dlclose(arr_lib);

    // сортировка
    mysort(arr_b, count, sizeof(int), cmp_int);

    // запись в файл
    f = fopen(argv[2], "w");
    write_array(f, arr_b, arr_e);

    // очишение памяти
    fclose(f);
    free(arr_b);
    arr_b = NULL;
}


