#include <stdio.h>

#include <stdlib.h>

#include "common_define.h"
#include "export_data.h"
#include "import_data.h"
#include "io_func.h"
#include "hash_type.h"
#include "hash_table_emulate.h"
#include "tree_emulate.h"
#include "test.h"

typedef enum 
{
    EXIT = 0,
    TREE_EMULATE,
    HASH_TABLE_EMULATE,
    AVG_CMP_COUNT,
    COMPARE_TIME_TO_DEL,
    COMPARE_TIME_TO_SEARCH,
    COMPARE_COLLISION_PERCENT,
    
    MAX_CMD_ACTION_TREE,
    CONTINUE,
} cmd_action_tree;

int main(void)
{
    printf(
        "Исследуему типы данных:\n"
        "   - Двоичное дерево поиска\n  - Сбалансированнное дерево\n"
        "   - Хэш-таблица с открытым хэшированием\n   - Хэш-таблица с закрытым хэшированием\n"
        "-------------------------------\n"
        "1. Эмуляция деревьев\n"
        "2. Эмуляция хэш-таблиц\n"
        "-------------------------------\n"
        "3. Среднее кол-во сравнений для деревьев и хэш-таблиц\n"
        "4. Сравнение эффективности по памяти и времени для удаления элемента\n"
        "5. Сравнение эффективности по памяти и времени для поиска элемента\n"
        "6. Количество сравнений до и после реструктуризации\n"
        "-------------------------------\n"
        "0. Выйти\n"
        "-------------------------------\n"
    );

    int cmd = CONTINUE;
    int rc;
    
    while (cmd != EXIT)
    {

        // Чтение команды
        printf("Введите команду: ");
        rc = input_pos_int(&cmd, MAX_CMD_ACTION_TREE);
        if (rc != OK)
            cmd = CONTINUE;

        switch (cmd)
        {
            case TREE_EMULATE:
                rc = run_emulate_tree();
                break;
            case HASH_TABLE_EMULATE:
                rc = run_emulate_hash_table();
                break;
            case AVG_CMP_COUNT:
                test_avg_cmp();
                break;
            case COMPARE_TIME_TO_DEL:
                test_time_del(); 
                break;
            case COMPARE_TIME_TO_SEARCH:
                test_time_search();
                break;
            case COMPARE_COLLISION_PERCENT:
                test_hash_efficiency_collision();
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
    }
}

