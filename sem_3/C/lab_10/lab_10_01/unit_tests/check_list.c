#include <check.h>

#include "list.h"
#include "cmp_func.h"

#include "list_struct.h"

// добавление в конец пустого списка
START_TEST(add_in_empty_list)
{
    node_t *list = create_list();
    int num = 10;
    node_t *new_node = create_node(&num);
    list = add_end_list(list, new_node);

    ck_assert(*(int*)list->data == num);
    ck_assert(list->next == NULL);

    destroy_list(list);
}
END_TEST
// добавление в конец непустого списка
START_TEST(add_in_list)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5 };
    
    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);

    node_t *cur = list;
    for (size_t i = 0; i < 4; i++)
    {
        ck_assert(*(int*)cur->data == (int)(i + 1));
        ck_assert(cur->next != NULL);
        cur = cur->next;
    }
    ck_assert(cur->next == NULL);
    ck_assert(*(int*)cur->data == 5);

    destroy_list(list);
}
END_TEST

// вставка перед головой списка
START_TEST(insert_before_head)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 7, 1, 2, 3, 4, 5 };
    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);

    tmp_node = create_node(&n[7]);
    insert(&list, tmp_node, list);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST
// вставка в середину списка
START_TEST(insert_in_list)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 1, 2, 3, 7, 4, 5 };

    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    node_t *rem_tmp_node = create_node(&n[4]);
    list = add_end_list(list, rem_tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);

    tmp_node = create_node(&n[7]);
    insert(&list, tmp_node, rem_tmp_node);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST
// вставка перед NULL
START_TEST(insert_before_null)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 1, 2, 3, 4, 5, 7 };
    
    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    node_t *rem_tmp_node = create_node(&n[4]);
    list = add_end_list(list, rem_tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);
    
    insert(&list, create_node(&n[7]), NULL);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST

// pop не пустого списка
START_TEST(pop_list)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);

    int *poped_n = pop_back(&list);
    ck_assert(*(int*)poped_n == 5);
    
    node_t *cur = list;
    for (size_t i = 0; i < 3; i++)
        cur = cur->next;

    ck_assert(cur->next == NULL);

    destroy_list(list);
}
END_TEST
// pop пустого списка
START_TEST(pop_empty_list)
{
    node_t *list = create_list();
    node_t *poped_node = pop_back(&list);

    ck_assert(poped_node == NULL);

    destroy_list(list);
}
END_TEST

// reverse пустого списка
START_TEST(reverse_empty_list)
{
    node_t *list = create_list();
    list = reverse(list);

    ck_assert(list == NULL);

    destroy_list(list);
}
END_TEST
// reverse списка из 1 элемента
START_TEST(reverse_list_one_elem)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    node_t *tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    
    list = reverse(list);

    ck_assert(*(int*)list->data == 4);
    ck_assert(list->next == NULL);

    destroy_list(list);
}
END_TEST
// reverse списка длиной больше 3
START_TEST(reverse_list)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 5, 4, 3, 2, 1 };
    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);
    
    list = reverse(list);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST

// сортируемая вставка в начало списка
START_TEST(sort_insert_in_start)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 1, 4, 5, 6, 7, 8 };
    list = add_end_list(list, create_node(&n[4]));
    list = add_end_list(list, create_node(&n[5]));
    list = add_end_list(list, create_node(&n[6]));
    list = add_end_list(list, create_node(&n[7]));
    list = add_end_list(list, create_node(&n[8]));

    node_t *tmp_node;
    tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[6]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[7]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[8]);
    list = add_end_list(list, tmp_node);
    
    
    node_t *inserted_node = create_node(&n[1]);
    sorted_insert(&list, inserted_node, cmp_int);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }
    destroy_list(list);
}
END_TEST
// сортируемая вставка в конец списка
START_TEST(sort_insert_in_end)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 2, 3, 4, 5, 6, 8 };

    node_t *tmp_node;
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[6]);
    list = add_end_list(list, tmp_node);
    
    node_t *inserted_node = create_node(&n[8]);
    sorted_insert(&list, inserted_node, cmp_int);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST
// сортируемая вставка в середину списка
START_TEST(sort_insert_in_med)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 1, 2, 4 ,6, 7, 8 };
    node_t *tmp_node;
    tmp_node = create_node(&n[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[6]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[7]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&n[8]);
    list = add_end_list(list, tmp_node);
    
    node_t *inserted_node = create_node(&n[4]);
    sorted_insert(&list, inserted_node, cmp_int);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST
// сортируемая вставка в пустой список
START_TEST(sort_insert_in_empty_list)
{
    node_t *list = create_list();
    int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int out_data[] = { 6 };
    
    node_t *inserted_node = create_node(&n[6]);
    sorted_insert(&list, inserted_node, cmp_int);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(int); i++)
    {
        ck_assert(*(int*)cur->data == out_data[i]);
        cur = cur->next;
    }

    destroy_list(list);
}
END_TEST

TCase *list_tcase(void)
{
    TCase *tc = tcase_create("list");
    
    tcase_add_test(tc, add_in_empty_list);
    tcase_add_test(tc, add_in_list);
    
    tcase_add_test(tc, insert_before_head);
    tcase_add_test(tc, insert_in_list);
    tcase_add_test(tc, insert_before_null);
    
    tcase_add_test(tc, pop_list);
    tcase_add_test(tc, pop_empty_list);
    tcase_add_test(tc, reverse_empty_list);
    tcase_add_test(tc, reverse_list_one_elem);
    tcase_add_test(tc, reverse_list);
    tcase_add_test(tc, sort_insert_in_start);
    tcase_add_test(tc, sort_insert_in_end);
    tcase_add_test(tc, sort_insert_in_med);
    tcase_add_test(tc, sort_insert_in_empty_list);

    return tc;
}
