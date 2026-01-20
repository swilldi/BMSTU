#ifndef ITEM_STRUCT_H__
#define ITEM_STRUCT_H__

#include <stdint.h>

typedef struct
{
    char label[31];
    char producer[16];
    uint32_t prise;
    uint32_t count;
} item_t;

#endif
