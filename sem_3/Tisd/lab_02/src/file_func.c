#include "string.h"
#include "exit_code.h"
#include "stdio.h"
#include "structs.h"

int read_str(FILE *f, char *str, size_t max_len)
{
    if (fgets(str, max_len + 2, f) == NULL)
        return 1;

    size_t len = strlen(str);
    if (len > max_len)
    {
        // Очистка буфера
        return 1;
    }
    str[len - 1] = '\0';
    return OK;
}

int set_car_value(car_t *car, car_fields field, char *value)
{
    long int buff;
    double buff_double;

    switch (field)
    {
        case BREND:
            strcpy(car->brend, value);
            break;
        case COUNTRY:
            if (sscanf(value, "%ld", &buff) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff < 0 || buff > COUNTRIES_MAX)
                return NUM_NOT_IN_RANGE;
            car->country = buff;

            break;
        case SERVIES:
            if (*value != '0' && *value != '1')
                return INVALID_BOOL_FIELD;

            car->servies = (*value == '1');
            break;
        case PRISE:
            if (sscanf(value, "%lf", &buff_double) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff_double < 0 || buff_double > PRISE_MAX)
                return NUM_NOT_IN_RANGE;
            
            car->prise = buff_double;
            break;
        case COLOR:
            strcpy(car->color, value);
            break;
        case IS_NEW:
            if (*value != '0' && *value != '1')
                return INVALID_BOOL_FIELD;
        
                car->is_new = (*value == '1');
            break;
        case WARRANTY:
            if (sscanf(value, "%ld", &buff) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff < 0 || buff > WARRANTY_MAX)
                return NUM_NOT_IN_RANGE;
            car->info.n.warranty = buff;
            break;
        case YEAR:
            if (sscanf(value, "%ld", &buff) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff < 0 || buff > YEAR_MAX)
                return NUM_NOT_IN_RANGE;
            car->info.u.year = buff;

            break;
        case MILEAGE:
            if (sscanf(value, "%ld", &buff) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff < 0 || buff > MILAGE_MAX)
                return NUM_NOT_IN_RANGE;
            car->info.u.mileage = buff;
            break;
        case OWNERS:
            if (sscanf(value, "%ld", &buff) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff < 0 || buff > OWNERS_MAX)
                return NUM_NOT_IN_RANGE;
            car->info.u.owners = buff;
            break;
        case REPAIRING:
            if (sscanf(value, "%ld", &buff) != 1)
                return INVALID_VALUE_IN_FIELD;
            if (buff < 0 || buff > REPAIRING_MAX)
                return NUM_NOT_IN_RANGE;
            car->info.u.repairing = buff;
            break;
    }
    return OK;
}

int read_item(FILE *f, car_t *car)
{
    char buff[128], *value = NULL;
    int rc;
    rc = read_str(f, buff, 128 - 2);
    if (rc != OK)
        return rc;

    value = strtok(buff, ";");
    car_fields field = BREND;
    while (value != NULL)
    {
        
        rc = set_car_value(car, field, value);
        if (rc != OK || field == WARRANTY || field == REPAIRING)
            break;

        value = strtok(NULL, ";");
        field++;
        if ((field == SERVIES && car->country == RUSSIA) || (field == WARRANTY && !car->is_new))
            field++;
    }
    // printf("\n");

    return rc;
}

int read_items(FILE *f, car_t *cat_table)
{
    
}

