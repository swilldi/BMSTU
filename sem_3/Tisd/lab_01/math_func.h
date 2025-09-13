#include "large_num_struct.h"
#include <stdbool.h>

int get_t(ulong_num_t *part_dividend, ulong_num_t *divider);
void ulong_num_add_zeros(ulong_num_t *num, size_t count_zero);
void ulong_num_align(large_num_t *large_a, ulong_num_t *b, large_num_t *);
void ulong_num_multiply_digit(ulong_num_t *multiplicand, int multiplier, ulong_num_t *res);
void ulong_num_subtract(ulong_num_t *minuend, ulong_num_t *subtrahend, ulong_num_t *res);
void get_partial_dividend(large_num_t *dividend, ulong_num_t *divider, large_num_t *res, ulong_num_t *partial_dividend);
int cmp_ulong_num(const ulong_num_t *l, const ulong_num_t *r);
void round_large_num(large_num_t *num);
void large_num_divide(large_num_t *dividend, large_num_t *divider, large_num_t *res);
bool is_zero(ulong_num_t *num);

void update_part_dividend(large_num_t *dividend, ulong_num_t *part_dividend, size_t *i_next_digit);

void add_digit(ulong_num_t *num, int new_digit);

void add_digit_to_res(ulong_num_t *mantissa, int new_digit);

// заполняем с конца, поэтому надо сдвинуть всё к началу
void formate_res(ulong_num_t *mantissa);
