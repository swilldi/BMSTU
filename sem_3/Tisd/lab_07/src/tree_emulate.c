#include <stdio.h>
#include "exit_code.h"
#include "bin_search_tree.h"
#include "avl_tree.h"
#include "compare_func.h"
#include "export_data.h"
#include "import_data.h"
#include "io_func.h"

#define STANDART_DOT_FILE_NAME "test_dot.dot"
#define STANDART_TREE_FILE_NAME "test.txt"
#define CMD_STR_LEN 128

typedef enum 
{
    EXIT = 0,
    ADD_TREE_NODE,
    REMOVE_TREE_NODE,
    DELL_BY_SYMBOL,
    CMP_COUNT_FOR_VALUE,
    AVG_CMP,
    IMPORT_TREE_FROM_FILE,
    
    CONTINUE,
    MAX_CMD_ACTION_TREE
} cmd_action_tree;

typedef enum
{
    BST,
    AVL
} tree_mode;

typedef struct
{
    void *tree;
    tree_mode mode;
} tree_t;

// Создание дерева
tree_t *tree_create(tree_mode mode)
{
    tree_t *t = malloc(sizeof(tree_t));
    if (!t)
        return NULL;

    if (mode == BST)
        t->tree = bin_tree_create();
    else if (mode == AVL)
        t->tree = avl_tree_create();

    t->mode = mode;

    return t;
}

// Уничтожение дерева
void tree_destory(tree_t *t)
{
    if (!t || !t->tree)
        return;

    if (t->mode == BST)
        bin_tree_destroy(t->tree);
    else if (t->mode == AVL)
        avl_tree_destroy(t->tree);

    free(t);
}

// Добавление элемента
int tree_insert(tree_t *t, char *value)
{
    
    if (t->mode == BST)
    {
        bin_tree_node *bst = t->tree;
        // проверка вхождения значения
        if (bin_tree_lookup(bst, value, cmp_str) != NULL)
            return VALUE_EXITS;

        // создание узла дерева и его вставка
        bin_tree_node *temp_node = bin_tree_node_create(value);
        if (!temp_node)
            return MEMORY_ERROR;

        t->tree = bin_tree_insert(bst, temp_node, cmp_str);
    }
    else if (t->mode == AVL)
    {
        avl_tree_node *avl = t->tree;
        // проверка вхождения значения
        if (avl_tree_lookup(avl, value, cmp_str) != NULL)
            return VALUE_EXITS;

        // создание узла дерева и его вставка
        avl_tree_node *temp_node = avl_tree_node_create(value);
        if (!temp_node)
            return MEMORY_ERROR;

        t->tree = avl_tree_insert(avl, temp_node, cmp_str);
    }

    return OK;
}
// Удаление элемента
int tree_remove(tree_t *t, char *value)
{
    if (t->mode == BST)
    {
        bin_tree_node *bst = t->tree;
        // проверка вхождения значения
        if (bin_tree_lookup(bst, value, cmp_str) == NULL)
            return VALUE_NOT_EXITS;

        // удаление узла
        t->tree = bin_tree_remove(bst, value, cmp_str);
    }
    else if (t->mode == AVL)
    {
        avl_tree_node *avl = t->tree;
        // проверка вхождения значения
        if (avl_tree_lookup(avl, value, cmp_str) == NULL)
            return VALUE_NOT_EXITS;

        // удаление узла
        t->tree = avl_tree_remove(avl, value, cmp_str);
    }

    return OK;
}

// Удаление элементов по символу
int tree_remove_by_first_symbol(tree_t *t, char symb)
{
    if (t->mode == BST)
    {
        bin_tree_node *bst = t->tree;

        // удаление узлов
        t->tree = bin_tree_remove_by_first_symbol(bst, symb);
    }
    else if (t->mode == AVL)
    {
        avl_tree_node *avl = t->tree;

        // удаление узлов
        t->tree = avl_tree_remove_by_first_symbol(avl, symb);;
    }

    return OK;
}
// Экспорт в dot
int tree_to_dot(tree_t *t, FILE *f)
{
    if (t->mode == BST)
    {
        // удаление узлов
        export_bin_tree_to_dot(t->tree, f);
    }
    else if (t->mode == AVL)
    {
        // удаление узлов
        export_avl_tree_to_dot(t->tree, f);
    }

    return OK;
}

// Импорт из файла
void tree_from_file(tree_t *t, FILE *f)
{
    if (t->mode == BST)
    {
        // Чтение дерева
        t->tree = file_to_bin_tree(f);
    }
    else if (t->mode == AVL)
    {
        // Чтение дерева
        t->tree = file_to_avl_tree(f);
    }
}

void create_tree_png(tree_t *t, char *dot_file_name)
{
    char cmd_str[CMD_STR_LEN];
    FILE *f = fopen(dot_file_name, "w");

    // Экспорт дерева в dot файл
    if (t->mode == BST)
        export_bin_tree_to_dot(t->tree, f);
    else if (t->mode == AVL)
        export_avl_tree_to_dot(t->tree, f);
    fclose(f);

    snprintf(cmd_str, CMD_STR_LEN, "dot -Tpng %s -o %s.png", dot_file_name, t->mode == AVL ? "avl" : "bst");
    system(cmd_str);
}


int tree_lookup_cmp_count(tree_t *t, char *value, int *cmp_count_ptr)
{
    int cmp_count = -1;
    if (t->mode == BST)
    {
        if (bin_tree_lookup(t->tree, value, cmp_str) == NULL)
            return VALUE_NOT_EXITS;
        
        cmp_count = bin_tree_lookup_cmp_count(t->tree, value);
    }
    else if (t->mode == AVL)
    {
        if (avl_tree_lookup(t->tree, value, cmp_str) == NULL)
            return VALUE_NOT_EXITS;
        
        cmp_count = avl_tree_lookup_cmp_count(t->tree, value);
    }

    if (cmp_count == -1)
        return 1;

    *cmp_count_ptr = cmp_count;
    return OK;
}

int tree_avg_cmp(tree_t *t, double *avg_cmp_ptr)
{
    double avg_cmp = -1;
    if (t->mode == BST)
    {   
        avg_cmp = bin_tree_avg_cmp(t->tree, TEST_COUNT_FOR_AVG_CMP);
    }
    else if (t->mode == AVL)
    {   
        avg_cmp = avl_tree_avg_cmp(t->tree, TEST_COUNT_FOR_AVG_CMP);
    }

    if (avg_cmp < -1)
        return 1;

    *avg_cmp_ptr = avg_cmp;
    return OK;
}


int run_emulate_tree(void)
{
    printf(
        "1. Добавить узел\n"
        "2. Удалить узел\n"
        "3. Удалить по первому символу\n"
        "4. Количества сравнения для поиска по значению\n"
        "5. Среднее количество значения для поиска\n"
        "6. Прочитать дерево из файла\n"
        "0. Выйти\n"
        "-------------------------------\n"
    );

    // Создание деревьев
    tree_t *bin_tree = tree_create(BST);
    tree_t *avl_tree = tree_create(AVL);
    
    // Чтение деревьев из стандартного файла
    FILE *f = fopen(STANDART_TREE_FILE_NAME, "r");
    tree_from_file(bin_tree, f);
    tree_from_file(avl_tree, f);
    fclose(f);

    // Перенос деревьев в картинки 
    create_tree_png(bin_tree, STANDART_DOT_FILE_NAME);
    create_tree_png(avl_tree, STANDART_DOT_FILE_NAME);

    // !!! ТОЛЬКО ДЛЯ СДАЧИ ЛАБЫ
    system("code avl.png bst.png --diff");

    int cmd = CONTINUE;
    int rc;
    
    char temp_str[STR_LEN];
    char temp_char;
    while (cmd != EXIT)
    {

        // Чтение команды
        printf("Введите команду: ");
        rc = input_pos_int(&cmd, MAX_CMD_ACTION_TREE);
        if (rc != OK)
            cmd = CONTINUE;

        switch (cmd)
        {
            case ADD_TREE_NODE:
                // Ввод строки
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    break;
                }
                // Добавление элемента
                rc = tree_insert(bin_tree, temp_str);
                if (rc != OK)
                    break;
                rc = tree_insert(avl_tree, temp_str);
                break;
            case REMOVE_TREE_NODE:
                // Ввод удаляемого значения
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    break;
                }
                
                // удаление по значению
                rc = tree_remove(bin_tree, temp_str);
                if (rc != OK)
                    break;
                rc = tree_remove(avl_tree, temp_str);
                break;
            case DELL_BY_SYMBOL:
                // Ввод символа
                printf("Введите символ: ");
                if (scanf("%c", &temp_char) != 1)
                {
                    rc = INVALID_INPUT;
                    break;
                }

                // удаление по первому символу
                rc = tree_remove_by_first_symbol(bin_tree, temp_char);
                if (rc != OK)
                    break;
                rc = tree_remove_by_first_symbol(avl_tree, temp_char);
                break;
            case IMPORT_TREE_FROM_FILE:
                // Ввод файла
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }

                // открытие файла и экспорт 
                FILE *f = fopen(temp_str, "r");
                if (!f)
                {
                    rc = OPEN_FILE_ERR;
                    break;
                }
                if (file_is_empty(f))
                {
                    rc = EMPTY_FILE;
                    break;
                }

                tree_from_file(bin_tree, f);
                tree_from_file(avl_tree, f);
                fclose(f);
                break;
            case CMP_COUNT_FOR_VALUE:
                // Ввод значения
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }
                
                int bin_count, avl_count;
                rc = tree_lookup_cmp_count(bin_tree, temp_str, &bin_count);
                if (rc != OK)
                    break;
                rc = tree_lookup_cmp_count(avl_tree, temp_str, &avl_count);
                if (rc != OK)
                    break;

                printf(
                    "Количество сравнений для поиска: %s\n"
                    "Бинарное дерево поиска: %d\n"
                    "            АВЛ дерево: %d\n",
                    temp_str, bin_count, avl_count
                );

                break;
            case AVG_CMP:
                printf("");
                double bin_avg, avl_avg;
                rc = tree_avg_cmp(bin_tree, &bin_avg);
                if (rc != OK)
                    break;
                rc = tree_avg_cmp(avl_tree, &avl_avg);
                if (rc != OK)
                    break;

                printf(
                    "Среднеее количество сравнений\n"
                    "Бинарное дерево поиска: %.4lf\n"
                    "            АВЛ дерево: %.4lf\n",
                    bin_avg, avl_avg
                );
                break;
            case EXIT:
                break;
            default:
                rc = INVALID_CMD;
                break;
        }

        printf("-------------------------------\n");
        if (rc != OK)
        {
            print_err_msg(rc);
            rc = OK;
            printf("-------------------------------\n");
        }
        
        // Обновление картинок деревьев
        create_tree_png(bin_tree, STANDART_DOT_FILE_NAME);
        create_tree_png(avl_tree, STANDART_DOT_FILE_NAME);
    }

    tree_destory(bin_tree);
    tree_destory(avl_tree);

    return OK;
}
