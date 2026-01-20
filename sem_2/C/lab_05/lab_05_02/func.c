#include "errors_code.h"
#include <math.h>
#include <stdio.h>

#include "func.h"

int arith_mean(FILE *f, double *res_num)
{
    rewind(f);

    *res_num = 0;
    double num;
    int count = 0;
    int rc = fscanf(f, "%lf", &num);
    while (rc == 1)
    {
        *res_num += num;
        count++;
        rc = fscanf(f, "%lf", &num);
    }
    if (rc == EOF && feof(f))
    {
        *res_num = *res_num / count;
        return OK;
    }
    else
    {
        return INVALID_CONTENT;
    }
}

int dispersion(FILE *f, double ar_mean, double *res_num)
{
    rewind(f);

    *res_num = 0;
    int count = 0;
    double num;
    int rc = fscanf(f, "%lf", &num);
    while (rc == 1)
    {
        *res_num += pow(num - ar_mean, 2);
        count++;
        rc = fscanf(f, "%lf", &num);
    }

    if (rc == EOF && feof(f))
    {
        *res_num = *res_num / count;
        return OK;
    }
    else
    {
        return INVALID_CONTENT;
    }
}
