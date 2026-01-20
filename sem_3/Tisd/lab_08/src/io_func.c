#include <stdio.h>
#include "io_func.h"
#include "exit_code.h"
#include "cmd_action.h"
#include <string.h>

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
        case INVALID_RANGE:
            printf("Некоректные диапазон значений");
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
        case EMPTY_FILE:
            printf("Файл пустой");
            break;
        case STR_EMPTY:
            printf("Строка пустой");
            break;
        case STR_OVERFLOW:
            printf("Строка длинее %d символов", STR_LEN - 1);
        default:
            printf("Неизвестная ошибка, rc = %d", rc);
            break;
    }

    printf("\n");
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
        return INVALID_RANGE;
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

int input_str(char *str, char *msg)
{

    #ifndef FUNC_OUT
    if (msg == NULL)
        printf("Введите строку: ");
    else
        printf("%s", msg);
    #endif

    char tmp_str[STR_LEN + 10];
    if (fgets(tmp_str, STR_LEN + 10, stdin) == NULL)
        return READ_ERROR;
    
    size_t len = strlen(tmp_str);
    if (len && tmp_str[len - 1] == '\n')
    {
        tmp_str[len - 1] = '\0';
        len -= 1;
    }

    if (!len)
        return STR_EMPTY;
    if (len > STR_LEN)
        return STR_OVERFLOW;

    strcpy(str, tmp_str);
        
    return OK;

}
