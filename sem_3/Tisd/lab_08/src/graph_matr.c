#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#include "graph_matr.h"
#include "matrix.h"
#include "exit_code.h"

#include <limits.h>
#define INF UINT32_MAX


struct graph_matr_t 
{
     matrix_t vertices;   // матрица смежностей
     int vertices_count;  // количество вершин
};

graph_matr_t *graph_create(int vertices_count)
{
    graph_matr_t *graph = malloc(sizeof(graph_matr_t));
    if (graph)
    {
        graph->vertices_count = vertices_count;
        graph->vertices = matrix_create(vertices_count, vertices_count);
        if (!graph->vertices)
        {
            free(graph);
            graph = NULL;

        }

        for (int i = 0; i < vertices_count; i++)
            for (int j = 0; j < vertices_count; j++)
                graph->vertices[i][j] = INF;
    }

    return graph;
}

// Добавление ребра
int graph_add_edge(graph_matr_t *graph, int from_point, int to_point, int weight)
{
    int rc;
    if (!graph)
        return 1;
    
    if (from_point < 0 || to_point < 0)
        return 1;

    if (from_point >= graph->vertices_count || to_point >= graph->vertices_count) 
    {
        // TODO расширить матрицу
        if (from_point > to_point)
            rc = graph_extend_matrix(graph, from_point + 1);
        else
            rc = graph_extend_matrix(graph, to_point + 1);
        
        if (rc != OK)
            return rc;
        
    }
    
    if (!graph_not_edge(graph, from_point, to_point))
        return EDGE_ALREADY_EXITS;

    graph->vertices[from_point][to_point] = weight;
    return OK;
}


// Удаление ребра
int graph_remove_edge(graph_matr_t *graph, int from_point, int to_point)
{
    if (!graph)
        return 1;
    
    if (from_point >= graph->vertices_count || to_point >= graph->vertices_count || from_point < 0 || to_point < 0)
        return 1;

    // TODO check exist edge
    if (graph_not_edge(graph, from_point, to_point))
        return EDGE_NOT_EXITS;
    
    graph->vertices[from_point][to_point] = INF;
    return OK;
}


matrix_t graph_vertices(graph_matr_t *graph)
{
    return graph->vertices;
}

int graph_vertices_count(graph_matr_t *graph)
{
    return graph->vertices_count;
}




#include <stdio.h>
#define TEMP_STR_LEN 128
int max_pos_num_in_file(FILE *f, int *max_num_ptr)
{
    rewind(f);

    int max_num = 0; 
    char temp_str[TEMP_STR_LEN];
    int temp_num_1, temp_num_2;;

    while (fgets(temp_str, TEMP_STR_LEN, f) != NULL)
    {
        if (sscanf(temp_str, "%d%d", &temp_num_1, &temp_num_2) != 2)
            return READ_ERROR;
        
        if (temp_num_1 <= 0 || temp_num_2 <= 0)
            return INVALID_DATA;
            
        if (temp_num_1 > max_num)
            max_num = temp_num_1;
        if (temp_num_2 > max_num)
            max_num = temp_num_2;
    }
    
    rewind(f);
    *max_num_ptr = max_num;
    return max_num == 0 ? INVALID_DATA : OK;
}

int read_vertices(char *str, int *from_vert, int *to_vert, int *value)
{
    if (sscanf(str, "%d%d%d", from_vert, to_vert, value) != 3)
        return READ_ERROR;

    if (*from_vert < 0 || *to_vert < 0 || *value < 0)
        return INVALID_RANGE;

    return OK;

}

int intput_vertices(int *from_vert, int *to_vert, int *value)
{
    printf("Ввод в формате: <исходная_вершина> <конечная_вершина> <стоимость_перехода>\n");
    if (scanf("%d%d%d", from_vert, to_vert, value) != 3)
        return READ_ERROR;

    if (*from_vert <= 0 || *to_vert <= 0 || *value < 0)
        return INVALID_RANGE;

    *from_vert -= 1;
    *to_vert -= 1;

    return OK;

}

int intput_vertices_no_value(int *from_vert, int *to_vert)
{
    printf("Ввод в формате: <исходная_вершина> <конечная_вершина>\n");
    if (scanf("%d%d", from_vert, to_vert) != 2)
        return READ_ERROR;

    if (*from_vert < 0 || *to_vert < 0)
        return INVALID_RANGE;


    *from_vert -= 1;
    *to_vert -= 1;
    return OK;
}

bool graph_not_edge(graph_matr_t *graph, int from_vert, int to_vert)
{
    if (from_vert >= graph->vertices_count || to_vert >= graph->vertices_count)
        return true;

    return graph->vertices[from_vert][to_vert] == INF ? true : false;
}

int graph_read_from_file(FILE *f, graph_matr_t **graph_ptr)
{
    int rc = OK;

    if (!f)
        return INVALID_PARAM;

    int vert_count;
    rc = max_pos_num_in_file(f, &vert_count);
    if (rc != OK)
        return rc;

    graph_matr_t *graph = graph_create(vert_count);
    if (!graph)
        return MEM_ERROR;

    
    int from_vert, to_vert, value;
    char temp_str[TEMP_STR_LEN];
    while (fgets(temp_str, TEMP_STR_LEN, f) != NULL)
    {
        rc = read_vertices(temp_str, &from_vert, &to_vert, &value);
        if (rc != OK)
        {
            // TODO освободить память
            break;
        }

        rc = graph_add_edge(graph, from_vert - 1, to_vert - 1, value);
        if (rc != OK)
        {
            // TODO освободить память
            break;
        }
    }

    *graph_ptr = graph;

    return rc;
}

int export_graph_matr_to_dot(graph_matr_t *graph, char *filename_dot)
{
    FILE *f = fopen(filename_dot, "w");
    if (!f)
    {
        return FILE_OPEN_ERROR;
    }

    fprintf(f, "digraph G {\n");

    matrix_t vertices = graph_vertices(graph);
    int vertices_count = graph_vertices_count(graph);

    for (int i = 0; i < vertices_count; i++)
    {
        for (int j = 0; j < vertices_count; j++)
        {
            if (vertices[i][j] != INF)
            {
                fprintf(f, "  %d -> %d [label=\"%d\"];\n", i + 1, j + 1, vertices[i][j]);
            }
        }
    }
    fprintf(f, "}\n");

    fclose(f);
    return OK;
}

int graph_extend_matrix(graph_matr_t *graph, int new_count)
{
    matrix_t new_matrix = matrix_create(new_count, new_count);
    if (!new_matrix)
        return MEM_ERROR;

    for (int i = 0; i < new_count; i++)
    {
        for (int j = 0; j < new_count; j++)
        {
            if (i < graph->vertices_count && j < graph->vertices_count)
                new_matrix[i][j] = graph->vertices[i][j];
            else
                new_matrix[i][j] = INF;
        }
    }

    matrix_destoy(graph->vertices, graph->vertices_count);
    
    graph->vertices = new_matrix;
    graph->vertices_count = new_count;

    return OK;
}

int graph_path_value(graph_matr_t *graph, int from_vect, int to_vect)
{
    return graph->vertices[from_vect][to_vect];
}

matrix_t graph_shortest_paths(graph_matr_t *graph)
{
    const int n = graph->vertices_count;
    matrix_t dist = matrix_create(n, n);

    // 1) dist = копия матрицы смежности
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = graph->vertices[i][j];

    // 2) расстояние до себя = 0
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;

    // 3) Флойд–Уоршелл: k внешний
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (dist[i][k] == INF)
                continue;

            for (int j = 0; j < n; j++)
            {
                if (dist[k][j] == INF)
                    continue;

                // защита от переполнения (если INF большой)
                if (dist[i][k] > INF - dist[k][j])
                    continue;

                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    return dist;
}
