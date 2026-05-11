//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "TaskManager.h"

#include <chrono>
#include <QDebug>

TaskManager::TaskManager()
{
}

bool TaskManager::add(const Task& task)
{
    auto it = std::find(_tasks.begin(), _tasks.end(), task);
    if (it == _tasks.end())
    {
        _tasks.push_back(task);
        qInfo("[Задачи] Добавлена: %s", task.to_string().c_str());
        return true;
    }

    qInfo("[Задачи] Уже существует: %s", task.to_string().c_str());
    return false;
}

bool TaskManager::remove(const Task& task)
{
    auto it = std::find(_tasks.begin(), _tasks.end(), task);
    if (it != _tasks.end())
    {
        _tasks.erase(it);
        qInfo("[Задачи] Удалена: %s", task.to_string().c_str());
        return true;
    }

    qInfo("[Задачи] Отсутствует: %s", task.to_string().c_str());
    return false;
}

void TaskManager::clear_all()
{
    _tasks.clear();
}

void TaskManager::clear_cabin(CabinID id)
{
    _tasks.erase(
        std::remove_if(
            _tasks.begin(),
            _tasks.end(),
            [id](const Task& task) { return task.get_cabin_id() == id; }
        ),
        _tasks.end()
    );
}

std::vector<Task> TaskManager::filter_tasks(std::function<bool(const Task&)> predicate) const
{
    std::vector<Task> result;
    std::copy_if(
        _tasks.begin(),
        _tasks.end(),
        std::back_inserter(result),
        predicate
    );
    return result;
}

std::vector<Task> TaskManager::get_for_cabin(CabinID id) const
{
    return filter_tasks([id](const Task& task){ return task.get_cabin_id() == id; });
}

std::vector<Task> TaskManager::get_for_floor(floor_t floor) const
{
    return filter_tasks([floor](const Task &task) { return task.get_floor() == floor; });
}

std::vector<Task> TaskManager::get_for_cabin_and_floor(CabinID id, floor_t floor) const
{
    return filter_tasks([id, floor](const Task &task)
    {
        return task.get_cabin_id() == id && task.get_floor() == floor;
    });
}

std::vector<Task> TaskManager::get_by_task(TaskType type) const
{
    return filter_tasks([type](const Task &task) { return task.get_task_type() == type; });
}


bool TaskManager::any_of(std::function<bool(const Task&)> predicate) const
{
    return std::any_of(
        _tasks.begin(),
        _tasks.end(),
        predicate
    );
}

bool TaskManager::has_for_cabin(CabinID id) const
{
    return any_of([id](const Task& task) { return task.get_cabin_id() == id; });
}

bool TaskManager::has_for_floor(floor_t floor) const
{
    return any_of([floor](const Task& task) { return task.get_floor() == floor; });
}

bool TaskManager::has_for_cabin_and_floor(CabinID id, floor_t floor) const
{
    return any_of([id, floor](const Task& task)
    {
        return task.get_cabin_id() == id && task.get_floor() == floor;
    });
}

bool TaskManager::has_any() const
{
    return !_tasks.empty();
}

bool TaskManager::has_cabin_call(CabinID id, floor_t floor) const
{
    return any_of([id, floor](const Task& task)
    {
        return task.get_cabin_id() == id && task.get_floor() == floor && task.get_task_type() == CABIN_CALL;
    });
}

bool TaskManager::has_floor_call(CabinID id, floor_t floor) const
{
    return any_of([id, floor](const Task& task)
    {
        return task.get_cabin_id() == id && task.get_floor() == floor && task.get_task_type() == FLOOR_CALL;
    });
}

size_t TaskManager::get_count_for_cabin(CabinID id) const
{
    return std::count_if(_tasks.begin(), _tasks.end(),
      [id](const Task& task) { return task.get_cabin_id() == id; }
    );
}

std::vector<Task> TaskManager::get_all() const
{
    return _tasks;
}

void TaskManager::print_tasks() const
{
    qInfo("[Задачи] === Список (всего: %lu) ===", _tasks.size());

    for (const auto &task : _tasks)
        qInfo("[Задачи]   • %s", task.to_string().c_str());

    qInfo("[Задачи] === Конец списка ===");
}
