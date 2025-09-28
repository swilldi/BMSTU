#include "output_func.h"
#include "exit_code.h"

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

void print_car(car_t *car, size_t ind)
{
    char str_country[32];
    country_to_str(str_country, car->country);

    printf("| %5ld | %9s | %7s |", ind,  car->brend, str_country);
    
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
        print_car(&car_table[i], i + 1);
    
    if (len == 0)
    {
        printf(
            SEPARATOR_LINE_SPACE
            "|                                                       ТАБЛИЦА ПУСТАЯ                                                          |\n"
            SEPARATOR_LINE_SPACE
        );
    
    }
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
        print_car(&car_table[ind], i + 1);
    }
    printf(SEPARATOR_LINE);
}

void print_header(void)
{   printf(
        SEPARATOR_LINE
        "|  ind  |   Brend   | Country | Servies |      Prise     |   Color  | Condition | Warranty | Year | Milage | Owners | Repairing |\n"
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

void print_command_list(void)
{
    printf(
        "1. Добавить запись в конец таблицы\n"
        "2. Удалить запись из таблицы\n"
        "3. Выполнить поиск в диапазоне цен\n"
        "4. Вывод таблицы\n"
        "5. Вывод отсортированной таблицы ключей (исходная таблица не изменяется)\n"
        "6. Вывод отсортированной таблицы (сортируется сама таблица)\n"
        "7. Вывод отсортированной таблицы (по отсортированной таблице ключей)\n"
        "8. Сравнить эффективность обработки исходной таблицы и таблицы ключей\n"
        "9. Сравнить алгоритм сортировки \"Пузырек\" и \"Шейкер\"\n"
        "0. Выйти\n"
    );
}

void print_error_msg(int code)
{
    switch (code)
    {
        case FILE_NOT_SELECTED:
            printf("file not selected\n");
            return;
        case FILE_IS_EMPTY:
            printf("file is empty\n");
            return;
        case ERROR_OPEN_FILE:
            printf("error with open file\n");
            return;
        case DINAMIC_MEMORRY_ERROR:
            printf("error with dinamic memory\n");
            return;
        case NUM_NOT_IN_RANGE:
            printf("number not in range\n");
            return;
        case INVALID_BOOL_FIELD:
            printf("invalid bool field in file\n");
            return;
        case INVALID_VALUE_IN_FIELD:
            printf("invalid value field in file\n");
            return;
        case NOT_FOUND_FIELD:
            printf("not found field\n");
            return;
        case INPUT_ERROR:
            printf("input error\n");
            return;
        case INVALID_RANGE_COMMAND:
            printf("invalid number of command\n");
            return;
        case OVERFLOW_STR:
            printf("String overflow\n");
            break;
    }
}

