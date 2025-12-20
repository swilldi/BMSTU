#ifndef GRAPH_LIST_H__
#define GRAPH_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Структура ребра
typedef struct edge_t {
    int to;
    int weight;
    struct edge_t *next;
} edge_t;

// Структура графа на списках
typedef struct graph_list_t {
    edge_t **adj_lists; // массив списков смежности
    int vertices_count;
} graph_list_t;

graph_list_t *graph_list_create(int vertices_count);
int graph_list_add_edge(graph_list_t *graph, int from, int to, int weight);
int graph_list_remove_edge(graph_list_t *graph, int from, int to);
bool graph_list_not_edge(graph_list_t *graph, int from, int to);
void graph_list_destroy(graph_list_t *graph);
int graph_list_vertices_count(graph_list_t *graph);
int graph_list_path_value(graph_list_t *graph, int from, int to);
unsigned int **graph_list_shortest_paths(graph_list_t *graph);
size_t graph_list_memory_capacity(graph_list_t *graph);
int graph_list_read_from_file(FILE *f, graph_list_t **graph_ptr);
int export_graph_list_to_dot(graph_list_t *graph, char *filename_dot);
int graph_list_extend(graph_list_t *graph, int new_count);

#endif
