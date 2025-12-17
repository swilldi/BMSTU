#include "exit_code.h"
#include <stdio.h>
#include "graph_matr.h"
#include <limits.h>


// TODO  построение остовых деревьев минимальной стоимости
// TODO Для каждой пары городов найти длину кратчайшего пути между ними
// TODO 2-я структура со списком
// TODO проверка связности

#define GRAPH_DOT_FILE "graph.dot"

typedef enum
{
    EXIT = 0,

    ADD_EDGE,
    REMOVE_EDGE,
    CHECK_CONNECTION,
    SHORT_PATH,
    MST,
    CMP_STRUCT,

    MAX_CMD_ACTION,
    START,

} cmd_action;

void print_err_msg(int rc)
{
    (void)rc;
    printf("TODO\n");
}

int pos_int_read(FILE *f, int *num, int *max_value)
{
    if (fscanf(f, "%d", num) != 1)
        return INVALID_INPUT;

    if (max_value && *num >= *max_value)
        return INVALID_DATA;

    return OK;
}

int pos_int_input(int *num, int *max_value)
{
    return pos_int_read(stdin, num, max_value);
}

int cmd_input(int *cmd)
{
    int max_cmd_value = MAX_CMD_ACTION;
    printf("Введите команду: ");
    return pos_int_input(cmd, &max_cmd_value);
}

#define SEPARATOR_LINE "========================================================\n"
void print_cmd_list(void)
{
    printf(
        SEPARATOR_LINE
        "| 1. Добавить ребро                                    |\n"
        "| 2. Удалить ребро                                     |\n"
        "| 3. Проверить наличие ребра между вершинами           |\n"
        "| 4. Найти кратчайшего пути между всеми парами вершин  |\n"
        "| 5. Построить остовые деревья минимальной стоимости   |\n"
        "| 0. Выйти                                             |\n"
        SEPARATOR_LINE
    );
}

int main(void)
{
    int rc = OK;
    FILE *f = fopen("test.txt", "r");
    if (!f)
        return FILE_OPEN_ERROR;
    
    graph_matr_t *graph = NULL;
    graph_read_from_file(f, &graph);
    export_graph_matr_to_dot(graph, GRAPH_DOT_FILE);
    system("dot -Tpng "GRAPH_DOT_FILE" -o res.png");
    system("code res.png");
    
    print_cmd_list();
    int to_vert, from_vert, value_vert; 
    matrix_t temp_mtr;
    int cmd = START;
    while (cmd != EXIT)
    {
        // ввод команды
        rc = cmd_input(&cmd);
        if (rc != OK)
            return rc;

        // выполнение действия команды
        switch (cmd)
        {
            
            case ADD_EDGE:
                rc = intput_vertices(&from_vert, &to_vert, &value_vert);
                if (rc != OK)
                    break;

                rc = graph_add_edge(graph, from_vert - 1, to_vert - 1, value_vert);
                break;
            case REMOVE_EDGE:
                rc = intput_vertices_no_value(&from_vert, &to_vert);
                if (rc != OK)
                    break;

                rc = graph_remove_edge(graph, from_vert - 1, to_vert - 1);
                break;
            case CHECK_CONNECTION:
                rc = intput_vertices_no_value(&from_vert, &to_vert);
                if (rc != OK)
                    break;

                if (graph_not_edge(graph, from_vert, to_vert))
                    printf("Вершины не соеденины\n");
                else
                    printf("Вершины соеденины, стоимость перехода: %d\n", graph_path_value(graph, from_vert, to_vert));
                
                break;
            case SHORT_PATH:
                temp_mtr = graph_shortest_paths(graph);
                matrix_print(temp_mtr, graph_vertices_count(graph));
                break;
            case MST:
                break;
            case CMP_STRUCT:
                break;
            
            case EXIT:
            case START:
                break;
        }

        if (rc != OK)
        {
            print_err_msg(rc);
            rc = OK;
            cmd = START;
        }

        if (cmd != EXIT)
        {
            export_graph_matr_to_dot(graph, GRAPH_DOT_FILE);
            system("dot -Tpng "GRAPH_DOT_FILE" -o res.png");
        }
        printf(SEPARATOR_LINE);
    }


}
