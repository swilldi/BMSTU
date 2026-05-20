//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_TASK_H
#define LAB_04_TASK_H
#include <string>

#include "defines.h"


class Task
{
public:
    Task(floor_t floor, Direction direction, CabinID id, TaskType type);

    floor_t get_floor() const;
    CabinID get_cabin_id() const;
    TaskType get_task_type() const;

    bool operator==(const Task& other) const;

    std::string to_string() const;

private:
    floor_t _floor;
    CabinID _cabin_id;
    Direction _direction;
    TaskType _type;
};


#endif //LAB_04_TASK_H