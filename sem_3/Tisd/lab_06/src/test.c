#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "test.h"
#include "exit_code.h"
#include "array_t.h"
#include "tree.h"
#include "file_func.h"

char *paths[] = {
    "test_trees/tree_10_0.txt",
    "test_trees/tree_10_20.txt",
    "test_trees/tree_10_50.txt",
    "test_trees/tree_10_70.txt",
    "test_trees/tree_10_100.txt",
    "test_trees/tree_20_0.txt",
    "test_trees/tree_20_20.txt",
    "test_trees/tree_20_50.txt",
    "test_trees/tree_20_70.txt",
    "test_trees/tree_20_100.txt",
    "test_trees/tree_50_0.txt",
    "test_trees/tree_50_20.txt",
    "test_trees/tree_50_50.txt",
    "test_trees/tree_50_70.txt",
    "test_trees/tree_50_100.txt",
    "test_trees/tree_100_0.txt",
    "test_trees/tree_100_20.txt",
    "test_trees/tree_100_50.txt",
    "test_trees/tree_100_70.txt",
    "test_trees/tree_100_100.txt",
    "test_trees/tree_500_0.txt",
    "test_trees/tree_500_20.txt",
    "test_trees/tree_500_50.txt",
    "test_trees/tree_500_70.txt",
    "test_trees/tree_500_100.txt",
    "test_trees/tree_1000_0.txt",
    "test_trees/tree_1000_20.txt",
    "test_trees/tree_1000_50.txt",
    "test_trees/tree_1000_70.txt",
    "test_trees/tree_1000_100.txt",
    "test_trees/tree_5000_0.txt",
    "test_trees/tree_5000_20.txt",
    "test_trees/tree_5000_50.txt",
    "test_trees/tree_5000_70.txt",
    "test_trees/tree_5000_100.txt"
};


#define PRE_TEST_COUNT 10
#define TEST_COUNT 100

#include <time.h>

int sort_arr_test(FILE *f, array_t *arr, double *t)
{

    

    clock_t tm = 0;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        rewind(f);
        tree_node *tree = read_from_file_to_tree(f);
        tree_to_sort_array(tree, arr);
        arr->len = 0;
        tree_destroy(tree);
    }

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        clock_t start = clock();

        rewind(f);
        tree_node *tree = read_from_file_to_tree(f);
        tree_to_sort_array(tree, arr);

        clock_t end = clock();
        tree_destroy(tree);
        arr->len = 0;
        tm += end - start;
    }

    *t = (double)tm / CLOCKS_PER_SEC / TEST_COUNT * 1000.0;

    

    return OK;
}

int find_elem_test(tree_node *tree, char *elem, double *t)
{
    clock_t tm = 0;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        if (tree_lookup(tree, elem) == NULL)
            return 1;
        
    }

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        clock_t start = clock();
        tree_lookup(tree, elem);
        clock_t end = clock();
        tm += end - start;
    }

    *t = (double)tm / CLOCKS_PER_SEC / TEST_COUNT * 1000.0;

    return OK;
}


#define SEPARATOR_LINE "|-------------|-----------------------|----------|-----------------|\n"
int run_test(void)
{
    char buf[128];
    int rc;

    printf(
        "\nРезультаты сортировки данных при помощи дерева\n"
        SEPARATOR_LINE
        "|   Кол-во    | Соотношение элементов |  Высота  |  Время работы,  |\n"
        "|  элементов  |    левое / правое     |  дерева  |   милисекунды   |\n"
        SEPARATOR_LINE
    );
    for (size_t i = 0; i < sizeof(paths)/sizeof(paths[0]); i++)
    // for (size_t i = 0; i < 10; i++)
    {
        FILE *f = fopen(paths[i], "r");
        if (!f)
            return OPEN_FILE_ERROR;


        strcpy(buf, paths[i]);
        *(strchr(buf, '.')) = '\0';
        int n = -1, b = -1;

        char *str = strtok(buf, "_");
        while (str)
        {
            if (isdigit(str[0]))
            {
                if (n == -1)
                    n = atoi(str);
                else if (b == -1)
                    b = atoi(str);
            }
            str = strtok(NULL, "_");
        }

        
        tree_node *tree = read_from_file_to_tree(f);
        int h = tree_height(tree, 1);

        array_t *arr = calloc(1, sizeof(array_t));
        arr->data = malloc(n * sizeof(char*));

        double sort_time = 0;
        sort_arr_test(f, arr, &sort_time);

        fclose(f);

        free(arr->data);
        free(arr);

        printf("| %11d | %17d/%3d | %8d | %15lf |\n", n, b, 100 - b, h, sort_time);
        if (b == 100)
            printf(SEPARATOR_LINE);

        

    }

    printf(
        "\n\n"
        "Результаты поиска максимального элемента\n"
        SEPARATOR_LINE
        "|   Кол-во    | Соотношение элементов |  Высота  |  Время работы,  |\n"
        "|  элементов  |    левое / правое     |  дерева  |   милисекунды   |\n"
        SEPARATOR_LINE
    );
    for (size_t i = 0; i < sizeof(paths)/sizeof(paths[0]); i++)
    // for (size_t i = 0; i < 10; i++)
    {
        FILE *f = fopen(paths[i], "r");
        if (!f)
            return OPEN_FILE_ERROR;

        tree_node *tree = read_from_file_to_tree(f);
        int h = tree_height(tree, 1);

        strcpy(buf, paths[i]);
        *(strchr(buf, '.')) = '\0';
        int n = -1, b = -1;

        char *str = strtok(buf, "_");
        while (str)
        {
            if (isdigit(str[0]))
            {
                if (n == -1)
                    n = atoi(str);
                else if (b == -1)
                    b = atoi(str);
            }
            str = strtok(NULL, "_");
        }


        double find_time = 0;
        char find_str[128];
        sprintf(find_str, "str%d", n);
        rc = find_elem_test(tree, find_str, &find_time);
        if (rc != OK)
        {
            return rc;
        }


        printf("| %11d | %17d/%3d | %8d | %15lf |\n", n, b, 100 - b, h, find_time);
        if (b == 100)
            printf(SEPARATOR_LINE);

    }


    return OK;
}
