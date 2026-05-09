//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_DEFINES_H
#define LAB_04_DEFINES_H

#include <cstddef>

enum Direction : size_t
{
    DOWN,
    STAY,
    UP
};

enum CabinID : size_t
{
    FIRST,
    SECOND
};

enum TaskType: size_t
{
    FLOOR_CALL,
    CABIN_CALL
};

#define WAIT_TIME 1000

#endif //LAB_04_DEFINES_H