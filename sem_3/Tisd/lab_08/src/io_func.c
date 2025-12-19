#include <stdio.h>
#include "io_func.h"
#include "exit_code.h"
#include "cmd_action.h"

void free_buff(FILE *f)
{
    int ch = fgetc(f);
    while (ch != '\n' && ch != EOF)
        ch = fgetc(f);
}

void print_err_msg(int rc)
{
    switch (rc)
    {
        case INVALID_PARAM:
            printf("Некоректные переданные параметры");
            break;
        case READ_ERROR:
            printf("Ошибка чтения");
            break;
        case MEM_ERROR:
            printf("Ошибка выделения памяти");
            break;
        case FILE_OPEN_ERROR:
            printf("Ошибка открытия файла");
            break;
        case EDGE_NOT_EXITS:
            printf("Ребра не существует");
            break;
        case EDGE_ALREADY_EXITS:
            printf("Ребро уже существует");
            break;
        case INVALID_DATA:
            printf("Некоректные данные");
            break;
        case INVALID_INPUT:
            printf("Некоректный ввод");
            break;
    }
}

int pos_int_read(FILE *f, int *num, int *max_value)
{
    if (fscanf(f, "%d", num) != 1)
    {
        free_buff(f);
        return INVALID_INPUT;
    }

    if ((max_value && *num >= *max_value) || *num < 0)
    {
        free_buff(f);
        return INVALID_DATA;
    }

    free_buff(f);

    return OK;
}

int pos_int_input(int *num, int *max_value)
{
    return pos_int_read(stdin, num, max_value);
}

int cmd_input(int *cmd, int max_cmd_value)
{
    printf("Введите команду: ");
    return pos_int_input(cmd, &max_cmd_value);
}


void print_cmd_list(void)
{
    printf(
        SEPARATOR_LINE
        "| 1. Эмуляция матричного графа                         |\n"
        "| 2. Эмуляция списочного графа                         |\n"
        "| 3. Сравнить структуры по памяти и времени            |\n"
        "| 0. Выйти                                             |\n"
        SEPARATOR_LINE
    );
}

void print_cmd_list_emu(void)
{
    printf(
        SEPARATOR_LINE
        "| 1. Добавить ребро                                    |\n"
        "| 2. Удалить ребро                                     |\n"
        "| 3. Проверить наличие ребра между вершинами           |\n"
        "| 4. Найти кратчайший путь между всеми парами вершин   |\n" 
        "| 0. Выйти                                             |\n"
        SEPARATOR_LINE
    );
}

int read_vertices(char *str, int *from_vert, int *to_vert, int *value)
{
    if (sscanf(str, "%d%d%d", from_vert, to_vert, value) != 3)
    {
        return READ_ERROR;
    }

    if (*from_vert < 0 || *to_vert < 0 || *value < 0)
    {
        return INVALID_RANGE;
    }

    return OK;
}

int intput_vertices(int *from_vert, int *to_vert, int *value)
{
    printf("Ввод в формате: <исходная_вершина> <конечная_вершина> <стоимость_перехода>\n");
    if (scanf("%d%d%d", from_vert, to_vert, value) != 3)
    {
        free_buff(stdin);
        return INVALID_INPUT;
    }

    if (*from_vert <= 0 || *to_vert <= 0 || *value < 0)
    {
        free_buff(stdin);
        return INVALID_RANGE;
    }

    *from_vert -= 1;
    *to_vert -= 1;
    free_buff(stdin);
    return OK;

}

int intput_vertices_no_value(int *from_vert, int *to_vert)
{
    printf("Ввод в формате: <исходная_вершина> <конечная_вершина>\n");
    if (scanf("%d%d", from_vert, to_vert) != 2)
    {
        free_buff(stdin);
        return INVALID_INPUT;
    }

    if (*from_vert < 0 || *to_vert < 0)
    {
        free_buff(stdin);
        return INVALID_RANGE;
    }


    *from_vert -= 1;
    *to_vert -= 1;
    free_buff(stdin);
    return OK;
}
