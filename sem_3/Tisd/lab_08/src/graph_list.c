#include "graph_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF UINT32_MAX

// Создание графа
graph_list_t *graph_list_create(int vertices_count)
{
    graph_list_t *graph = malloc(sizeof(graph_list_t));
    if (!graph)
        return NULL;
    graph->vertices_count = vertices_count;
    graph->adj_lists = calloc(vertices_count, sizeof(edge_t*));
    if (!graph->adj_lists)
    {
        free(graph);
        return NULL;
    }
    return graph;
}

// Добавление ребра
int graph_list_add_edge(graph_list_t *graph, int from, int to, int weight)
{
    if (!graph || from < 0 || to < 0 || from >= graph->vertices_count || to >= graph->vertices_count)
        return 1;
    edge_t *curr = graph->adj_lists[from];
    while (curr)
    {
        if (curr->to == to)
            return 2; // EDGE_ALREADY_EXISTS
        curr = curr->next;
    }
    edge_t *new_edge = malloc(sizeof(edge_t));
    if (!new_edge)
        return 3; // MEM_ERROR
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->next = graph->adj_lists[from];
    graph->adj_lists[from] = new_edge;
    return 0;
}

// Удаление ребра
int graph_list_remove_edge(graph_list_t *graph, int from, int to)
{
    if (!graph || from < 0 || to < 0 || from >= graph->vertices_count || to >= graph->vertices_count)
        return 1;
    edge_t **curr = &graph->adj_lists[from];
    while (*curr)
    {
        if ((*curr)->to == to)
        {
            edge_t *to_delete = *curr;
            *curr = (*curr)->next;
            free(to_delete);
            return 0;
        }
        curr = &(*curr)->next;
    }
    return 2; // EDGE_NOT_EXISTS
}

// Проверка отсутствия ребра
bool graph_list_not_edge(graph_list_t *graph, int from, int to)
{
    if (!graph || from < 0 || to < 0 || from >= graph->vertices_count || to >= graph->vertices_count)
        return true;
    edge_t *curr = graph->adj_lists[from];
    while (curr)
    {
        if (curr->to == to)
            return false;
        curr = curr->next;
    }
    return true;
}

// Освобождение памяти
def void graph_list_destroy(graph_list_t *graph)
{
    if (!graph)
        return;
    for (int i = 0; i < graph->vertices_count; i++)
    {
        edge_t *curr = graph->adj_lists[i];
        while (curr)
        {
            edge_t *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->adj_lists);
    free(graph);
}

// Количество вершин
int graph_list_vertices_count(graph_list_t *graph)
{
    return graph ? graph->vertices_count : 0;
}

// Вес пути между двумя вершинами
int graph_list_path_value(graph_list_t *graph, int from, int to)
{
    if (!graph || from < 0 || to < 0 || from >= graph->vertices_count || to >= graph->vertices_count)
        return INF;
    edge_t *curr = graph->adj_lists[from];
    while (curr)
    {
        if (curr->to == to)
            return curr->weight;
        curr = curr->next;
    }
    return INF;
}

// Чтение графа из файла
int graph_list_read_from_file(FILE *f, graph_list_t **graph_ptr)
{
    if (!f)
        return 1;
    int max_num = 0;
    char buf[128];
    int from, to, weight;
    rewind(f);
    while (fgets(buf, sizeof(buf), f))
    {
        if (sscanf(buf, "%d%d%d", &from, &to, &weight) == 3)
        {
            if (from > max_num) max_num = from;
            if (to > max_num) max_num = to;
        }
    }
    if (max_num == 0)
        return 2;
    graph_list_t *graph = graph_list_create(max_num);
    if (!graph)
        return 3;
    rewind(f);
    while (fgets(buf, sizeof(buf), f))
    {
        if (sscanf(buf, "%d%d%d", &from, &to, &weight) == 3)
        {
            graph_list_add_edge(graph, from - 1, to - 1, weight);
        }
    }
    *graph_ptr = graph;
    return 0;
}

// Экспорт в DOT
int export_graph_list_to_dot(graph_list_t *graph, char *filename_dot)
{
    FILE *f = fopen(filename_dot, "w");
    if (!f)
        return 1;
    fprintf(f, "digraph G {\n");
    for (int i = 0; i < graph->vertices_count; i++)
    {
        edge_t *curr = graph->adj_lists[i];
        while (curr)
        {
            fprintf(f, "  %d -> %d [label=\"%d\"];\n", i + 1, curr->to + 1, curr->weight);
            curr = curr->next;
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    return 0;
}
