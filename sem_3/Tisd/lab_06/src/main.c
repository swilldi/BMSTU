#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "tree.h"
#include "list.h"
#include "file_func.h"
#include "enums.h"
#include "exit_code.h"
#include "output_func.h"


#define TREE_DOT "tree.dot"
#define TREE_PNG "tree.png"





int is_empty_file(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    size_t start = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t end = ftell(f);
    fseek(f, 0, SEEK_SET);

    return end == start;

}

int run_tests(void)
{
    printf("Представьте, что здесь появилась большая таблица со сложными данными\n");
    return OK;
}

int main(void)
{

    int rc;
    int cmd;

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
        // TODO Сделать тесты для сравнения эффективонсти
        rc = run_tests();
        return rc;
    }
    else if (cmd == EXIT)
    {
        return rc;
    }

    
    tree_node *tree = NULL;
    tree_node *tmp_node = NULL;
    node_t *point_list = NULL; 
    char tmp_str[STR_LEN];
    char tmp_char;
    FILE *f;

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
                // TODO Сделать сравнение поиска в файле и в дереве
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
                
                // dot_to_png(TREE_DOT, TREE_PNG);
                
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
