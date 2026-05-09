//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_TASKMANAGER_H
#define LAB_04_TASKMANAGER_H

#include <functional>

#include "Task/Task/Task.h"
#include <vector>

class TaskManager
{
public:
    TaskManager();

    bool add(const Task& task);
    bool remove(const Task& task);
    void clear_all();
    void clear_cabin(CabinID id);

    std::vector<Task> get_for_cabin(CabinID id) const;
    std::vector<Task> get_for_floor(size_t floor) const;
    std::vector<Task> get_for_cabin_and_floor(CabinID id, size_t floor) const;
    std::vector<Task> get_by_task(TaskType type) const;

    bool has_for_cabin(CabinID id) const;
    bool has_for_floor(size_t floor) const;
    bool has_for_cabin_and_floor(CabinID id, size_t floor) const;
    bool has_any() const;

    bool has_cabin_call(CabinID id, size_t floor) const;
    bool has_floor_call(CabinID id, size_t floor) const;

    size_t get_count_for_cabin(CabinID id) const;
    std::vector<Task> get_all() const;

private:
    std::vector<Task> _tasks;

    std::vector<Task> filter_tasks(std::function<bool(const Task&)> predicate) const;
    bool any_of(std::function<bool(const Task&)> predicate) const;

};


#endif //LAB_04_TASKMANAGER_H
