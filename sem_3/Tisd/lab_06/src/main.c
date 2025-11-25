#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "tree.h"
#include "list.h"
#include "file_func.h"
#include "enums.h"
#include "exit_code.h"
#include "output_func.h"
#include "input_func.h"

#include "test.h"


#define TREE_DOT "tree.dot"
#define TREE_PNG "tree.png"

#define PRE_TEST_COUNT 10
#define TEST_COUNT 20

double tree_time_test(FILE *f, char tmp_char)
{
    rewind(f);
    clock_t start, end;
    double res = 0;

    tree_node *tmp_tree = read_from_file_to_tree(f);
    if (!tmp_tree)
        return -1;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        node_t *tmp_list_point = NULL;
        tree_find_by_first_symbol_all(tmp_tree, &tmp_list_point, tmp_char);
        destroy_list(tmp_list_point);
    }

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        node_t *tmp_list_point = NULL;
        start = clock();
        tree_find_by_first_symbol_all(tmp_tree, &tmp_list_point, tmp_char);
        end = clock();
        res += (double)(end - start);
        destroy_list(tmp_list_point);
        
    }

    tree_destroy(tmp_tree);

    return res / CLOCKS_PER_SEC / TEST_COUNT;
}

double file_time_test(FILE *f, char tmp_char)
{
    rewind(f);
    node_t *tmp_list = NULL;
    clock_t start, end;
    double res = 0;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        rewind(f);
        tmp_list = read_from_file_by_letter(f, tmp_char);
        destroy_list(tmp_list);
    }

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        rewind(f);
        start = clock();
        tmp_list = read_from_file_by_letter(f, tmp_char);
        end = clock();
        res += (double)(end - start);
        destroy_list(tmp_list);
    }

    return res / CLOCKS_PER_SEC / TEST_COUNT;
}


int is_empty_file(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    size_t start = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t end = ftell(f);
    fseek(f, 0, SEEK_SET);

    return end == start;

}

int cmp_tree_files_search_time(char tmp_char)
{
    char *paths[STR_LEN] = 
    {
        "./test_tree_cmp_file/test_10.txt",
        "./test_tree_cmp_file/test_100.txt",
        "./test_tree_cmp_file/test_500.txt",
        "./test_tree_cmp_file/test_5000.txt",
        "./test_tree_cmp_file/test_10000.txt",
        "./test_tree_cmp_file/test_50000.txt",
        "./test_tree_cmp_file/test_100000.txt",
        "./test_tree_cmp_file/test_1000000.txt",
        "./test_tree_cmp_file/test_3000000.txt"
    };
    int elem_count[] = { 10, 100, 500, 5000, 10000, 50000, 100000, 1000000, 3000000 };

    printf(
        "|------------|-------------------------|--------------------|-----------------|\n"
        "|   Кол-во   |    Время работы, сек    | Память для дерева, | Дерево быстрее, |\n"
        "|  элементов |------------|------------|        байт        |  чем файла на   |\n"
        "|            |   Дерево   |    Файл    |                    |                 |\n"
        "|------------|------------|------------|--------------------|-----------------|\n"
    );
    for (size_t i = 0; i < sizeof(elem_count) / sizeof(int); i++)
    {
        FILE *f = fopen(paths[i], "r");
        if (!f)
            return OPEN_FILE_ERROR;
        
        double file_time = file_time_test(f, tmp_char);
        double tree_time = tree_time_test(f, tmp_char);
        double time_percent = (file_time - tree_time) / file_time * 100;

        printf(
            "| %10d | %10lf | %10lf | %18lu | %14.2lf%% |\n", 
            elem_count[i], tree_time, file_time, sizeof(tree_node) * elem_count[i], time_percent
        );
        fclose(f);
    }
    printf("|------------|------------|------------|--------------------|-----------------|\n");
    return OK;
}



void print_tree_node(tree_node *tree, void(*tree_apply)(tree_node*, ptr_action_t, void*), char *msg)
{
    node_t *list = NULL;
    tree_apply(tree, tree_add_to_list, &list);
    printf("\n%s\n", msg);
    print_list(list);
    destroy_list(list);
}


int main(void)
{

    int rc = OK;
    int cmd;

    tree_node *tree = NULL;

    tree_node *tmp_node = NULL;
    node_t *point_list = NULL; 
    char tmp_str[STR_LEN];
    char tmp_char;
    FILE *f;

    #ifndef FUNC_OUT
    print_prog_mode_list();
    #endif

    rc = input_cmd(&cmd, MAX_PROG_MODE);
    if (rc != OK)
    {
        return rc;
    }

    if (cmd == RUN_TESTS)
    {
        rc = run_test();
        print_err_msg(rc);
        return rc;
    }
    else if (cmd == TEST_TREE_FILES)
    {
        rc = input_char(&tmp_char); 
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        rc = cmp_tree_files_search_time(tmp_char);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        return rc;
                
    }
    else if (cmd == EXIT)
    {
        return rc;
    }

    #ifndef FUNC_OUT
    print_action_cmd_list();
    #endif
    while (cmd != EXIT)
    {
        rc = input_cmd(&cmd, MAX_ACTION_CMD);
        if (rc != OK)
        {

            cmd = CONTINUE;
        }

        switch (cmd)
        {
            case ADD:
                rc = input_str(tmp_str, NULL);
                if (rc != OK)
                    break;

                if (tree_lookup(tree, tmp_str) != NULL)
                {
                    rc = VALUE_ALREADY_IN_TREE;
                    break;
                }
                
                tmp_node = tree_node_create(tmp_str);
                if (!tmp_node)
                {
                    rc = MEMORY_ERROR;
                    break;
                }

                tree = tree_insert(tree, tmp_node);
                break;

            case DEL:
                rc = input_str(tmp_str, NULL);
                if (rc != OK)
                    break;

                if (tree_lookup(tree, tmp_str) == NULL)
                {
                    rc = VALUE_NOT_IN_TREE;
                    break;
                }

                // tree = tree_insert(tree, tmp_node);
                tree = tree_remove(tree, tmp_str);
                break;

            case COUNT_BY_LETTER:
                rc = input_char(&tmp_char);
                if (rc != OK)
                    break;

                destroy_list(point_list);
                point_list = NULL;

                int count = tree_lookup_count(tree, tmp_char);
                printf("В %d вершинах строки начинаются с \"%c\"\n", count, tmp_char);
                break;

            case CMP_TREE_AND_FILE:
                rc = input_str(tmp_str, "Введите файл: ");
                if (rc != OK)
                    break;
                
                f = fopen(tmp_str, "r");
                if (!f)
                {
                    rc = OPEN_FILE_ERROR;
                    break;
                }
                if (is_empty_file(f))
                {
                    rc = EMPTY_FILE;
                    break;
                }

                rc = input_char(&tmp_char); 
                if (rc != OK)
                    break;

                double tree_time = tree_time_test(f, tmp_char), file_time = file_time_test(f, tmp_char);

                printf("Время для поиска в\nВ дереве: %.6f сек.\nВ файле:  %.6f сек.\n", tree_time, file_time);

                fclose(f);

                break;
            
            case READ_TREE:
                rc = input_str(tmp_str, "Введите файл: ");
                if (rc != OK)
                    break;
                
                f = fopen(tmp_str, "r");
                if (!f)
                {
                    rc = OPEN_FILE_ERROR;
                    break;
                }
                if (is_empty_file(f))
                {
                    rc = EMPTY_FILE;
                    break;
                }

                tree_destroy(tree);
                
                tree = NULL;
                tree = read_from_file_to_tree(f);

                fclose(f);
                break;

            case CLEAR_QUICK_EXPORT:
                f = fopen(TREE_DOT, "w");
                if (!f)
                {
                    rc = OPEN_FILE_ERROR;
                    break;
                }

                tree_export_to_dot(f, tree, NULL);
                fclose(f);
                dot_to_png(TREE_DOT, TREE_PNG);
                print_tree_node(tree, tree_apply_in, "Инфиксный обход");
                print_tree_node(tree, tree_apply_pre, "Префиксный обход");
                print_tree_node(tree, tree_apply_post, "Постфиксный обход");
                break;
            
            case QUICK_EXPORT:
                rc = input_char(&tmp_char); 
                if (rc != OK)
                    break;

                tree_find_by_first_symbol_all(tree, &point_list, tmp_char);
                
                f = fopen(TREE_DOT, "w");
                if (!f)
                {
                    rc = OPEN_FILE_ERROR;
                    break;
                }
                tree_export_to_dot(f, tree, point_list);
                fclose(f);
                
                dot_to_png(TREE_DOT, TREE_PNG);
                print_tree_node(tree, tree_apply_in, "Инфиксный обход");
                print_tree_node(tree, tree_apply_pre, "Префиксный обход");
                print_tree_node(tree, tree_apply_post, "Постфиксный обход");
                
                destroy_list(point_list);
                point_list = NULL;
                break;
        
            case CLEAR_EXPORT:
                rc = input_str(tmp_str, "Введите файл: ");
                if (rc != OK)
                    break;
                
                f = fopen(TREE_DOT, "w");
                if (!f)
                {
                    rc = OPEN_FILE_ERROR;
                    break;
                }

                tree_export_to_dot(f, tree, NULL);
                fclose(f);
                dot_to_png(TREE_DOT, tmp_str);
                print_tree_node(tree, tree_apply_in, "Инфиксный обход");
                print_tree_node(tree, tree_apply_pre, "Префиксный обход");
                print_tree_node(tree, tree_apply_post, "Постфиксный обход");
                break;

            case EXPORT:
                rc = input_str(tmp_str, "Введите файл: ");
                if (rc != OK)
                    break;
                rc = input_char(&tmp_char); 
                if (rc != OK)
                    break;

                tree_find_by_first_symbol_all(tree, &point_list, tmp_char);
                
                f = fopen(TREE_DOT, "w");
                if (!f)
                {
                    rc = OPEN_FILE_ERROR;
                    break;
                }
                tree_export_to_dot(f, tree, point_list);
                fclose(f);
                
                dot_to_png(TREE_DOT, tmp_str);

                print_tree_node(tree, tree_apply_in, "Инфиксный обход");
                print_tree_node(tree, tree_apply_pre, "Префиксный обход");
                print_tree_node(tree, tree_apply_post, "Постфиксный обход");
                
                destroy_list(point_list);
                point_list = NULL;
                break;   
             
                
            case CONTINUE:
            case EXIT:
                break;
                
            default:
                printf("Пока нет\n");
                break;
        }

        if (rc)
        {
            print_err_msg(rc);
            rc = OK; 
        }
    }

    tree_destroy(tree);
    destroy_list(point_list);
    
}
