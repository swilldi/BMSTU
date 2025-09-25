#include <stdio.h>
#include <string.h>

#include "io_func.h"
#include "structs.h"


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

    printf("| %7s | %7s |", car->brend, str_country);
    
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
