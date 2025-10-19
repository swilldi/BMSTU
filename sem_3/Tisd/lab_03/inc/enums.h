#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum
{
    INPUT,
    OUTPUT
} command_t;

typedef enum
{
    CLASSIC_INPUT = 1,
    COORD_INPUT,
    CLASSIC_FILE,
    COORD_FILE,
    COMPARE
} input_command_t;
#define INPUT_CMD_MAX COMPARE

typedef enum 
{
    EXIT = 0,
    MATRIX,
    COORD,
    CSR
} output_command_t;
#define OUTPUT_CMD_MAX CSR

typedef enum 
{ 
    TYPE_NONE = 0, 
    TYPE_CSR, 
    TYPE_CSC 
} type_matrixt;

#endif
