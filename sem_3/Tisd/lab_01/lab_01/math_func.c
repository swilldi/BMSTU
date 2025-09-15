#include "large_num_struct.h"
#include "errors_code.h"
#include <stdbool.h>
#include "io_func.h"
#include "math_func.h"

#include "stdio.h"

int get_t(ulong_num_t *part_dividend, ulong_num_t *divider)
{
    int a, b;
    
    size_t l = part_dividend->len;
    if (l > divider->len)
        a = 10 * part_dividend->digits[l - 1] + part_dividend->digits[l - 2];
    else
        a = part_dividend->digits[l - 1];
    b = divider->digits[divider->len - 1];

    return a / b;
}

void ulong_num_add_zeros(ulong_num_t *num, size_t count_zero)
{
    for (size_t i = num->len; i > 0; i--)
        num->digits[i - 1 + count_zero] = num->digits[i - 1];
    for (size_t i = 0; i < count_zero; i++)
        num->digits[i] = 0;
    num->len += count_zero;
}

void ulong_num_align(large_num_t *large_a, ulong_num_t *b)
{
    ulong_num_t *a = &large_a->mantissa;
    int diff = b->len - a->len;
    if (diff > 0)
    {
        ulong_num_add_zeros(a, diff);
    }

    if (cmp_ulong_num(a, b) < 0)
    {
        ulong_num_add_zeros(a, 1);
    }
}

// умножение числа, на цифру
void ulong_num_multiply_digit(ulong_num_t *multiplicand, int multiplier, ulong_num_t *res)
{
    res->len = multiplicand->len;

    int carry = 0;
    for (size_t i = 0; i < multiplicand->len; i++)
    {
        int value = multiplicand->digits[i] * multiplier + carry;
        res->digits[i] = value % 10;
        carry = value / 10;
    }
    
    if (carry > 0)
    {
        res->digits[res->len] = carry;
        res->len++;
    }
}

void ulong_num_subtract(ulong_num_t *minuend, ulong_num_t *subtrahend, ulong_num_t *res)
{
    bool borrow = false;
    res->len = minuend->len;

    // вычитание числа
    for (size_t i = 0; i < minuend->len; i++)
    {
        int digit_a = minuend->digits[i], digit_b = i < subtrahend->len ? subtrahend->digits[i] : 0;
        int sub = digit_a - digit_b - borrow;

        if (sub < 0)
        {
            sub += 10;
            borrow = true;
        }
        else
        {
            borrow = false;
        }

        res->digits[i] = sub;
    }
    while (res->len > 0 && res->digits[res->len - 1] == 0)
            res->len--;
}

void get_partial_dividend(large_num_t *dividend, ulong_num_t *divider, ulong_num_t *partial_dividend)
{
    size_t l = divider->len;
    partial_dividend->len = l;
    for (size_t i = 1; i <= l; i++)
    {
        if (i <= dividend->mantissa.len)
            partial_dividend->digits[l - i] = dividend->mantissa.digits[dividend->mantissa.len - i];
        else
        {
            partial_dividend->digits[l - i] = 0;
        }
    }

    if (cmp_ulong_num(partial_dividend, divider) < 0)
    {
        for (size_t i = l; i > 0; i--)
        {
            partial_dividend->digits[i] = partial_dividend->digits[i - 1];
        }
        
        if (l < dividend->mantissa.len)
            partial_dividend->digits[0] = dividend->mantissa.digits[dividend->mantissa.len - l - 1];
        else
        {
            partial_dividend->digits[0] = 0;
        }
        partial_dividend->len++;
    }
}

int cmp_ulong_num(const ulong_num_t *l, const ulong_num_t *r)
{
    if (l->len > r->len)
        return 1;
    else if (l->len < r->len)
        return -1;
    
    size_t max_len = l->len >= r->len ? l->len : r->len;
    int lv, rv;
    // сравнение по значением разраядов, если длины равны
    for (size_t i = 1; i <= max_len; i++)
    {
        if (i <= l->len)
            lv = l->digits[l->len - i];
        else
            lv = 0;
        
        if (i <= r->len)
            rv = r->digits[r->len - i];
        else
            rv = 0;

        if (lv > rv)
            return 1;
        else if (lv < rv)
            return -1;
    }

    // числа равны
    return 0;
}

// округление числа
void round_large_num(large_num_t *num)
{

    num->mantissa.len = DIGITS_COUNT_MAX;
    while (num->mantissa.digits[DIGITS_COUNT_MAX] != 0)
    {
        int carry = num->mantissa.digits[0] >= 5 ? 1 : 0;

        for (size_t i = 0; i < DIGITS_COUNT_MAX; i++)
        {
            int value = num->mantissa.digits[i + 1] + carry;
            num->mantissa.digits[i] = value % 10;
            carry = value / 10;
        }

        num->mantissa.digits[DIGITS_COUNT_MAX] = carry;
//        if (carry)
//            num->exponent++;

//         update_exponent(num);
    }
}

int large_num_divide(large_num_t *dividend, large_num_t *divider, large_num_t *res)
{
    if (is_zero(&divider->mantissa))
        return DIVISION_BY_ZERO;
    
    if (is_zero(&dividend->mantissa))
    {
        res->exponent = 0;
        res->sign = false;
        res->mantissa.digits[0] = 0;
        res->mantissa.len = 1;
        return OK;
    }
    
    res->mantissa.len = 0;
    res->sign = dividend->sign ^ divider->sign;
    
    
    res->exponent = dividend->exponent - dividend->mantissa.len - divider->exponent + divider->mantissa.len;
//    res->exponent = 0;
    bool drob = false;
    
//    if (is_one(&divider->mantissa))
//        res->exponent++;
    

    
    ulong_num_t part_dividend, vichitaemoe;
    size_t i_next_digit = 0;
    part_dividend.len = 0;
    while(cmp_ulong_num(&part_dividend, &divider->mantissa) < 0 && i_next_digit < dividend->mantissa.len + DIGITS_COUNT_MAX) {
        if (drob)
            res->exponent--;
        update_part_dividend(dividend, &part_dividend, &i_next_digit, &drob);
    }
    
    size_t t;
    do 
    {
        t = get_t(&part_dividend, &divider->mantissa);

        ulong_num_multiply_digit(&divider->mantissa, t, &vichitaemoe);
        while (cmp_ulong_num(&part_dividend, &vichitaemoe) < 0)
        {
            t -= 1;
            ulong_num_multiply_digit(&divider->mantissa, t, &vichitaemoe);
        }
        ulong_num_subtract(&part_dividend, &vichitaemoe, &part_dividend);
        add_digit_to_res(&res->mantissa, t);
        if (!drob)
            res->exponent++;
        

        if (is_zero(&part_dividend) && i_next_digit >= dividend->mantissa.len)
            break;

        update_part_dividend(dividend, &part_dividend, &i_next_digit, &drob);

        
        while (cmp_ulong_num(&part_dividend, &divider->mantissa) < 0 && res->mantissa.len < DIGITS_COUNT_MAX + 1)
        {
            update_part_dividend(dividend, &part_dividend, &i_next_digit, &drob);
            add_digit_to_res(&res->mantissa, 0);
        }

    } while (res->mantissa.len < DIGITS_COUNT_MAX + 1);

    if (res->mantissa.len >= DIGITS_COUNT_MAX + 1)
        round_large_num(res);
    else
        formate_res(&res->mantissa);
    
    if (is_zero(&dividend->mantissa))
        res->exponent = 0;
//    else if (divider->mantissa.len == 1)
//        res->exponent++;
    
//    if (i_next_digit > dividend->mantissa.len)
//        res->exponent += i_next_digit - dividend->mantissa.len;
    if (res->exponent > MAX_EXP)
        return MACHINE_INF;
    if (res->exponent < MIN_EXP)
        return MACHINE_ZERO;
    
    return OK;
}

bool is_zero(ulong_num_t *num)
{
    for (size_t i = 0; i < num->len; i++)
    {
        if (num->digits[i] != 0)
            return false;
    }

    return true;
}

bool is_one(ulong_num_t *num)
{
    return num->len == 1 && num->digits[0] == 1;
}

void update_part_dividend(large_num_t *dividend, ulong_num_t *part_dividend, size_t *i_next_digit, bool *drob)
{
    if (*i_next_digit >= dividend->mantissa.len)
    {
        add_digit(part_dividend, 0);
        *drob = true;
    }
    else
    {
        add_digit(part_dividend, dividend->mantissa.digits[dividend->mantissa.len - *i_next_digit - 1]);
        *i_next_digit += 1;
    }
    
    size_t i = part_dividend->len - 1;
    while (part_dividend->digits[i] == 0)
    {
        part_dividend->len--;
        i--;
    }
}

void add_digit(ulong_num_t *num, int new_digit)
{
    for (size_t i = num->len; i > 0; i--)
        num->digits[i] = num->digits[i - 1];
    num->digits[0] = new_digit;
    num->len += 1;
}

void add_digit_to_res(ulong_num_t *mantissa, int new_digit)
{
    size_t i = DIGITS_COUNT_MAX - mantissa->len;
    mantissa->digits[i] = new_digit;
    mantissa->len += 1;
}

// заполняем с конца, поэтому надо сдвинуть всё к началу
void formate_res(ulong_num_t *mantissa)
{
    for (size_t i = 0; i < mantissa->len; i++)
        mantissa->digits[i] = mantissa->digits[DIGITS_COUNT_MAX - mantissa->len + i + 1];
}

