#ifndef PROCESS_DEVICE_H__
#define PROCESS_DEVICE_H__

#include <stdio.h>
#include <time.h>
#include "queue.h"

typedef enum 
{
    WORK_T1,
    WORK_T2,
    WORK_END,
    FREE
} device_action_t;

typedef struct 
{
    q_type max;
    q_type min;
} trange_t;

int run_process_divece(mode_t mode, int request_count, trange_t *t1, trange_t *t2, trange_t *t3, trange_t *t4);
double rand_uniform(double min, double max);
q_type min(q_type a, q_type b);

#endif
