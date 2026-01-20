#ifndef SORT_FIELD_H__
#define SORT_FIELD_H__

typedef enum
{
    INVALID,
    TITLE,
    DIRECTOR,
    YEAR
} field;

typedef union 
{
    char *str;
    int num;
} field_value;

#endif
