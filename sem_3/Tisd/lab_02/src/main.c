#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_func.h"
#include "io_func.h"

void print_command_list(void)
{
    printf(
        "1. Выбрать файл"
        "2. Добавить запись в конец таблицы"
        "3. Удалить запись из таблицы"
        "4. Вывод отсортированной таблицы ключей (исходная таблица не изменяется)"
        "5. Вывод отсортированной таблицы (сортируется сама таблица)"
        "6. Вывод отсортированной таблицы (по отсортированной таблице ключей)"
        "7. Сравнить эффективность обработки исходной таблицы и таблицы ключей"
        "8. Сравнить алгоритм сортировки \"Пузырек\" и \"Шейкер\""
    );
}

void print_header(void)
{   printf(
        "|---------------------------------------------------------------------------------------------------------------------|\n"
        "|  Brend  | Country | Servies |      Prise     |   Color  | Condition | Warranty | Year | Milage | Owners | Repairing |\n"
        "|---------------------------------------------------------------------------------------------------------------------|\n"
    );
}

#include <string.h>

// сортировка по цене
int main(void)
{
    FILE *f = fopen("/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_1.txt", "r");
    if (f == NULL)
        return 1;
    car_t c;
    
    print_header();
    
    read_item(f, &c);
    print_car(&c);
    read_item(f, &c);
    print_car(&c);
}

