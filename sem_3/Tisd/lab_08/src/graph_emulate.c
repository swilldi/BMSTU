#include "exit_code.h"
#include <stdio.h>
#include <stdlib.h>
#include "graph_emulate.h"
#include "graph_matr.h"
#include "graph_list.h"
#include "matrix.h"
#include "io_func.h"

#define GRAPH_DOT_FILE "graph.dot"

typedef enum {
    EMU_EXIT = 0,
    EMU_ADD_EDGE,
    EMU_REMOVE_EDGE,
    EMU_CHECK_CONNECTION,
    EMU_SHORT_PATH,
    EMU_MAX_CMD,
    EMU_START
} emulate_cmd_t;

// Универсальный тип графа
typedef struct {
    graph_type_t type;
    void *graph;
} graph_any_t;

// Универсальные функции
int graph_add(graph_any_t *g, int from, int to, int weight) 
{
    if (g->type == GRAPH_TYPE_MATRIX)
        return graph_add_edge((graph_matr_t*)g->graph, from, to, weight);
    else
        return graph_list_add_edge((graph_list_t*)g->graph, from, to, weight);
}

int graph_remove(graph_any_t *g, int from, int to) 
{
    if (g->type == GRAPH_TYPE_MATRIX)
        return graph_remove_edge((graph_matr_t*)g->graph, from, to);
    else
        return graph_list_remove_edge((graph_list_t*)g->graph, from, to);
}

int graph_not_edge_any(graph_any_t *g, int from, int to) 
{
    if (g->type == GRAPH_TYPE_MATRIX)
        return graph_not_edge(g->graph, from, to);
    else
        return graph_list_not_edge(g->graph, from, to);
}

int graph_path_value_any(graph_any_t *g, int from, int to) 
{
    if (g->type == GRAPH_TYPE_MATRIX)
        return graph_path_value(g->graph, from, to);
    else
        return graph_list_path_value(g->graph, from, to);
}

void graph_print_shortest(graph_any_t *g) 
{
    if (g->type == GRAPH_TYPE_MATRIX) {
        matrix_t m = graph_shortest_paths((graph_matr_t*)g->graph);
        matrix_print(m, graph_vertices_count((graph_matr_t*)g->graph));
        matrix_destoy(m, graph_vertices_count((graph_matr_t*)g->graph));
    } else {
        matrix_t m = graph_list_shortest_paths((graph_list_t*)g->graph);
        matrix_print(m, graph_list_vertices_count((graph_list_t*)g->graph));
        matrix_destoy(m, graph_list_vertices_count((graph_list_t*)g->graph));
    }
}

void graph_destroy_any(graph_any_t *g) 
{
    if (g->type == GRAPH_TYPE_MATRIX)
        graph_destroy((graph_matr_t*)g->graph);
    else
        graph_list_destroy((graph_list_t*)g->graph);
}

int graph_to_png(graph_any_t *g) 
{
    int rc;
    if (g->type == GRAPH_TYPE_MATRIX)
    {
        rc = export_graph_matr_to_dot(g->graph, GRAPH_DOT_FILE);
    }   
    else
    {
        rc = export_graph_list_to_dot(g->graph, GRAPH_DOT_FILE);
    }

    if (rc != OK)
        return rc;
    
    if (g->type == GRAPH_TYPE_MATRIX)
    {
        system("dot -Tpng "GRAPH_DOT_FILE" -o res_matr.png");
        system("code res_matr.png");
    }
    else
    {
        system("dot -Tpng "GRAPH_DOT_FILE" -o res_list.png");
        system("code res_list.png");
    }

        
    
    return rc;
}

// Основная функция взаимодействия с графом
int run_emulate(graph_type_t type) 
{
    int rc;
    FILE *f = fopen("test.txt", "r");
    if (!f)
        return FILE_OPEN_ERROR;

    // создание графа
    graph_any_t g = {0};
    g.type = type;
    if (type == GRAPH_TYPE_MATRIX)
    {
        graph_matr_t *temp_graph = g.graph;
        rc = graph_read_from_file(f, &temp_graph);
        g.graph = temp_graph;
    }
    else
    {
        graph_list_t *temp_graph = g.graph;
        rc = graph_list_read_from_file(f, &temp_graph);
        g.graph = temp_graph;
    }

    graph_to_png(&g);

    int cmd = EMU_START;
    while (cmd != EMU_EXIT) {
        print_cmd_list_emu();
        int rc = cmd_input(&cmd, EMU_MAX_CMD);
        if (rc != OK) {
            print_err_msg(rc);
            continue;
        }

        int from, to, value;
        switch (cmd) {
            case EMU_ADD_EDGE:
                rc = intput_vertices(&from, &to, &value);
                if (rc == OK)
                    rc = graph_add(&g, from, to, value);
                break;
            case EMU_REMOVE_EDGE:
                rc = intput_vertices_no_value(&from, &to);
                if (rc == OK)
                    rc = graph_remove(&g, from, to);
                break;
            case EMU_CHECK_CONNECTION:
                rc = intput_vertices_no_value(&from, &to);
                if (rc == OK) 
                {
                    if (graph_not_edge_any(&g, from, to))
                        printf("Вершины не соединены\n");
                    else
                        printf("Вершины соединены, стоимость перехода: %d\n", graph_path_value_any(&g, from, to));
                }
                break;
            case EMU_SHORT_PATH:
                graph_print_shortest(&g);
                break;
            case EMU_EXIT:
                system("clear");
                break;
            default:
                printf("Неизвестная команда\n");
        }

        if (rc != OK)
        {
            print_err_msg(rc);
            rc = OK;
        }

        if (cmd != EMU_EXIT)
        {
            graph_to_png(&g);
        }
    }
    graph_destroy_any(&g);

    return rc;
}
