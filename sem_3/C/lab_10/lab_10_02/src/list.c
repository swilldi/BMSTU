#include "list.h"
#include <stdlib.h>

struct node_t
{
    int data;
    node_t *next;
};

// Создание списка
node_t *create_list(void)
{
    return NULL;
}

// Создание элемента списка
node_t *create_node(int value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->data = value;
        node->next = NULL;
    }
    return node;
}

void destroy_list(node_t *head)
{
    if (!head)
        return;

    node_t *cur = head, *next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

// Добавление к конец списка нового элемента
node_t *add_end_list(node_t *head, node_t *node)
{
    if (!head)
        return node;

    node_t *cur = head;
    while (cur->next)
        cur = cur->next;

    cur->next = node;

    return head;
}

node_t *reverse(node_t *head)
{
    if (!head)
        return NULL;

    node_t *prev = NULL, *cur = head, *next = head->next;
    while (next)
    {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = cur->next;
    }
    cur->next = prev;

    return cur;
}

void print_list(node_t *head, print_func_ptr print)
{
    while (head)
    {
        print(&head->data);
        head = head->next;
    }
}

int data_list(node_t *node)
{
    return node->data;
}

size_t len_list(node_t *head)
{
    size_t count = 0;
    while (head)
    {
        head = head->next;
        count += 1;
    }
    return count;
}

node_t *node_by_index_list(node_t *head, size_t ind)
{
    node_t *cur = head;
    for (size_t i = 0; i < ind; i++)
        cur = cur->next;

    return cur;
}

#include <math.h>
#include <stdbool.h>
bool is_prime_num(int num)
{
    if (num < 2)
        return false;

    int limit = (int)(sqrt(num)) + 1;
    for (int i = 2; i < limit; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int next_prime_num(int num)
{
    num += 1;
    while (!is_prime_num(num))
        num += 1;

    return num;
}

node_t *num_to_list(int num)
{
    node_t *list = create_list();
    node_t *tmp_node;

    if (num == 1)
    {
        tmp_node = create_node(0);
        if (!tmp_node)
        {
            destroy_list(list);
            return NULL;
        }
        list = add_end_list(list, tmp_node);
    }

    int cur_prime = 2;
    while (num > 1)
    {
        // TODO Убрать
        // printf("%d ", cur_prime);

        int count = 0;
        while (num % cur_prime == 0)
        {
            count += 1;
            num /= cur_prime;
        }

        tmp_node = create_node(count);
        if (!tmp_node)
        {
            destroy_list(list);
            return NULL;
        }
        list = add_end_list(list, tmp_node);
        cur_prime = next_prime_num(cur_prime);
    }
    // TODO Убрать
    // printf("\n");

    return list;
}

error list_to_num(node_t *head, int *num)
{
    *num = 0;
    int res = 1;
    int cur_prime = 2;
    while (head)
    {
        for (int i = 0; i < head->data; i++)
            res *= cur_prime;
        head = head->next;
        cur_prime = next_prime_num(cur_prime);
    }
    *num = res;
    return OK;
}

node_t *mul_list_num(node_t *num_1, node_t *num_2)
{
    node_t *mul_res = create_list();
    // проход по общим числам
    while (num_1 && num_2)
    {
        node_t *tmp_node = create_node(num_1->data + num_2->data);
        if (!tmp_node)
        {
            destroy_list(mul_res);
            return NULL;
        }
        mul_res = add_end_list(mul_res, tmp_node);

        num_1 = num_1->next;
        num_2 = num_2->next;
    }

    // добавлнение оставшихся частей
    while (num_1)
    {
        node_t *tmp_node = create_node(num_1->data);
        if (!tmp_node)
        {
            destroy_list(mul_res);
            return NULL;
        }
        mul_res = add_end_list(mul_res, tmp_node);
        num_1 = num_1->next;
    }

    while (num_2)
    {
        node_t *tmp_node = create_node(num_2->data);
        if (!tmp_node)
        {
            destroy_list(mul_res);
            return NULL;
        }
        mul_res = add_end_list(mul_res, tmp_node);
        num_2 = num_2->next;
    }

    return mul_res;
}

node_t *sqr_list_num(node_t *num)
{
    // проход по общим числам
    node_t *cur = num;
    while (cur)
    {
        cur->data *= 2;
        cur = cur->next;
    }

    return num;
}

// node_t *div_list_num(node_t *num_1, node_t *num_2)
// {
//     node_t *div_res = create_list();
//     // проход по общим числам
//     while (num_1 && num_2)
//     {
//         int cur_degree = num_1->data - num_2->data;
//         if (cur_degree < 0)
//         {
//             destroy_list(div_res);
//             return NULL;
//         }
//         node_t *tmp_node = create_node(cur_degree);
//         if (!tmp_node)
//         {
//             destroy_list(div_res);
//             return NULL;
//         }
//         div_res = add_end_list(div_res, tmp_node);

//         num_1 = num_1->next;
//         num_2 = num_2->next;
//     }

//     // второе число больше первого
//     if (num_2)
//     {
//         destroy_list(div_res);
//         return NULL;
//     }

//     // добавлнение оставшихся частей
//     while (num_1)
//     {
//         node_t *tmp_node = create_node(num_1->data);
//         if (!tmp_node)
//         {
//             destroy_list(div_res);
//             return NULL;
//         }
//         div_res = add_end_list(div_res, tmp_node);
//         num_1 = num_1->next;
//     }

//     // Удаление не значащих нулей
//     node_t *cur = div_res;
//     node_t *last_not_zero = NULL;
//     while (cur)
//     {
//         if (cur->data != 0)
//             last_not_zero = cur;

//         cur = cur->next;
//     }

//     if (last_not_zero)
//     {
//         destroy_list(last_not_zero->next);
//         last_not_zero->next = NULL;
//     }

//     return div_res;
// }

error div_list_num(node_t *lnum_1, node_t *lnum_2, node_t **div_num)
{
    // проход по общим числам
    int num_1, num_2;
    error rc;
    rc = list_to_num(lnum_1, &num_1);
    if (rc != OK)
    {
        return rc;
    }

    rc = list_to_num(lnum_2, &num_2);
    if (rc != OK)
    {
        return rc;
    }

    int div_value = num_1 / num_2;
    if (div_value <= 0)
        return RES_IS_ZERO;

    *div_num = num_to_list(div_value);
    if (!*div_num)
        return MEMORY_ERR;

    return OK;
}
