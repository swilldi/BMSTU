#include "string.h"
#include "exit_code.h"
#include "stdio.h"
#include "structs.h"
#include "file_func.h"



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

int read_car(FILE *f, car_t *car)
{
    char buff[BUFF_LEN], *value = NULL;
    int rc;
    rc = read_str(f, buff, BUFF_LEN - 2);
    if (rc != OK)
        return rc;

    value = strtok(buff, ";");
    car_fields field = BREND;
    while (value != NULL)
    {
        if ((field == BREND && strlen(value) > BREND_LEN) || (field == COLOR && strlen(value) > COLOR_LEN))
        {
            rc = OVERFLOW_STR;
            break;
        }

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


size_t count_items(FILE *f)
{
    fseek(f, 0, SEEK_SET);

    size_t len = 0;
    char buff[BUFF_LEN];
    while (fgets(buff, BUFF_LEN, f) != NULL)
        len++;

    fseek(f, 0, SEEK_SET);
    return len;
}

int read_cars(FILE *f, car_t **car_table, size_t *len)
{
    int rc;
    *len = count_items(f);

    // выделение памяти
    if (*car_table == NULL)
        *car_table = malloc(*len * sizeof(car_t));
        
    if (*car_table == NULL)
        return DINAMIC_MEMORRY_ERROR;

    for (size_t i = 0; i < *len; i++)
    {
        rc = read_car(f, &(*car_table)[i]);
        if (rc != OK)
            break;
    }
    
    return rc;
}

bool is_empty(FILE *f)
{
    size_t start, end;
    
    fseek(f, 0, SEEK_SET);
    start = ftell(f);
    fseek(f, 0, SEEK_END);
    end = ftell(f);

    fseek(f, 0, SEEK_SET);
    return start == end;

}

int open_file(FILE **f, char *path)
{
    if (*f != NULL)
        fclose(*f);
    
    *f = fopen(path, "r");
    if (*f == NULL)
        return ERROR_OPEN_FILE;
    
    if (is_empty(*f))
        return FILE_IS_EMPTY;

    return OK;
}
