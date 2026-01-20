/*
Запуск: ./app.exe in_file out_file action
action:
    - insert
    - pop_back
    - reverse
    - sort

1. Прочитать из файлика данные
2. Выполнить оперцию
3. Результат в файл

Осмысленанная задача:
Реализация инвентаря персонажа
Каждый предмет имеет три характеристики
    - Название (строка)
    - Цену (целое число)
    - Вес (целое число)
В файле каждое поле предмета содержится на новой строке

insert используется для ручного контроля расположения предметов
pop_back используется для удаления последнего полученного предмета
reverse используется, чтобы получить инвентарь от старых до новых предметов
sort используется чтобы упорядочить по следующей градации (первый показатель самый влиятельный)
    - Цена
    - Название
    - Вес

Cортируем по названию
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

#include "action_t.h"
#include "cmp_func.h"
#include "exit_code.h"
#include "file_func.h"
#include "item.h"
#include "list.h"
#include "out_func.h"

#define CORRECT_ARGS_COUNT 4

// - insert
// - pop_back
// - reverse

error input_pos_int(int *num, int *max_value)
{
    if (scanf("%d", num) != 1)
        return INVALID_INPUT;

    if ((max_value && *num > *max_value) || *num < 0)
        return INVALID_INDEX;

    int c = getchar();
    while (c != EOF && c != '\n')
        c = getchar();

    return OK;
}

int main(int argc, char **argv)
{
    int rc = OK;
    // количество аргументов
    if (argc != CORRECT_ARGS_COUNT)
    {
        rc = INVALID_ARGS_COUNT;
        print_err_msg(rc);
        return rc;
    }

    // корректность действия
    action_t action = str_to_action(argv[3]);
    if (action == ACTION_ERR)
    {
        rc = INVALID_ACTION;
        print_err_msg(rc);
        return rc;
    }

    // открытие файла
    char *in_file_name = argv[1];
    FILE *f = fopen(in_file_name, "r");
    if (!f)
    {
        rc = FILE_OPEN_ERR;
        print_err_msg(rc);
        return rc;
    }
    else if (is_empty_file(f))
    {
        fclose(f);
        rc = EMPTY_FILE;
        print_err_msg(rc);
        return rc;
    }

    // чтение данных из файла
    file_data_t *fdata = NULL;
    rc = read_file_data(f, &fdata, read_item, sizeof(item_t));
    if (rc != OK)
    {
        destroy_file_data(fdata, sizeof(item_t), free_content_item);
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    fclose(f);

    // for (size_t i = 0; i < fdata->len; i++)
    // {
    //     print_item((char*)fdata->data + i * sizeof(item_t));
    // }

    // перенос данных из fdata в список
    node_t *list = fdata_to_list(fdata, sizeof(item_t));
    if (!list)
    {
        rc = MEMORY_ERR;
        destroy_file_data(fdata, sizeof(item_t), free_content_item);
        print_err_msg(rc);
        return rc;
    }

    char *out_file_name = argv[2];
    f = fopen(out_file_name, "w");
    if (!f)
    {
        rc = FILE_OPEN_ERR;
        destroy_file_data(fdata, sizeof(item_t), free_content_item);
        print_err_msg(rc);
        return rc;
    }

    item_t *temp_item;
    switch (action)
    {
        // TODO вставка по позиции
        case INSERT:
            temp_item = malloc(sizeof(item_t));
            if (!temp_item)
            {
                rc = MEMORY_ERR;
                break;
            }

            #ifndef FUNC_OUT
            printf("      |--------------------------------------------|\n"
                "      |     Название     |    Цена    |     Вес    |\n"
                "      |--------------------------------------------|\n");
            print_list_index(list, print_item);
            printf("      |--------------------------------------------|\n");
            #endif

            #ifndef FUNC_OUT
            printf("Введите индекс перед, которым будет вставлен элемент.\nИндекс: ");
            #endif

            int index;
            int len = len_list(list) + 1;
            rc = input_pos_int(&index, &len);
            if (index == 0)
                rc = INVALID_INDEX;
            if (rc != OK)
            {
                free(temp_item);
                break;
            }

            node_t *point_node;
            if (index == len)
            {
                point_node = NULL;
            }
            else
            {
                index -= 1;
                point_node = node_by_index_list(list, index);
            }

            node_t *temp_node = create_node(temp_item);
            if (!temp_node)
            {
                free(temp_item);
                rc = MEMORY_ERR;
                break;
            }
            printf("Введите название, цену и вес предмета: \n");
            rc = read_item(stdin, temp_item);
            if (rc != OK)
            {
                free(temp_node);
                free(temp_item);
                print_err_msg(rc);
                break;
            }

            insert(&list, temp_node, point_node);

            write_list(f, list, write_item);
            free_content_item(temp_item);
            free(temp_item);
            break;
        case POPBACK:
            temp_item = pop_back(&list);
            if (!temp_item)
            {
                rc = EMPTY_LIST;
                print_err_msg(rc);
                break;
            }
            write_item(f, temp_item);
            break;
        case REVERSE:
            list = reverse(list);
            write_list(f, list, write_item);
            break;
        case SORT:
            list = sort(list, cmp_item_by_prise);
            print_list(list, print_item);
            write_list(f, list, write_item);
            break;
        default:
            break;
    }

    if (rc != OK)
    {
        print_err_msg(rc);
    }

    fclose(f);
    destroy_file_data(fdata, sizeof(item_t), free_content_item);
    destroy_list(list);

    return rc;
}
