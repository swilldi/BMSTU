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
#define TEST_COUNT 100

double tree_time_test(FILE *f, char tmp_char)
{
    clock_t start, end;
    double res = 0;

    tree_node *tmp_tree = read_from_file_to_tree(f);
    if (!tmp_tree)
        return -1;

    printf("Начались прогревочные тесты\n");
    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        node_t *tmp_list_point = NULL;
        tree_find_by_first_symbol_all(tmp_tree, &tmp_list_point, tmp_char);
        destroy_list(tmp_list_point);
    }
    printf("Завершились прогревочные тесты\n");

    printf("Начались основные тесты\n");
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        node_t *tmp_list_point = NULL;
        start = clock();
        tree_find_by_first_symbol_all(tmp_tree, &tmp_list_point, tmp_char);
        end = clock();
        res += (double)(end - start);
        destroy_list(tmp_list_point);
        
        if ((i + 1) % 10 == 0)
            printf("Выполнено %lu тестов\n", i + 1);
    }
    printf("Заврешились основные тесты\n");

    tree_destroy(tmp_tree);

    return res / CLOCKS_PER_SEC / TEST_COUNT;
}

double file_time_test(FILE *f, char tmp_char)
{
    node_t *tmp_list = NULL;
    clock_t start, end;
    double res = 0;

    printf("Начались прогревочные тесты\n");
    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        rewind(f);
        tmp_list = read_from_file_by_letter(f, tmp_char);
        destroy_list(tmp_list);
    }
    printf("Завершились прогревочные тесты\n");

    printf("Начались основные тесты\n");
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        rewind(f);
        start = clock();
        tmp_list = read_from_file_by_letter(f, tmp_char);
        end = clock();
        res += (double)(end - start);
        destroy_list(tmp_list);
        if ((i + 1) % 10 == 0)
            printf("Выполнено %lu тестов\n", i + 1);
    }
    printf("Заврешились основные тесты\n");

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


void print_in(tree_node *tree)
{
    node_t *list = NULL;
    tree_apply_in(tree, tree_add_to_list, &list);
    printf("\nИнфиксный вывод\n");
    print_list(list);
    destroy_list(list);
}

void print_post(tree_node *tree)
{
    node_t *list = NULL;
    tree_apply_post(tree, tree_add_to_list, &list);
    printf("\nПостфиксный вывод\n");
    print_list(list);
    destroy_list(list);
}

void print_pre(tree_node *tree)
{
    node_t *list = NULL;
    tree_apply_pre(tree, tree_add_to_list, &list);
    printf("\nПрефиксный вывод\n");
    print_list(list);
    destroy_list(list);
}


int main(void)
{

    int rc;
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
                print_in(tree);
                print_pre(tree);
                print_post(tree);
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
                print_in(tree);
                print_pre(tree);
                print_post(tree);
                
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
                print_in(tree);
                print_pre(tree);
                print_post(tree);
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

                
                print_in(tree);
                print_pre(tree);
                print_post(tree);

                
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
