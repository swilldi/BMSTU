//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "Task.h"

#include <format>

Task::Task(size_t floor, CabinID id, TaskType type) : _floor(floor), _cabin_id(id), _type(type)
{
}

bool Task::operator==(const Task& other) const
{
    return _floor == other._floor && _cabin_id == other._cabin_id && _type == other._type;
}

std::string Task::to_string() const
{
    std::string msg = std::format(
        "Task: cabin = {}, floor = {}, type = {}",
        _cabin_id + 1, _floor, _type == FLOOR_CALL ? "FLOOR" : "CABIN"
    );

    return msg;
}
