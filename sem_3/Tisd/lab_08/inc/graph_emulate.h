#ifndef GRAPH_EMULATE_H__
#define GRAPH_EMULATE_H__

// Типы графов
typedef enum {
    GRAPH_TYPE_MATRIX = 1,
    GRAPH_TYPE_LIST = 2
} graph_type_t;

// Основная функция эмуляции работы с графом
int run_emulate(graph_type_t type); 

#endif
