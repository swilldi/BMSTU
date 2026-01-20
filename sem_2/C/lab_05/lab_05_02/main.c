#include "errors_code.h"
#include "func.h"
#include <math.h>
#include <stdio.h>

int is_empty(FILE *f)
{
    fseek(f, 0, SEEK_END);

    if (ftell(f) == 0)
        return 1;
    rewind(f);

    return OK;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        return ARGS_TOO_FEW;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        return -1;
    }

    if (is_empty(file))
    {
        return -2;
    }

    double ar_mean, disp;
    if (arith_mean(file, &ar_mean) != OK)
        return INVALID_CONTENT;

    // printf("%lf\n", ar_mean);
    if (dispersion(file, ar_mean, &disp) != OK)
        return INVALID_CONTENT;

    fclose(file);

    printf("%f\n", disp);
}
