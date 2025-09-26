#include "output_func.h"

void country_to_str(char *str, countries country)
{
    switch (country)
    {
        case CHINA:
            strcpy(str, "China");
            break;
        case FRANCE:
            strcpy(str, "France");
            break;
        case GERMANY:
            strcpy(str, "Germany");
            break;
        case ITALY:
            strcpy(str, "Italy");
            break;
        case JAPAN:
            strcpy(str, "Japan");
            break;
        case KOREA:
            strcpy(str, "Korea");
            break;
        case RUSSIA:
            strcpy(str, "Russia");
            break;
        case SWEDEN:
            strcpy(str, "Sweden");
            break;
        case UK:
            strcpy(str, "UK");
            break;
        case USA:
            strcpy(str, "USA");
            break;
        default:
            strcpy(str, "");
            break;
    }
}

void print_car(car_t *car)
{
    char str_country[32];
    country_to_str(str_country, car->country);

    printf("| %9s | %7s |", car->brend, str_country);
    
    if (car->country != RUSSIA)
        printf(" %7s |", car->servies ? "Yes" : "No");
    else
        printf(" ------- |");
    
    printf(" %14.2lf | %8s | %9s |", car->prise, car->color, car->is_new ? "New" : "Used");
    
    if (car->is_new)
    {
        printf(" %8d |", car->info.n.warranty);
        printf(" ---- | ------ | ------ | --------- |\n");
    }
    else
    {
        printf(" -------- |");
        printf(
            " %4d | %6d | %6hd | %9hd |\n",
            car->info.u.year,
            car->info.u.mileage,
            car->info.u.owners,
            car->info.u.repairing
        );
    }
}

void print_cars(car_t *car_table, size_t len)
{
    print_header();
    for (size_t i = 0; i < len; i++)
        print_car(&car_table[i]);
    printf(SEPARATOR_LINE);
}

void print_key_table_value(key_value_t *key)
{
    printf("| %11lu | %14.2lf |\n", key->index, key->value.num_f);
}

void print_keys_table(key_value_t *key_table, size_t len)
{
    print_header_key_table();
    for (size_t i = 0; i < len; i++)
        print_key_table_value(&key_table[i]);
    printf(SEPARATOR_LINE_KEY);
}

void print_cars_table_by_key_table(car_t *car_table, key_value_t *key_table, size_t len)
{
    size_t ind;

    print_header();
    for (size_t i = 0; i < len; i++)
    {
        ind = key_table[i].index;
        print_car(&car_table[ind]);
    }
    printf(SEPARATOR_LINE);
}

void print_header(void)
{   printf(
        SEPARATOR_LINE
        "|   Brend   | Country | Servies |      Prise     |   Color  | Condition | Warranty | Year | Milage | Owners | Repairing |\n"
        SEPARATOR_LINE
    );
}

void print_header_key_table(void)
{
    printf(
        SEPARATOR_LINE_KEY
        "|    index    |      Prise     |\n"
        SEPARATOR_LINE_KEY
    );
}
