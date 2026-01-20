#include <check.h>
#include <math.h>

#include "check_unit_tests.h"
#include "list.h"
#include "cmp_func.h"
#include "item.h"



#include "list_struct.h"

// отсортированный список
START_TEST(sorted_list)
{
    node_t *list = create_list();
    item_t items[] = 
    { 
        { "apple", 1, 0.2f },
        { "sword", 10, 1.0 },
        { "glass", 1, 0.5 },
        { "arrow", 2, 1.5 },
        { "metal", 5, 10.0 },
        { "fish", 2, 1.0 }
    };
    item_t out_data[] =
    {
        { "apple", 1, 0.2f },
        { "arrow", 2, 1.5 },
        { "fish", 2, 1.0 },
        { "glass", 1, 0.5 },
        { "metal", 5, 10.0 },
        { "sword", 10, 1.0 }
    };

    node_t *tmp_node;
    tmp_node = create_node(&items[0]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[1]);
    list = add_end_list(list, tmp_node);
    
    list = sort(list, cmp_item_by_title);

    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(item_t); i++)
    {
        item_t *cur_item = cur->data;
        cur = cur->next;
        ck_assert(strcmp(cur_item->title, out_data[i].title) == 0);
    }

    destroy_list(list);
}
END_TEST

// отсортированный в обратном направлении список
START_TEST(reverse_sorted_list)
{
    node_t *list = create_list();
    item_t items[] = 
    { 
        { "apple", 1, 0.2f },
        { "sword", 10, 1.0 },
        { "glass", 1, 0.5 },
        { "arrow", 2, 1.5 },
        { "metal", 5, 10.0 },
        { "fish", 2, 1.0 }
    };
    item_t out_data[] =
    {
        { "apple", 1, 0.2f },
        { "arrow", 2, 1.5 },
        { "fish", 2, 1.0 },
        { "glass", 1, 0.5 },
        { "metal", 5, 10.0 },
        { "sword", 10, 1.0 }
    };

    node_t *tmp_node;
    tmp_node = create_node(&items[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[4]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[0]);
    list = add_end_list(list, tmp_node);
    
    list = sort(list, cmp_item_by_title);

    
    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(item_t); i++)
    {
        item_t *cur_item = cur->data;
        cur = cur->next;
        ck_assert(strcmp(cur_item->title, out_data[i].title) == 0);
    }
    
    destroy_list(list);
}
END_TEST

// сортировка по названию
START_TEST(sort_by_title_list)
{
    node_t *list = create_list();
    item_t items[] = 
    { 
        { "apple", 1, 0.2f },
        { "sword", 10, 1.0 },
        { "glass", 1, 0.5 },
        { "arrow", 2, 1.5 },
        { "metal", 5, 10.0 },
        { "fish", 2, 1.0 }
    };
    item_t out_data[] =
    {
        { "apple", 1, 0.2f },
        { "arrow", 2, 1.5 },
        { "fish", 2, 1.0 },
        { "glass", 1, 0.5 },
        { "metal", 5, 10.0 },
        { "sword", 10, 1.0 }
    };

    node_t *tmp_node;
    tmp_node = create_node(&items[0]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[4]);
    list = add_end_list(list, tmp_node);

    list = sort(list, cmp_item_by_title);

    
    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(item_t); i++)
    {
        item_t *cur_item = cur->data;
        cur = cur->next;
        ck_assert(strcmp(cur_item->title, out_data[i].title) == 0);
    }
    
    destroy_list(list);
}
END_TEST

// сортировка по цене
START_TEST(sort_by_prise_list)
{
    node_t *list = create_list();
    item_t items[] = 
    { 
        { "apple", 1, 0.2f },
        { "sword", 10, 1.0 },
        { "glass", 1, 0.5 },
        { "arrow", 2, 1.5 },
        { "metal", 5, 10.0 },
        { "fish", 2, 1.0 }
    };
    item_t out_data[] =
    {
        { "apple", 1, 0.2f },
        { "glass", 1, 0.5 },
        { "arrow", 2, 1.5 },
        { "fish", 2, 1.0 },
        { "metal", 5, 10.0 },
        { "sword", 10, 1.0 }
    };

    node_t *tmp_node;
    tmp_node = create_node(&items[0]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[4]);
    list = add_end_list(list, tmp_node);
    
    list = sort(list, cmp_item_by_prise);

    
    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(item_t); i++)
    {
        item_t *cur_item = cur->data;
        cur = cur->next;
        // printf("%s %d | %s %d\n", cur_item->title, cur_item->prise, out_data[i].title, out_data[i].prise);
        ck_assert(cur_item->prise - out_data[i].prise == 0);

    }

    destroy_list(list);
}
END_TEST


// сортировка по весу
START_TEST(sort_by_weight_list)
{
    node_t *list = create_list();
    item_t items[] = 
    { 
        { "apple", 1, 0.2f },
        { "sword", 10, 1.0 },
        { "glass", 1, 0.5 },
        { "arrow", 2, 1.5 },
        { "metal", 5, 10.0 },
        { "fish", 2, 1.0 }
    };
    item_t out_data[] =
    {
        { "apple", 1, 0.2f },
        { "glass", 1, 0.5 },
        { "sword", 10, 1.0 },
        { "fish", 2, 1.0 },
        { "arrow", 2, 1.5 },
        { "metal", 5, 10.0 }
    };

    node_t *tmp_node;
    tmp_node = create_node(&items[0]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[3]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[5]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[2]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[1]);
    list = add_end_list(list, tmp_node);
    tmp_node = create_node(&items[4]);
    list = add_end_list(list, tmp_node);
    
    list = sort(list, cmp_item_by_weight);

    
    node_t *cur = list;
    for (size_t i = 0; i < sizeof(out_data) / sizeof(item_t); i++)
    {
        item_t *cur_item = cur->data;
        cur = cur->next;
        ck_assert(fabs(cur_item->weight - out_data[i].weight) <= EPS);
    }
    
    destroy_list(list);
}
END_TEST



TCase *sort_tcase(void)
{
    TCase *tc = tcase_create("sort");
    tcase_add_test(tc, sorted_list);
    tcase_add_test(tc, reverse_sorted_list);
    tcase_add_test(tc, sort_by_title_list);
    tcase_add_test(tc, sort_by_prise_list);
    tcase_add_test(tc, sort_by_weight_list);

    return tc;
}
