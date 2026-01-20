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

#include "action.h"
#include "exit_code.h"
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
        return INVALID_INPUT;

    int c = getchar();
    while (c != EOF && c != '\n')
        c = getchar();

    return OK;
}

int main(void)
{
    error rc;
    action_t action;

    rc = input_action(&action, "Введите действие: ");
    if (rc != OK)
    {
        // print_err_msg(rc);
        return rc;
    }

    int tmp_num_1, tmp_num_2;
    node_t *lnum_1 = NULL, *lnum_2 = NULL;

// Ввод  чисел
    // #ifndef FUNC_OUT
    // printf("Введите первое число: ");
    // #endif
    rc = input_pos_int(&tmp_num_1, NULL);
    if (rc != OK)
    {
        // print_err_msg(rc);
        return rc;
    }
    
    if (tmp_num_1 == 0)
        return RES_IS_ZERO;

    if (action == MUL || action == DIV)
    {
        // #ifndef FUNC_OUT
        // printf("Введите второе число: ");
        // #endif
        rc = input_pos_int(&tmp_num_2, NULL);
        if (rc != OK)
        {
            // print_err_msg(rc);
            return rc;
        }
    }

    if (action == DIV && tmp_num_2 == 0)
        return DIV_BY_ZERO;

    // Перенос чисел в список
    lnum_1 = num_to_list(tmp_num_1);
    if (!lnum_1)
    {
        rc = MEMORY_ERR;
        // print_err_msg(rc);
        return rc;
    }

    if (action == MUL || action == DIV)
    {
        lnum_2 = num_to_list(tmp_num_2);
        if (!lnum_2)
        {
            destroy_list(lnum_1);
            rc = MEMORY_ERR;
            // print_err_msg(rc);
            return rc;
        }
    }


    // выполнение операции
    node_t *action_res_num = NULL;
    switch (action)
    {
        case OUT:
            print_list(lnum_1, print_prime_num);
            printf("L\n");
            break;
        case MUL:
            action_res_num = mul_list_num(lnum_1, lnum_2);
            if (!action_res_num)
            {
                rc = MEMORY_ERR;
                break;
            }
            print_list(action_res_num, print_prime_num);
            printf("L\n");
            break;
        case SQR:
            lnum_1 = sqr_list_num(lnum_1);
            if (!lnum_1)
            {
                rc = MEMORY_ERR;
                break;
            }
            print_list(lnum_1, print_prime_num);
            printf("L\n");
            break;
        case DIV:
            rc = div_list_num(lnum_1, lnum_2, &action_res_num);
            if (rc != OK)
            {
                break;
            }
            print_list(action_res_num, print_prime_num);
            printf("L\n");
            break;
        default:
            break;
    }

    // if (rc != OK)
    //     print_err_msg(rc);

    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(action_res_num);

    return rc;
}
