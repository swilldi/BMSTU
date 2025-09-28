#include "input_func.h"
#include "structs.h"
#include "enums.h"
#include "exit_code.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_space(char *str)
{
    for (; *str != '\n' && *str != '\0'; str++ )
    {
        if (!isspace(*str))
            return false;
    }
    return true;
}

int input_str(char *str, size_t max_len)
{
    
    if (fgets(str, max_len + 2, stdin) == NULL)
        return 1;
    
    if (is_space(str))
    {
        if (fgets(str, max_len + 2, stdin) == NULL)
        return 1;
    }

    size_t len = strlen(str);
    if (len > max_len)
    {
        return 1;
    }
    str[len - 1] = '\0';
    return OK;
}


int input_int(int *num, size_t max_value)
{
    
    if (scanf("%d", num) != 1)
        return INPUT_ERROR;
    
    if (*num < 0 || *num > (long int)max_value)
        return NUM_NOT_IN_RANGE;
    
    return OK;
}

int input_double(double *num, double max_value)
{
    if (scanf("%lf", num) != 1)
        return INPUT_ERROR;
    
    if (*num < 0 || *num > (long int)max_value)
        return NUM_NOT_IN_RANGE;
    
    return OK;
}

int input_car(car_t *car)
{
    char buff[BUFF_LEN];
    int rc;

    #ifndef FUNC_OUT
    printf("Entry brend: ");
    #endif

    rc = input_str(buff, BREND_LEN);
    if (rc != OK)
        return rc;
    strcpy(car->brend, buff);

    #ifndef FUNC_OUT
    printf("Entry countries: ");
    #endif
    rc = input_int((int *)&car->country, COUNTRIES_MAX);
    if (rc != OK)
        return rc;

    if (car->country != RUSSIA)
    {
        #ifndef FUNC_OUT
        printf("Entry servies: ");
        #endif
        rc = input_int((int *)&car->servies, SERVISE_MAX);
        if (rc != OK)
            return rc;
    }

    #ifndef FUNC_OUT
    printf("Entry prise: ");
    #endif
    rc = input_double((double *)&car->prise, PRISE_MAX);
    if (rc != OK)
        return rc;

    #ifndef FUNC_OUT
    printf("Entry color: ");
    #endif
    rc = input_str(buff, COLOR_LEN);
    if (rc != OK)
        return rc;
    strcpy(car->color, buff);

    #ifndef FUNC_OUT
    printf("Entry condithion: ");
    #endif
    rc = input_int((int *)&car->is_new, IS_NEW_MAX);
    if (rc != OK)
        return rc;

    if (car->is_new)
    {
        #ifndef FUNC_OUT
        printf("Entry warranty: ");
        #endif
        rc = input_int((int *)&car->info.n.warranty, WARRANTY_MAX);
        if (rc != OK)
            return rc;
    }
    else 
    {
        #ifndef FUNC_OUT
        printf("Entry year: ");
        #endif
        rc = input_int((int *)&car->info.u.year, YEAR_MAX);
        if (rc != OK)
            return rc;
        

        #ifndef FUNC_OUT
        printf("Entry milage: ");
        #endif
        rc = input_int((int *)&car->info.u.mileage, MILAGE_MAX);
        if (rc != OK)
            return rc;

        #ifndef FUNC_OUT
        printf("Entry owners: ");
        #endif
        rc = input_int((int *)&car->info.u.owners, OWNERS_MAX);
        if (rc != OK)
            return rc;

        #ifndef FUNC_OUT
        printf("Entry repairing: ");
        #endif
        rc = input_int((int *)&car->info.u.repairing, REPAIRING_MAX);
        if (rc != OK)
            return rc;
    }

    return OK;
}

int input_filter(car_filter *filter)
{
    char buff[BUFF_LEN];
    int rc;

    #ifndef FUNC_OUT
    printf("Entry brend: ");
    #endif
    rc = input_str(buff, BREND_LEN);
    if (rc != OK)
        return rc;
    strncpy(filter->brend, buff, BREND_LEN);

    #ifndef FUNC_OUT
    printf("Entry min prise: ");
    #endif
    rc = input_double((double *)&filter->min_prise, PRISE_MAX);
    if (rc != OK)
        return rc;

    #ifndef FUNC_OUT
    printf("Entry max prise: ");
    #endif
    rc = input_double((double *)&filter->max_prise, PRISE_MAX);
    if (rc != OK)
        return rc;

    if (filter->max_prise < filter->min_prise)
        return INVALID_VALUE_IN_FILTER;

    filter->is_new = 0;
    filter->info.u.owners = 1;
    filter->info.u.repairing = 0;
    
    return OK;
}

int input_command(command_t *command)
{
    if (scanf("%d", (int *)command) != 1)
        return INPUT_ERROR;
    if (*command > COMMAND_MAX || *command < 0)
        return INVALID_RANGE_COMMAND;
    
    return OK;
}
