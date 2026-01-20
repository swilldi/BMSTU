#include "list.h"
#include "file_func.h"
#include <stdlib.h>

#include "list_struct.h"

// Создание списка
node_t *create_list(void)
{
    return NULL;
}

// Создание элемента списка
node_t *create_node(void *value)
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

// Вставка элемента перед другим в списке
// ЕСЛИ ЧТО-ТО НЕ БУДЕТ ПРОХОДИТЬ В ПАЙПЛАЙНЕ, ТО ОНО РАБОТАТЬ ПРИ BEFORE == NULL НЕ БУДЕТ
// По идее будет работать =)
void insert(node_t **head, node_t *elem, node_t *before)
{
    if (!*head)
        return;
    if (!before)
    {
        *head = add_end_list(*head, elem);
        return;
    }

    if (*head == before)
    {
        elem->next = *head;
        *head = elem;
        return;
    }

    node_t *cur = *head;
    while (cur)
    {
        if (cur->next == before)
        {
            cur->next = elem;
            elem->next = before;
            return;
        }
        else
            cur = cur->next;
    }
}

// Удаление элемента из списка по значению
node_t *del_by_value_list(node_t *head, void *value, func_cmp_ptr fcmp)
{
    // пустой списко
    if (head == NULL)
        return NULL;

    node_t *cur = head, *prev = NULL, *del = NULL;
    while (cur)
    {
        if (fcmp(cur->data, value) == 0)
        {
            del = cur;
            if (prev)
                prev->next = cur = cur->next;
            else
                head = cur = cur->next;

            free(del);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

    return head;
}

// возвращает указатель на данные из элемента, который расположен в «хвосте» списка и удаляет из списка
void *pop_back(node_t **head)
{
    if (!head || !*head)
        return NULL;

    node_t *cur = *head;
    node_t *prev = NULL;

    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
    }

    if (prev)
        prev->next = NULL;
    else
        *head = NULL;

    void *data = cur->data;
    free(cur);

    return data;
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
        print(head->data);
        head = head->next;
    }
}

void print_list_index(node_t *head, print_func_ptr print)
{
    size_t ind = 1;
    while (head)
    {
        printf("%4lu. ", ind);
        ind += 1;
        print(head->data);
        head = head->next;
    }
}

void write_list(FILE *f, node_t *head, write_func_ptr write)
{
    while (head)
    {
        write(f, head->data);
        head = head->next;
    }
}

node_t *fdata_to_list(file_data_t *fdata, size_t data_size)
{
    node_t *head = create_list();
    for (size_t i = 0; i < fdata->len; i++)
    {
        node_t *tmp_node = create_node((char *)fdata->data + i * data_size);
        if (tmp_node == NULL)
        {
            destroy_list(head);
            return NULL;
        }
        head = add_end_list(head, tmp_node);
    }

    return head;
}

void sorted_insert(node_t **head, node_t *elem, func_cmp_ptr fcmp)
{
    if (*head == elem)
    {
        return;
    }

    node_t *prev = NULL, *cur = *head;
    while (cur && fcmp(elem->data, cur->data) >= 0)
    {
        prev = cur;
        cur = cur->next;
    }

    if (prev == NULL)
    {
        elem->next = *head;
        *head = elem;
    }
    else
    {
        prev->next = elem;
        elem->next = cur;
    }
}

void *data_list(node_t *node)
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

node_t *sort(node_t *head, func_cmp_ptr fcmp)
{
    size_t len = len_list(head);

    node_t *cur = head, *next = NULL;
    for (size_t i = 0; i < len; i++)
    {
        next = cur->next;
        cur->next = NULL;
        sorted_insert(&head, cur, fcmp);
        cur = next;
    }

    return head;
}
