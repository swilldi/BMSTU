#include <check.h>
#include <math.h>
#include "exit_code.h"

#include "check_unit_tests.h"
#include "list.h"

struct node_t
{
    int data;
    node_t *next;
};

// Результат деления ноль
START_TEST(div_res_zero)
{
    node_t *lnum_1 = num_to_list(100);
    node_t *lnum_2 = num_to_list(120);

    node_t *div_lnum;
    error rc = div_list_num(lnum_1, lnum_2, &div_lnum);
    
    destroy_list(lnum_1);
    destroy_list(lnum_2);
    
    ck_assert(rc == RES_IS_ZERO);
}
END_TEST


// Результат деления не ноль
START_TEST(div_res_no_zero)
{
    node_t *lnum_1 = num_to_list(132);
    node_t *lnum_2 = num_to_list(2);

    int res_n[] = { 1, 1, 0, 0, 1 };
    size_t i = 0;

    node_t *div_lnum;
    error rc = div_list_num(lnum_1, lnum_2, &div_lnum);
    ck_assert(rc == OK);

    node_t *cur = div_lnum;
    for (; i < 4; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);

    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(div_lnum);
    
}
END_TEST

// Результат деления на 1
START_TEST(div_by_one)
{
    node_t *lnum_1 = num_to_list(100);
    node_t *lnum_2 = num_to_list(1);

    int res_n[] = { 2, 0, 2 };
    size_t i = 0;

    node_t *div_lnum;
    error rc = div_list_num(lnum_1, lnum_2, &div_lnum);
    ck_assert(rc == OK);

    node_t *cur = div_lnum;
    for (; i < 2; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);

    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(div_lnum);
    
}
END_TEST

// Результат деления числа на само себя
START_TEST(div_num_by_num)
{
    node_t *lnum_1 = num_to_list(100);
    node_t *lnum_2 = num_to_list(100);

    int res_n[] = { 0 };

    node_t *div_lnum;
    error rc = div_list_num(lnum_1, lnum_2, &div_lnum);
    ck_assert(rc == OK);

    node_t *cur = div_lnum;
    ck_assert(cur->data == res_n[0]);

    ck_assert(cur->next == NULL);

    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(div_lnum);
    
}
END_TEST

// Умножения двух чисел 
START_TEST(mul_two_num)
{
    node_t *lnum_1 = num_to_list(132);
    node_t *lnum_2 = num_to_list(50);

    int res_n[] = { 3, 1, 2, 0, 1 };
    size_t i = 0;

    node_t *mul_lnum;
    mul_lnum = mul_list_num(lnum_1, lnum_2);
    ck_assert(mul_lnum != NULL);

    node_t *cur = mul_lnum;
    for (; i < 4; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);
    
    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(mul_lnum);
}
END_TEST

// Умножения на 1 
START_TEST(mul_by_one)
{
    node_t *lnum_1 = num_to_list(132);
    node_t *lnum_2 = num_to_list(1);

    int res_n[] = { 2, 1, 0, 0, 1 };
    size_t i = 0;

    node_t *mul_lnum;
    mul_lnum = mul_list_num(lnum_1, lnum_2);
    ck_assert(mul_lnum != NULL);

    node_t *cur = mul_lnum;
    for (; i < 4; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);
    
    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(mul_lnum);
}
END_TEST

// Умножения на себя
START_TEST(mul_num_by_num)
{
    node_t *lnum_1 = num_to_list(25);
    node_t *lnum_2 = num_to_list(25);

    int res_n[] = { 0, 0, 4 };
    size_t i = 0;

    node_t *mul_lnum;
    mul_lnum = mul_list_num(lnum_1, lnum_2);
    ck_assert(mul_lnum != NULL);

    node_t *cur = mul_lnum;
    for (; i < 2; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);
    
    destroy_list(lnum_1);
    destroy_list(lnum_2);
    destroy_list(mul_lnum);
}
END_TEST

// Возведение в квадрат
START_TEST(sqr_num)
{
    node_t *lnum_1 = num_to_list(12);

    int res_n[] = { 4, 2 };
    size_t i = 0;

    lnum_1 = sqr_list_num(lnum_1);
    ck_assert(lnum_1);

    node_t *cur = lnum_1;
    for (; i < 1; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);
    
    destroy_list(lnum_1);
}
END_TEST

// Возведение в квадрат 1
START_TEST(sqr_num_one)
{
    node_t *lnum_1 = num_to_list(1);

    int res_n[] = { 0 };
    size_t i = 0;

    lnum_1 = sqr_list_num(lnum_1);
    ck_assert(lnum_1);

    node_t *cur = lnum_1;
    ck_assert(cur->data == res_n[i]);
    ck_assert(cur->next == NULL);
    
    destroy_list(lnum_1);
}
END_TEST


// Вывол числа
START_TEST(out_num)
{
    node_t *lnum = num_to_list(132);

    int res_n[] = { 2, 1, 0, 0, 1 };
    size_t i = 0;

    node_t *cur = lnum;
    for (; i < 4; i++)
    {
        ck_assert(cur->data == res_n[i]);
        cur = cur->next;
    }

    ck_assert(cur->next == NULL);
    
    destroy_list(lnum);
}
END_TEST

TCase *action_tcase(void)
{
    TCase *tc = tcase_create("list");
    
    tcase_add_test(tc, div_res_zero);
    tcase_add_test(tc, div_res_no_zero);
    tcase_add_test(tc, mul_two_num);
    tcase_add_test(tc, out_num);
    tcase_add_test(tc, div_by_one);
    tcase_add_test(tc, div_num_by_num);
    tcase_add_test(tc, mul_by_one);
    tcase_add_test(tc, mul_num_by_num);
    tcase_add_test(tc, sqr_num);
    tcase_add_test(tc, sqr_num_one);
    
    return tc;
}
