#ifndef ERROR_CODES_H
#define ERROR_CODES_H

enum error_code
{
    OK = 0,

    // Ошибки файла
    FILE_OPEN_ERR,
    FILE_INVALID,
    FILE_INVALID_TYPE_DATA,
    FILE_DATA_INVALID_RANGE,

    // Ошибки с памятью
    MEMORY_ERR,

    MODEL_NOT_LOADED,

    // Ошибки с сценой для отрисовки
    DRAW_SCENE_SCENE_INVALID,
    DRAW_SCENE_WIDTH_INVALID_RANGE,
    DRAW_SCENE_HEIGHT_INVALID_RANGE,

    // Ошибки с ребрами
    EDGES_INVALID,
    EDGES_EMPTY,

    // Ошибки с точками
    POINTS_INVALID,
    POINTS_EMPTY,

};

using error_code = enum error_code;

void print_error_message(const error_code rc);
void error_message_box(const error_code rc);

#endif // ERROR_CODES_H
