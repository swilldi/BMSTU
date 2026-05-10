//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "Task.h"

#include <format>

Task::Task(size_t floor, Direction direction, CabinID id, TaskType type) :
    _floor(floor), _cabin_id(id), _direction(direction), _type(type) { }

size_t Task::get_floor() const
{
    return _floor;
}

CabinID Task::get_cabin_id() const
{
    return _cabin_id;
}

TaskType Task::get_task_type() const
{
    return _type;
}

bool Task::operator==(const Task& other) const
{
    return _floor == other._floor && _direction == other._direction && _cabin_id == other._cabin_id
                && _type == other._type;
}

std::string Task::to_string() const
{
    std::string msg = std::format(
        "Task: cabin = {}, floor = {}, type = {}",
        _cabin_id + 1, _floor, _type == FLOOR_CALL ? "FLOOR" : "CABIN"
    );

    return msg;
}
