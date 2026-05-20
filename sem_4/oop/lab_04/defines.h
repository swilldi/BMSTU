//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_DEFINES_H
#define LAB_04_DEFINES_H

#include <cstddef>

using floor_t = int;

enum Direction : int
{
    DOWN = -1,
    IDLE = 0,
    UP = 1
};

enum CabinID : int
{
    FIRST,
    SECOND
};

enum TaskType: int
{
    FLOOR_CALL,
    CABIN_CALL
};

#define WAIT_TIME 1000
#define MOVE_TIME 700

#define CABINS_COUNT 2

#define DIRECTIONS_COUNT 2
#define FLOOR_COUNT 10
#define START_FLOOR 3

#endif //LAB_04_DEFINES_H