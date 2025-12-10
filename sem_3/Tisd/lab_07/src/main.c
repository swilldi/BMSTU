#include <stdio.h>

#include <stdlib.h>

#include "bin_search_tree.h"
#include "avl_tree.h"
#include "common_define.h"
#include "export_data.h"
#include "import_data.h"
#include "input_func.h"
#include "hash_type.h"
#include "hash_table_open.h"
#include "hash_table_close.h"

typedef enum 
{
    EXIT = 0,
    ADD_TREE_NODE,
    REMOVE_TREE_NODE,
    
    CONTINUE,
    MAX_CMD_ACTION_TREE
} cmd_action_tree;



#if 0
int main(void)
{
    printf(
        "1. Добавить узел\n"
        "2. Удалить узел\n"
        "0. Выйти\n"
    );

    FILE *f = fopen("test.txt", "r");
    tree_node *tree = file_to_tree(f);
    fclose(f);

    f = fopen("test_dot.dot", "w");
    export_tree_to_dot(tree, f);
    fclose(f);
    system("dot -Tpng test_dot.dot -o res.png");

    int cmd = CONTINUE;
    int rc;
    
    char temp_str[TREE_STR_LEN];
    while (cmd != EXIT)
    {
        printf("Введите команду: ");
        if (scanf("%d", &cmd) != 1)
        {
            break;
        }
        while (fgetc(stdin) != '\n');

        switch (cmd)
        {
            case ADD_TREE_NODE:
                rc = input_str(temp_str, TREE_STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }
                tree_node *temp_node = tree_node_create(temp_str);
                if (tree_lookup(tree, temp_str, cmp_str) != NULL)
                {
                    rc = VALUE_EXITS;
                    break;
                }
                tree = tree_insert(tree, temp_node, cmp_str);
                break;
            case REMOVE_TREE_NODE:
                rc = input_str(temp_str, TREE_STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }
                
                if (tree_lookup(tree, temp_str, cmp_str) == NULL)
                {
                    rc = VALUE_NOT_EXITS;
                    break;
                }
                tree = tree_remove(tree, temp_str, cmp_str);
                break;
                
        }
        
        f = fopen("test_dot.dot", "w");
        export_tree_to_dot(tree, f);
        fclose(f);
        system("dot -Tpng test_dot.dot -o res.png");
    }
}
#endif 

#if 0
int main(void)
{
    printf(
        "1. Добавить узел\n"
        "2. Удалить узел\n"
        "0. Выйти\n"
    );

    FILE *f = fopen("test.txt", "r");
    avl_tree_node *tree = file_to_avl_tree(f);
    fclose(f);

    f = fopen("test_dot.dot", "w");
    export_avl_tree_to_dot(tree, f);
    fclose(f);
    system("dot -Tpng test_dot.dot -o res_avl.png");

    int cmd = CONTINUE;
    int rc;
    
    char temp_str[TREE_STR_LEN];
    while (cmd != EXIT)
    {
        printf("Введите команду: ");
        if (scanf("%d", &cmd) != 1)
        {
            break;
        }
        while (fgetc(stdin) != '\n');

        switch (cmd)
        {
            case ADD_TREE_NODE:
                rc = input_str(temp_str, TREE_STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }
                avl_tree_node *temp_node = avl_tree_node_create(temp_str);
                if (avl_tree_lookup(tree, temp_str, cmp_str) != NULL)
                {
                    rc = VALUE_EXITS;
                    break;
                }
                tree = avl_tree_insert(tree, temp_node, cmp_str);
                break;
            case REMOVE_TREE_NODE:
                rc = input_str(temp_str, TREE_STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }
                
                if (avl_tree_lookup(tree, temp_str, cmp_str) == NULL)
                {
                    rc = VALUE_NOT_EXITS;
                    break;
                }
                tree = avl_tree_remove(tree, temp_str, cmp_str);
                break;
                
        }
        
        f = fopen("test_dot.dot", "w");
        export_avl_tree_to_dot(tree, f);
        fclose(f);
        system("dot -Tpng test_dot.dot -o res_avl.png");
    }
}
#endif



int main(void)
{
    // hash_table_open *table = hash_table_open_create(10);
    // table = hash_table_open_add(table, "123");
    // table = hash_table_open_add(table, "420");
    // table = hash_table_open_add(table, "060");
    // table = hash_table_open_add(table, "163");
    // table = hash_table_open_add(table, "543");
    // table = hash_table_open_add(table, "6578");
    // table = hash_table_open_add(table, "xcvcv");
    // hash_table_open_print(table);
    // printf("\n");
    // table = hash_table_open_add(table, "asdere");
    // hash_table_open_print(table);
    // printf("\n");
    // table = hash_table_open_add(table, "sdf");

    // // hash_table_open_restructuring(&table);
    
    FILE *f = fopen("test.txt", "r");
    // int rc;
    hash_table_close *table = file_to_hash_table_close(f);
    hash_table_close_print(table);
    printf("\n");

    hash_table_close_add(&table, "123");
    hash_table_close_print(table);
    printf("\n");


}

