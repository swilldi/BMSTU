#ifndef GRAPH_H__
#define GRAPH_H__

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include <stdbool.h>

typedef struct graph_matr_t graph_matr_t;

graph_matr_t *graph_create(int points_count);
int graph_add_edge(graph_matr_t *graph, int from_point, int to_point, int weight);
int graph_remove_edge(graph_matr_t *graph, int from_point, int to_point);
matrix_t graph_vertices(graph_matr_t *graph);
int graph_vertices_count(graph_matr_t *graph);
int graph_read_from_file(FILE *, graph_matr_t **graph_ptr);
int export_graph_matr_to_dot(graph_matr_t *graph, char *filename_dot);
int intput_vertices(int *from_vert, int *to_vert, int *value);
bool graph_not_edge(graph_matr_t *graph, int from_vert, int to_vert);
int intput_vertices_no_value(int *from_vert, int *to_vert);
int graph_extend_matrix(graph_matr_t *graph, int new_count);
int graph_path_value(graph_matr_t *graph, int from_vect, int to_vect);
matrix_t graph_shortest_paths(graph_matr_t *graph);
void graph_destroy(graph_matr_t *graph);
size_t graph_memory_capacity(graph_matr_t *graph);

#endif
