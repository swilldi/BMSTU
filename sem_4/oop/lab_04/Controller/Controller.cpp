//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "Controller.h"

namespace
{
    // === Единый формат отладочных сообщений ===
    // [Контроллер] ...   — глобальные события контроллера
    // [Лифт N] ...       — действия конкретного лифта (N — 1-based)
    // Направление выводится словом (вверх / вниз / стоит).
    inline const char* dir_str(Direction d)
    {
        switch (d)
        {
            case UP:   return "вверх";
            case DOWN: return "вниз";
            case IDLE: return "стоит";
        }
        return "?";
    }
} // namespace

Controller::Controller(QObject* parent) : QObject(parent)
{
    setup_cabins();
    setup_cabin_buttons();
    setup_floor_buttons();
    setup_internal_connection();
}

Controller::~Controller() { }

void Controller::setup_cabins()
{
    for (size_t i = 0; i < CABINS_COUNT; ++i)
    {
        _cabins[i] = std::make_unique<Cabin>(static_cast<CabinID>(i), this);
        _current_floor[i] = START_FLOOR - 1;
        _current_directions[i] = IDLE;
        _preferred_directions[i] = UP;


        connect(_cabins[i].get(), &Cabin::cabin_end_boarding_signal, this, &Controller::reach_dst_floor_slot);
        connect(&_cabins[i]->move_timer, &QTimer::timeout, this, [=, this]
        {
            manage_move_slot(static_cast<CabinID>(i));
        });
    }
}

void Controller::setup_floor_buttons()
{
    for (size_t i = 0; i < FLOOR_COUNT; ++i)
    {
        const floor_t floor = static_cast<floor_t>(i) + 1;
        _floor_buttons[i] = std::make_shared<FloorButton>(floor);

        // Лямбда отвечает только за обратную связь UI (смена цвета).
        // Бизнес-логика (создание задачи, выбор кабины, запуск планировщика)
        // выполняется в floor_destination_slot — точке входа для события нажатия.
        connect(_floor_buttons[i].get(), &FloorButton::activate_signal, this, [this, floor]
        {
            emit floor_button_change_color_signal(floor, true);
        });

        connect(_floor_buttons[i].get(), &FloorButton::deactivate_signal, this, [this, floor]
        {
            emit floor_button_change_color_signal(floor, false);
        });
    }
}

void Controller::setup_cabin_buttons()
{
    // === Создание и настройка кнопок ===
    for (size_t c = 0; c < CABINS_COUNT; ++c)
    {
        const CabinID id = static_cast<CabinID>(c);
        for (size_t i = 0; i < FLOOR_COUNT; ++i)
        {
            const floor_t floor = static_cast<floor_t>(i) + 1;
            _cabin_buttons[id][i] = std::make_shared<CabinButton>(floor, id);

            // Лямбда отвечает только за обратную связь UI (смена цвета).
            // Бизнес-логика — в cabin_destination_slot.
            connect(_cabin_buttons[id][i].get(), &CabinButton::activate_signal, this, [this, id, floor]
            {
                emit cabin_button_change_color_signal(floor, id, true);
            });

            connect(_cabin_buttons[id][i].get(), &CabinButton::deactivate_signal, this, [this, id, floor]
            {
                emit cabin_button_change_color_signal(floor, id, false);
            });
        }
    }
}


void Controller::setup_internal_connection()
{
    // TODO в теории они вообще не нужны и можно вызывать эти методы напрямую из слотов
    connect(this, &Controller::free_cabin_signal, this, [this](CabinID id)
    {
        _cabins[id]->cabin_free_slot();
    });
    connect(this, &Controller::move_cabin_signal, this, [this](CabinID id, floor_t floor, Direction direction)
    {
        _cabins[id]->cabin_moving_slot(floor, direction);
    });
    connect(this, &Controller::stop_cabin_signal, this, [this](CabinID id, floor_t floor)
    {
        _cabins[id]->cabin_start_boarding_slot(floor);
    });

    //
    connect(this, &Controller::button_deactivated_signal, this, &Controller::manage_cabin_slot);
    connect(this, &Controller::free_controller_signal, this, &Controller::free_controller_slot);

    // Начальная позиция лифтов
    for (size_t i = 0; i < CABINS_COUNT; ++i)
        emit cabin_position_change_signal(static_cast<CabinID>(i), START_FLOOR);
}

void Controller::floor_destination_slot(floor_t floor)
{
    qInfo("[Контроллер] Вызов лифта на этаж %d", floor);

    // Контроллер принимает новые запросы только если он не в середине обработки
    // другого (REQUEST/REACH_DST_FLOOR — переходные состояния).
    if (_state != FREE && _state != MANAGING_CABIN && _state != MANAGING_MOVE)
    {
        qInfo("[Контроллер] Запрос отклонён: занят (state=%d)", _state);
        return;
    }

    for (size_t i = 0; i < CABINS_COUNT; ++i)
    {
        const CabinID id = static_cast<CabinID>(i);
        if (_task_manager.has_floor_call(id, floor))
        {
            qInfo("[Контроллер] Запрос отклонён: вызов на этаж %d уже закреплён за лифтом %lu",
                  floor, id + 1);
            return;
        }
    }

    // Выбор кабины по минимальному весу (упрощённый SCAN)
    CabinID decided_id = CabinID::FIRST;
    double best_weight = std::numeric_limits<double>::max();

    for (size_t i = 0; i < CABINS_COUNT; ++i)
    {
        const CabinID id = static_cast<CabinID>(i);
        const double current_weight = cabin_weight(id, floor, _current_directions[id]);
        if (current_weight < best_weight)
        {
            best_weight = current_weight;
            decided_id = id;
        }

        qInfo("[Контроллер] [Лифт %lu] вес=%.2f (этаж=%d, направление=%s)",
              id + 1, current_weight, _current_floor[id] + 1, dir_str(_current_directions[id]));
    }

    qInfo("[Контроллер] Выбран лифт %lu (вес=%.2f) для этажа %d",
          decided_id + 1, best_weight, floor);

    _task_manager.print_tasks();
    Task new_task(floor, IDLE, decided_id, FLOOR_CALL);
    _task_manager.add(new_task);

    _floor_buttons[floor - 1]->activate();   // UI feedback через сигнал кнопки

    _state = FLOOR_REQUEST;
    manage_cabin_slot(decided_id);
}

void Controller::cabin_destination_slot(floor_t floor, CabinID id)
{
    qInfo("[Контроллер] Запрос из кабины %lu на этаж %d", id + 1, floor);

    if (_state != FREE && _state != MANAGING_CABIN && _state != MANAGING_MOVE)
    {
        qInfo("[Контроллер] Запрос отклонён: занят (state=%d)", _state);
        return;
    }

    if (_task_manager.has_cabin_call(id, floor))
    {
        qInfo("[Контроллер] Запрос отклонён: задача уже существует");
        return;
    }

    Task new_task(floor, IDLE, id, CABIN_CALL);
    _task_manager.add(new_task);

    _cabin_buttons[id][floor - 1]->activate();   // UI feedback

    _state = CABIN_REQUEST;
    manage_cabin_slot(id);
}

void Controller::manage_move_slot(CabinID id)
{
    if (_state != MANAGING_CABIN)
        return;

    _state = MANAGING_MOVE;
    const floor_t from = _current_floor[id] + 1;
    _current_floor[id] += _current_directions[id];
    const floor_t to = _current_floor[id] + 1;

    qInfo("[Лифт %lu] Прошёл этаж %d → %d (направление=%s)",
          id + 1, from, to, dir_str(_current_directions[id]));

    emit cabin_position_change_signal(id, to);
    manage_cabin_slot(id);
}


static constexpr floor_t FLOOR_NOT_FOUND = -1;

void Controller::manage_cabin_slot(CabinID id)
{
    if (_state == FREE || _state == MANAGING_CABIN)
        return;

    _state = MANAGING_CABIN;
    const floor_t next_floor = get_next_visit_floor(id);
    if (next_floor == FLOOR_NOT_FOUND)
    {
        qInfo("[Лифт %lu] Задач нет — освобождён", id + 1);
        _current_directions[id] = IDLE;
        emit free_cabin_signal(id);
    }
    else if (next_floor > _current_floor[id])
    {
        qInfo("[Лифт %lu] Едем вверх (текущий=%d, целевой=%d)",
              id + 1, _current_floor[id] + 1, next_floor + 1);
        _current_directions[id] = UP;
        emit move_cabin_signal(id, _current_floor[id], UP);
    }
    else if (next_floor < _current_floor[id])
    {
        qInfo("[Лифт %lu] Едем вниз (текущий=%d, целевой=%d)",
              id + 1, _current_floor[id] + 1, next_floor + 1);
        _current_directions[id] = DOWN;
        emit move_cabin_signal(id, _current_floor[id], DOWN);
    }
    else
    {
        qInfo("[Лифт %lu] Остановка на этаже %d", id + 1, _current_floor[id] + 1);
        _current_directions[id] = get_next_direction(id);
        emit stop_cabin_signal(id, _current_floor[id]);
    }

    if (!_task_manager.has_any())
        emit free_controller_signal();
}

void Controller::reach_dst_floor_slot(CabinID id)
{
    if (_state != MANAGING_CABIN)
        return;

    _state = REACH_DST_FLOOR;
    const floor_t floor = _current_floor[id] + 1;

    qInfo("[Лифт %lu] === Обработка задач на этаже %d ===", id + 1, floor);
    qInfo("[Лифт %lu] Задач до удаления: %lu", id + 1, _task_manager.get_count_for_cabin(id));

    if (_task_manager.has_cabin_call(id, floor))
    {
        Task task(floor, IDLE, id, CABIN_CALL);
        _task_manager.remove(task);
        _cabin_buttons[id][_current_floor[id]]->deactivate();
    }

    if (_task_manager.has_floor_call(id, floor))
    {
        Task task(floor, IDLE, id, FLOOR_CALL);
        _task_manager.remove(task);
        _floor_buttons[_current_floor[id]]->deactivate();
    }

    qInfo("[Лифт %lu] Задач после удаления: %lu", id + 1, _task_manager.get_count_for_cabin(id));
    _task_manager.print_tasks();

    _current_directions[id] = IDLE;

    emit button_deactivated_signal(id);
}

void Controller::free_controller_slot()
{
    if (_state == FREE)
        return;

    _state = FREE;
    qInfo("[Контроллер] Все задачи выполнены");
}

Direction Controller::get_direction(int diff)
{
    if (diff == 0)
        return IDLE;
    if (diff > 0)
        return UP;

    return DOWN;
}

floor_t Controller::get_next_visit_floor(CabinID id)
{
    std::vector<Task> tasks = _task_manager.get_for_cabin(id);

    if (tasks.empty())
    {
        qInfo("[Лифт %lu] Задач нет", id + 1);
        return FLOOR_NOT_FOUND;
    }

    const floor_t floor = _current_floor[id] + 1;
    qInfo("[Лифт %lu] Поиск следующего этажа (задач: %lu, текущий этаж: %d, направление: %s)",
          id + 1, tasks.size(), floor, dir_str(_current_directions[id]));

    // Важно: проверяем задачу именно ЭТОЙ кабины. Раньше использовался
    // has_for_floor (по всем кабинам) — из-за этого одна кабина «реагировала»
    // на задачи другой, что приводило к нарушению параллельной работы.
    if (_task_manager.has_for_cabin_and_floor(id, floor))
    {
        qInfo("[Лифт %lu] Есть задача на текущем этаже %d → остановка", id + 1, floor);
        return _current_floor[id];
    }

    if (_current_directions[id] == IDLE)
    {
        // Проверяем, есть ли задачи в предпочтительном направлении
        bool has_tasks_in_preferred = false;
        bool has_tasks_in_opposite = false;

        for (const auto& task : tasks)
        {
            if (_preferred_directions[id] == UP && task.get_floor() > floor)
                has_tasks_in_preferred = true;
            else if (_preferred_directions[id] == DOWN && task.get_floor() < floor)
                has_tasks_in_preferred = true;
            else if (_preferred_directions[id] == UP && task.get_floor() < floor)
                has_tasks_in_opposite = true;
            else if (_preferred_directions[id] == DOWN && task.get_floor() > floor)
                has_tasks_in_opposite = true;
        }

        qInfo("[Лифт %lu] Стоит: предпочтительное=%s, задачи по ходу=%s, в обратном=%s",
              id + 1, dir_str(_preferred_directions[id]),
              has_tasks_in_preferred ? "да" : "нет",
              has_tasks_in_opposite ? "да" : "нет");

        if (has_tasks_in_preferred)
        {
            const floor_t target_floor = next_floor_in_direction(id, _preferred_directions[id], floor);
            if (target_floor != FLOOR_NOT_FOUND)
                return target_floor;
        }
        else if (has_tasks_in_opposite)
        {
            _preferred_directions[id] = (_preferred_directions[id] == UP) ? DOWN : UP;
            qInfo("[Лифт %lu] Разворот: новое предпочтительное направление=%s",
                  id + 1, dir_str(_preferred_directions[id]));

            if (_preferred_directions[id] == UP)
            {
                for (floor_t new_floor = floor + 1; new_floor <= FLOOR_COUNT; ++new_floor)
                {
                    if (_task_manager.has_cabin_call(id, new_floor) || _task_manager.has_floor_call(id, new_floor))
                    {
                        qInfo("[Лифт %lu] После разворота едем вверх к этажу %d", id + 1, new_floor);
                        return new_floor - 1;
                    }
                }
            }
            else
            {
                for (floor_t new_floor = floor - 1; new_floor >= 1; --new_floor)
                {
                    if (_task_manager.has_cabin_call(id, new_floor) || _task_manager.has_floor_call(id, new_floor))
                    {
                        qInfo("[Лифт %lu] После разворота едем вниз к этажу %d", id + 1, new_floor);
                        return new_floor - 1;
                    }
                }
            }
        }
        qInfo("[Лифт %lu] Нет задач ни в одном направлении", id + 1);
        return FLOOR_NOT_FOUND;
    }
    else
    {
        const floor_t target_floor = next_floor_in_direction(id, _current_directions[id], floor);
        if (target_floor != FLOOR_NOT_FOUND)
            return target_floor;
    }

    qInfo("[Лифт %lu] Целевой этаж не найден", id + 1);
    return FLOOR_NOT_FOUND;
}

Direction Controller::get_next_direction(CabinID id)
{
    std::vector<Task> tasks = _task_manager.get_for_cabin(id);

    if (tasks.empty())
        return IDLE;

    if (_current_directions[id] == IDLE)
    {
        floor_t dst_visit_floor = FLOOR_NOT_FOUND;
        int min_dst = FLOOR_COUNT + 1;

        for (const auto& task : tasks)
        {
            const int diff = std::abs(_current_floor[id] + 1 - task.get_floor());
            if (diff > 0 && diff < min_dst)
            {
                min_dst = diff;
                dst_visit_floor = task.get_floor();
            }
        }

        if (dst_visit_floor == FLOOR_NOT_FOUND)
            return IDLE;
        else if (dst_visit_floor > _current_floor[id] + 1)
            return UP;
        else
            return DOWN;
    }

    const floor_t target_floor = get_next_visit_floor(id);
    if (target_floor == FLOOR_NOT_FOUND)
        return IDLE;

    const floor_t target_real_floor = target_floor + 1;
    const floor_t current_real_floor = _current_floor[id] + 1;

    qInfo("[Лифт %lu] Текущий этаж=%d, целевой=%d", id + 1, current_real_floor, target_real_floor);

    if (target_real_floor > current_real_floor)
        return UP;
    else if (target_real_floor < current_real_floor)
        return DOWN;
    else
        return IDLE;
}

#define DISTANCE_COEF 10.0
#define TASK_COUNT_COEF 20.0
double Controller::cabin_weight(CabinID id, floor_t target_floor, Direction direction)
{
    double weight = 0;
    const int distance = std::abs(target_floor - (_current_floor[id] + 1));
    weight += distance * DISTANCE_COEF;

    const int task_count = static_cast<int>(_task_manager.get_count_for_cabin(id));
    weight += task_count * TASK_COUNT_COEF;

    if (_current_directions[id] == IDLE)
    {
        // свободный лифт
        weight -= 15;
    }
    else
    {
        const int cur_dist = target_floor - (_current_floor[id] + 1);
        const Direction move_direction = get_direction(cur_dist);

        if (_current_directions[id] == move_direction && _current_directions[id] == direction)
            weight -= 25;  // движение в приоритетном направлении
        else if (_current_directions[id] != move_direction)
            weight += 30;
    }

    if (_current_directions[id] != IDLE)
    {
        const int cur_dist = target_floor - (_current_floor[id] + 1);
        const Direction required_direction = get_direction(cur_dist);

        if (_current_directions[id] != required_direction && required_direction != IDLE)
            weight += 15;
    }

    return weight;
}

floor_t Controller::next_floor_in_direction(CabinID id, Direction direction, floor_t current_floor)
{
    if (direction == UP)
    {
        // Самый верхний floor_call (для разворота в конце поездки)
        floor_t furthest_up_call = FLOOR_NOT_FOUND;
        for (floor_t floor = FLOOR_COUNT; floor >= current_floor + 1; --floor)
            if (_task_manager.has_floor_call(id, floor))
            {
                furthest_up_call = floor;
                break;
            }

        for (floor_t floor = current_floor + 1; floor <= FLOOR_COUNT; ++floor)
        {
            if (_task_manager.has_cabin_call(id, floor) || _task_manager.has_floor_call(id, floor))
            {
                if (furthest_up_call != FLOOR_NOT_FOUND && floor < furthest_up_call)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по пути к конечному этажу %d",
                          id + 1, floor, furthest_up_call);
                    return floor - 1;
                }
                else if (furthest_up_call == FLOOR_NOT_FOUND)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по ходу вверх", id + 1, floor);
                    return floor - 1;
                }
            }
        }

        if (furthest_up_call != FLOOR_NOT_FOUND)
        {
            qInfo("[Лифт %lu] Едет к этажу %d для смены направления", id + 1, furthest_up_call);
            return furthest_up_call - 1;
        }
    }
    else if (direction == DOWN)
    {
        // Самый нижний floor_call (для разворота в конце поездки)
        floor_t furthest_down_call = FLOOR_NOT_FOUND;
        for (floor_t floor = 1; floor <= current_floor - 1; ++floor)
        {
            if (_task_manager.has_floor_call(id, floor))
            {
                furthest_down_call = floor;
                break;
            }
        }

        for (floor_t floor = current_floor - 1; floor >= 1; --floor)
        {
            if (_task_manager.has_cabin_call(id, floor) || _task_manager.has_floor_call(id, floor))
            {
                if (furthest_down_call != FLOOR_NOT_FOUND && floor > furthest_down_call)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по пути к конечному этажу %d",
                          id + 1, floor, furthest_down_call);
                    return floor - 1;
                }
                else if (furthest_down_call == FLOOR_NOT_FOUND)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по ходу вниз", id + 1, floor);
                    return floor - 1;
                }
            }
        }

        if (furthest_down_call != FLOOR_NOT_FOUND)
        {
            qInfo("[Лифт %lu] Едет к этажу %d для смены направления", id + 1, furthest_down_call);
            return furthest_down_call - 1;
        }
    }

    return FLOOR_NOT_FOUND;
}
