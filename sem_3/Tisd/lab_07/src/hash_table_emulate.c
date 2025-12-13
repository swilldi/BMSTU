#include <stdio.h>
#include "exit_code.h"
#include "hash_table_open.h"
#include "hash_table_close.h"
#include "compare_func.h"
#include "export_data.h"
#include "import_data.h"
#include "io_func.h"

#define STANDART_DATA_FILE_NAME "test.txt"

typedef enum 
{
    EXIT = 0,
    ADD_VALUE,
    REMOVE_VALUE,
    PRINT_TABLE,
    CMP_COUNT_FOR_VALUE,
    AVG_CMP_COUNT,
    IMPORT_DATA_FROM_FILE,
    
    CONTINUE,
    MAX_CMD_ACTION_HASH_TABLE
} cmd_action_tree;

typedef enum
{
    OPEN_HASH,
    CLOSE_HASH
} hash_mode;

typedef struct
{
    void *table;
    hash_mode mode;
} hash_table_t;


// Уничтожение таблицы
void hash_table_destory(hash_table_t *t)
{
    if (!t || !t->table)
        return;

    if (t->mode == OPEN_HASH)
        hash_table_open_destroy(t->table);
    else if (t->mode == CLOSE_HASH)
        hash_table_close_destroy(t->table);

    free(t);
}

// Добавление элемента
int hash_table_add(hash_table_t *t, char *value)
{
    int rc = OK;
    if (t->mode == OPEN_HASH)
    {
         // проверка вхождения значения
        if (hash_table_open_contain(t->table, value))
            return VALUE_EXITS;

        // Добавление элемента
        rc = hash_table_open_add((hash_table_open **)&t->table, value);
    }
    else if (t->mode == CLOSE_HASH)
    {
        // проверка вхождения значения
        if (hash_table_close_contain(t->table, value))
            return VALUE_EXITS;

        // Добавление элемента
        rc = hash_table_close_add((hash_table_close **)&t->table, value);
    }

    return rc;
}

// Удаление элемента
int hash_table_remove(hash_table_t *t, char *value)
{
    int rc = OK;
    if (t->mode == OPEN_HASH)
    {
        // проверка вхождения значения
        if (!hash_table_open_contain(t->table, value))
            return VALUE_NOT_EXITS;

        // удаление узла
        rc = hash_table_open_del(t->table, value);
    }
    else if (t->mode == CLOSE_HASH)
    {
        // проверка вхождения значения
        if (!hash_table_close_contain(t->table, value))
            return VALUE_NOT_EXITS;

        // удаление узла
        rc = hash_table_close_del(t->table, value);
    }

    return rc;
}

// Вывод таблицы в консоль
int hash_table_print(hash_table_t *t)
{
    if (t->mode == OPEN_HASH)
    {
        // удаление узлов
        hash_table_open_print(t->table);
    }
    else if (t->mode == CLOSE_HASH)
    {
        // удаление узлов
        hash_table_close_print(t->table);
    }

    return OK;
}

// Импорт из файла
hash_table_t *table_from_file(hash_mode mode, FILE *f)
{
    hash_table_t *t = malloc(sizeof(hash_table_t));
    if (!t)
        return NULL;

    t->mode = mode;
    if (mode == OPEN_HASH)
    {
        // Чтение данных
         t->table = file_to_hash_table_open(f, get_str_hash);
        //  t->table = file_to_hash_table_open_no_rest(f, get_str_hash);
    }
    else if (mode == CLOSE_HASH)
    {
        // Чтение данных
        t->table = file_to_hash_table_close(f, get_str_hash);
        // t->table = file_to_hash_table_close_no_rest(f, get_str_hash);
    }

    return t;
}

// количество сравнений для элемента
int hash_table_cmp_count(hash_table_t *t, char *value, int *cmp_count_ptr)
{
    int cmp_count = -1;
    
    if (t->mode == OPEN_HASH)
    {
        if (!hash_table_open_contain(t->table, value))
            return VALUE_NOT_EXITS;

        cmp_count = hash_table_open_cmp_count(t->table, value);
    }
    else if (t->mode == CLOSE_HASH)
    {
        if (!hash_table_close_contain(t->table, value))
            return VALUE_NOT_EXITS;

        cmp_count = hash_table_close_cmp_count(t->table, value);
    }

    if (cmp_count == -1)
        return 1;

    *cmp_count_ptr = cmp_count;
    return OK;
}

// среднее количество сравнений для таблицы
int hash_table_avg_cmp(hash_table_t *t, double *avg_count_ptr)
{
    double avg_count = -1;
    
    if (t->mode == OPEN_HASH)
    {
        avg_count = hash_table_open_avg_cmp(t->table);
    }
    else if (t->mode == CLOSE_HASH)
    {
        avg_count = hash_table_close_avg_cmp(t->table);
    }

    if (avg_count < 0)
        return 1;

    *avg_count_ptr = avg_count;
    return OK;
}


int run_emulate_hash_table(void)
{
    printf(
        "1. Добавить элемент\n"
        "2. Удалить элемент\n"
        "3. Вывести таблицы\n"
        "4. Количество сравнений для поиска элемента\n"
        "5. Среднее количество сравнений для поиска в таблице\n"
        "6. Прочитать данные из файла\n"
        "0. Выйти\n"
        "-------------------------------\n"
    );

    
    // Чтение деревьев из стандартного файла
    FILE *f = fopen(STANDART_DATA_FILE_NAME, "r");
    hash_table_t *open_table = table_from_file(OPEN_HASH, f);
    hash_table_t *close_table = table_from_file(CLOSE_HASH, f);
    fclose(f);

    int cmd = CONTINUE;
    int rc;
    
    char temp_str[STR_LEN];
    while (cmd != EXIT)
    {

        // Чтение команды
        printf("Введите команду: ");
        rc = input_pos_int(&cmd, MAX_CMD_ACTION_HASH_TABLE);
        if (rc != OK)
            cmd = CONTINUE;


        switch (cmd)
        {
            case ADD_VALUE:
                // Ввод строки
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    cmd = EXIT;
                    break;
                }
                // Добавление элемента
                rc = hash_table_add(open_table, temp_str);
                if (rc != OK)
                    break;
                rc = hash_table_add(close_table, temp_str);
                break;
            case REMOVE_VALUE:
                // Ввод удаляемого значения
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    break;
                }
                
                // удаление по значению
                rc = hash_table_remove(open_table, temp_str);
                if (rc != OK)
                    break;
                rc = hash_table_remove(close_table, temp_str);
                break;
            case PRINT_TABLE:
                // TODO написать норм названия
                printf(
                    "\nТаблица с открытым хэшированием\n"
                      "===============================\n"
                );
                hash_table_print(open_table);
                printf("===============================\n");

                printf(
                    "\nТаблица с закрытым хэшированием\n"
                      "===============================\n"
                    );
                hash_table_print(close_table);
                printf("===============================\n");
                
                printf("\n");
                break;
            case CMP_COUNT_FOR_VALUE:
                // Ввод удаляемого значения
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
                    break;
                }

                int open_count, close_count;
                rc = hash_table_cmp_count(open_table, temp_str, &open_count);
                if (rc != OK)
                    break;

                rc = hash_table_cmp_count(close_table, temp_str, &close_count);
                if (rc != OK)
                    break;

                printf(
                    "Количество сравнений для поиска: %s\n"
                    "Таблица с открытым хэшированием: %d\n"
                    "Таблица с закрытым хэшированием: %d\n", 
                    temp_str, open_count, close_count
                );

                break;
            case AVG_CMP_COUNT:
                printf("");
                double open_avg_count, close_avg_count;
                rc = hash_table_avg_cmp(open_table, &open_avg_count);
                if (rc != OK)
                    break;

                rc = hash_table_avg_cmp(close_table, &close_avg_count);
                if (rc != OK)
                    break;

                printf(
                    "Среднее количество сравнений для поиска в таблице\n"
                    "Таблица с открытым хэшированием: %.4lf\n"
                    "Таблица с закрытым хэшированием: %.4lf\n", 
                    open_avg_count, close_avg_count
                );
                    break;
            case IMPORT_DATA_FROM_FILE:
                // Ввод файла
                printf("Введите строку: ");
                rc = input_str(temp_str, STR_LEN);
                if (rc != OK)
                {
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

                hash_table_destory(open_table);
                open_table = table_from_file(OPEN_HASH, f);
                
                hash_table_destory(close_table);
                close_table = table_from_file(CLOSE_HASH, f);
                fclose(f);
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

    hash_table_destory(open_table);
    hash_table_destory(close_table);

    return rc;
}
