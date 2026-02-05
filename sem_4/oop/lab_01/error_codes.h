#ifndef ERROR_CODES_H
#define ERROR_CODES_H

enum error_code
{
    OK = 0,

    // Ошибки файла
    FILE_OPEN_ERR,
    INVALID_FILE_ERR,
    INVALID_FILE_DATA,
    INVALID_DATA_RANGE,


    // Ошибки с памятью
    MEMORY_ERR,

    //



};

using error_code = enum error_code;

void print_error_message(const error_code &rc);

#endif // ERROR_CODES_H
