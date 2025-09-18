#ifndef MATH_FUNC_H__
#define MATH_FUNC_H__

#include "large_num_struct.h"
#include <stdbool.h>
#include <stdint.h>

// получение множителя
int get_t(ulong_num_t *part_dividend, ulong_num_t *divider);

// добавление в неполный делитеть следующего числа
void update_part_dividend(large_num_t *dividend, ulong_num_t *part_dividend, size_t *i_next_digit, bool *drob);

// добавление числа в мантиссу
void add_digit(ulong_num_t *num, uint8_t new_digit);

// добавление нового числа в мантиссу результата
void add_digit_to_res(ulong_num_t *mantissa, uint8_t new_digit);

// умножение мантиссы, на цифру
void ulong_num_multiply_digit(ulong_num_t *multiplicand, int multiplier, ulong_num_t *res);

// вычитание меньшей мантиссы из большей
void ulong_num_subtract(ulong_num_t *minuend, ulong_num_t *subtrahend, ulong_num_t *res);

// сравнение мантисс
int ulong_num_cmp(const ulong_num_t *l, const ulong_num_t *r);

// округление числа
void large_num_round(large_num_t *num);

// проверка, что число является нулем
bool is_zero(ulong_num_t *num);

// Преобразование мантиссы результата к формату: чем меньше индекс, тем меньше разряд цифры
void formate_res(ulong_num_t *mantissa);

// деление длинных чисел
int large_num_divide(large_num_t *dividend, large_num_t *divider, large_num_t *res);

#endif
