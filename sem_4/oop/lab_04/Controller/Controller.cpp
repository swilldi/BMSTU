//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "Controller.h"

#define ELEVATOR_WEIGHT_MESSAGE "[Вес лифта %lu]: %.2f (этаж – %lu; направление – %lu)"
#define BEST_ELEVATOR_WEIGHT_MESSAGE "Выбран лифт %d с весом %.2f для этажа %d (направление %s)"

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
        const size_t floor = i + 1;
        _floor_buttons[i] = std::make_shared<FloorButton>(floor);

        connect(_floor_buttons[i].get(), &FloorButton::activate_signal, this, [this, i, floor]
        {
            CabinID id = get_deside_cabin_id(i);
            manage_cabin_slot(id);
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
            const size_t floor = i + 1;
            _cabin_buttons[id][i] = std::make_shared<CabinButton>(floor, id);

            connect(_cabin_buttons[id][i].get(), &CabinButton::activate_signal, this, [this, id, floor]
            {
                manage_cabin_slot(id);
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
    connect(this, &Controller::move_cabin_signal, this, [this](CabinID id, size_t floor, Direction direction)
    {
        _cabins[id]->cabin_moving_slot(floor, direction);
    });
    connect(this, &Controller::stop_cabin_signal, this, [this](CabinID id, size_t floor)
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

void Controller::floor_destanation_slot(size_t floor, Direction direction)
{
    if (_state != FREE && _state != MANAGING_CABIN && _state != MANAGING_MOVE)
        return;

    for (size_t i = CabinID::FIRST; i < CABINS_COUNT; ++i)
    {
        CabinID id = static_cast<CabinID>(i);
        if (_task_manager.has_for_floor(floor))
            return;
    }

    for (size_t id = CabinID::FIRST; id < CABINS_COUNT; ++id)
    {
        if (_current_floor[id] == floor - 1 && _current_directions[id] == IDLE)
        {
            emit stop_cabin_signal(static_cast<CabinID>(id), _current_floor[id]);
            return;
        }
    }

    _state = FLOOR_REQUEST;
    CabinID desided_id = CabinID::FIRST;
    double best_weight = std::numeric_limits<double>::max();

    for (size_t i = 0; i < CABINS_COUNT; ++i)
    {
        const CabinID id = static_cast<CabinID>(i);
        double current_weight = cabin_weight(id, floor, direction);
        if (current_weight < best_weight)
        {
            best_weight = current_weight;
            desided_id = id;
        }


        qInfo(ELEVATOR_WEIGHT_MESSAGE, id + 1, current_weight, floor, direction);
    }

    qInfo(BEST_ELEVATOR_WEIGHT_MESSAGE, desided_id, best_weight, floor, direction == UP ? "Вверх" : "Вниз");

    _task_manager.print_tasks();
    Task new_task(floor, direction, desided_id, FLOOR_CALL);
    _task_manager.add(new_task);

    emit _floor_buttons[floor - 1]->activate_signal();
}

void Controller::cabin_destanation_slot(size_t floor, CabinID id)
{
    if (_state != FREE && _state != MANAGING_CABIN && _state != MANAGING_MOVE)
        return;

    if (_task_manager.has_cabin_call(id, floor))
        return;

    _state = CABIN_REQUEST;

    Task new_task(floor, IDLE, id, CABIN_CALL);
    _task_manager.add(new_task);

    emit _cabin_buttons[id][floor - 1]->activate_signal();
}

void Controller::manage_move_slot(CabinID id)
{
    if (_state != MANAGING_CABIN)
        return;

    _state = MANAGING_MOVE;
    _current_floor[id] += _current_directions[id];

    emit cabin_position_change_signal(id, _current_floor[id] + 1);
    emit manage_cabin_slot(id);
}


#define FLOOR_NOT_FOUND -1

void Controller::manage_cabin_slot(CabinID id)
{
    if (_state == FREE || _state == MANAGING_CABIN)
        return;

    _state = MANAGING_CABIN;
    size_t next_floor = get_next_visit_floor(id);
    if (next_floor == FLOOR_NOT_FOUND)
    {
        _current_directions[id] = IDLE;
        emit free_cabin_signal(id);
    }
    else if (next_floor > _current_floor[id])
    {
        _current_directions[id] = UP;
        emit move_cabin_signal(id, _current_floor[id], UP);
    }
    else if (next_floor < _current_directions[id])
    {
        _current_directions[id] = DOWN;
        emit move_cabin_signal(id, _current_floor[id], DOWN);
    }
    else
    {
        _current_directions[id] = get_next_direction(id);
        emit stop_cabin_signal(id, _current_floor[id]);
    }

    if (all_cabins_free())
        emit free_controller_signal();
}

void Controller::reach_dst_floor_slot(CabinID id)
{
    if (_state != MANAGING_CABIN)
        return;

    _state = REACH_DST_FLOOR;
    size_t floor = _current_floor[id] + 1;

    qInfo("=== Обработка задач лифта %lu на этаже %lu ===", id + 1, floor);

    qInfo("Задач до удаления: %lu", _task_manager.get_count_for_cabin(id));

    if (_task_manager.has_cabin_call(id, floor))
    {
        Task task(floor, IDLE, id, CABIN_CALL);
        _task_manager.remove(task);
        emit _cabin_buttons[id][_current_floor[id]]->deactivate_signal();
    }

    if (_task_manager.has_floor_call(id, floor))
    {
        Task task(floor, IDLE, id, FLOOR_CALL);
        _task_manager.remove(task);
        emit _floor_buttons[_current_floor[id]]->deactivate_signal();
    }

    qInfo("Задач после удаления: %lu", _task_manager.get_count_for_cabin(id));
    qInfo("=== Состояние всех задач после остановки ===");
    _task_manager.print_tasks();

    _current_directions[id] = IDLE;

    emit button_deactivated_signal(id);
}

void Controller::free_controller_slot()
{
    if (_state == FREE)
        return;

    _state = FREE;
    qInfo("[Контролер] Активных задач нет");
}

Direction Controller::get_direction(int diff)
{
    if (diff == 0)
        return IDLE;
    if (diff > 0)
        return UP;
    if (diff < 0)
        return DOWN;
}

CabinID Controller::get_deside_cabin_id(size_t floor)
{
    for (size_t i = 0; i < CABINS_COUNT; ++i)
    {
        if (_task_manager.has_for_floor(floor))
            return static_cast<CabinID>(i);
    }

    // TODO сделать более рациональный выбор
    return CabinID::FIRST;
}

size_t Controller::get_next_visit_floor(CabinID id)
{
    std::vector<Task> tasks = _task_manager.get_for_cabin(id);

    if (tasks.empty())
    {
        qInfo("[Лифт %lu] Задача нет", id);
        return FLOOR_NOT_FOUND;
    }

    size_t floor = _current_floor[id] + 1;
    qInfo("[Лифт %lu] Поиск следующего этажа (кол-во текущих задач: %lu, текущий этаж: %lu, направление %d)", id,
          tasks.size(), floor, _current_directions[id]);


    bool floor_already_call = false;
    if (_task_manager.has_for_floor(floor))
    {
        qInfo("[Лифт %lu] Задача для этажа %lu уже существует", id, floor);
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
            {
                // При движении вверх: подбираем ВСЕ задачи на этажах выше
                has_tasks_in_preferred = true;
            }
            else if (_preferred_directions[id] == DOWN && task.get_floor() < floor)
            {
                // При движении вниз: подбираем ВСЕ задачи на этажах ниже
                has_tasks_in_preferred = true;
            }
            else if (_preferred_directions[id] == UP && task.get_floor() < floor)
            {
                // Задачи в обратном направлении (для разворота)
                has_tasks_in_opposite = true;
            }
            else if (_preferred_directions[id] == DOWN && task.get_floor() > floor)
            {
                // Задачи в обратном направлении (для разворота)
                has_tasks_in_opposite = true;
            }
        }

        qInfo("[Лифт %lu] стоит: предпочтительное направление=%d, задачи в направлении=%s, задачи в обратном=%s",
              id, _preferred_directions[id],
              has_tasks_in_preferred ? "да" : "нет",
              has_tasks_in_opposite ? "да" : "нет");

        if (has_tasks_in_preferred)
        {
            size_t target_floor = next_floor_in_direction(id, _preferred_directions[id], floor);
            if (target_floor != FLOOR_NOT_FOUND)
                return target_floor;
        }
        else if (has_tasks_in_opposite)
        {
            _preferred_directions[id] = (_preferred_directions[id] == UP) ? DOWN : UP;
            qInfo("[Лифт %lu] Изменение направление. Новое направление %d", id, _preferred_directions[id]);

            if (_preferred_directions[id] == UP)
            {
                for (size_t new_floor = floor + 1; new_floor < FLOOR_COUNT; ++new_floor)
                {
                    if (_task_manager.has_cabin_call(id, new_floor) || _task_manager.has_floor_call(id, new_floor))
                    {
                        qInfo("Лифт %lu: после разворота едем вверх к этажу %lu", id, new_floor);
                        return new_floor + 1;
                    }
                }
            }
            else
            {
                for (size_t new_floor = floor - 1; new_floor < FLOOR_COUNT; --new_floor)
                {
                    if (_task_manager.has_cabin_call(id, new_floor) || _task_manager.has_floor_call(id, new_floor))
                    {
                        qInfo("Лифт %lu: после разворота едем вниз к этажу %lu", id, new_floor);
                        return new_floor - 1;
                    }
                }
            }
        }
        qInfo("Лифт %lu: нет задач в любом направлении", id);
        return FLOOR_NOT_FOUND;
    }
    else
    {
        size_t target_floor = next_floor_in_direction(id, _current_directions[id], floor);
        if (target_floor != FLOOR_NOT_FOUND)
            return target_floor;
    }

    qInfo("[Лифт %lu] Этаж не найден", id);
    return FLOOR_NOT_FOUND;
}

Direction Controller::get_next_direction(CabinID id)
{
    std::vector<Task> tasks = _task_manager.get_for_cabin(id);

    if (tasks.empty())
        return IDLE;

    if (_current_directions[id] == IDLE)
    {
        int dst_visit_floor = -1;
        int min_dst = FLOOR_COUNT + 1;

        for (const auto& task : tasks)
        {
            int diff = std::abs(static_cast<int>(_current_floor[id]) + 1 - static_cast<int>(task.get_floor()));
            if (diff > 0 && diff < min_dst)
            {
                min_dst = diff;
                dst_visit_floor = task.get_floor();
            }
        }

        if (dst_visit_floor == -1)
            return IDLE;
        else if (dst_visit_floor > _current_floor[id] + 1)
            return UP;
        else
            return DOWN;
    }

    size_t target_floor = get_next_visit_floor(id);
    if (target_floor == FLOOR_NOT_FOUND)
        return IDLE;

    size_t target_real_floor = target_floor + 1;
    size_t current_real_floor = _current_floor[id] + 1;

    qInfo("Лифт %lu: текущий этаж %lu, целевой этаж %lu", id, current_real_floor, target_real_floor);

    if (target_real_floor > current_real_floor)
        return UP;
    else if (target_real_floor < current_real_floor)
        return DOWN;
    else
        return IDLE;
}

bool Controller::all_cabins_free() const
{
    return !_task_manager.has_any();
}


#define DISTANCE_COEF 10.0
#define TASK_COUNT_COEF 20.0
double Controller::cabin_weight(CabinID id, size_t target_floor, Direction direction)
{
    double weight = 0;
    int distance = std::abs(static_cast<int>(target_floor) - (static_cast<int>(_current_floor[id]) + 1));
    weight += distance * DISTANCE_COEF;

    int task_count = _task_manager.get_count_for_cabin(id);
    weight += TASK_COUNT_COEF;

    if (_current_directions[id] == IDLE)
    {
        // свободный лифт
        weight -= 15;
    }
    else
    {
        int cur_dist = static_cast<int>(target_floor) - (static_cast<int>(_current_floor[id]) + 1);
        Direction move_direction = get_direction(cur_dist);

        if (_current_directions[id] == move_direction && _current_directions[id] == direction)
        {
            // движение в приоритетном направлении
            weight -= 25;
        }
        else if (_current_directions[id] != move_direction)
        {
            weight += 30;
        }
    }

    if (_current_directions[id] != IDLE)
    {
        int cur_dist = static_cast<int>(target_floor) - (static_cast<int>(_current_floor[id]) + 1);
        Direction required_direction = get_direction(cur_dist);

        if (_current_directions[id] != required_direction && required_direction != IDLE)
        {
            weight += 15;
        }
    }

    return weight;
}

size_t Controller::next_floor_in_direction(CabinID id, Direction direction, size_t current_floor)
{
    if (direction == UP)
    {
        int furthest_down_call = FLOOR_NOT_FOUND;
        for (int floor = FLOOR_COUNT; floor >= current_floor + 1; --floor)
            if (_task_manager.has_floor_call(id, floor))
                furthest_down_call = floor;

        for (int floor = current_floor + 1; floor <= FLOOR_COUNT; ++floor)
        {
            if (_task_manager.has_cabin_call(id, floor) || _task_manager.has_floor_call(id, floor))
            {
                if (furthest_down_call != FLOOR_NOT_FOUND && floor < furthest_down_call)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по пути к конечному этажу %d", id, floor, furthest_down_call);
                    return floor - 1;
                }
                else if (furthest_down_call == FLOOR_NOT_FOUND)
                {
                    qInfo("[Лифт %lu] Найден этаж %lu по ходу вверх", id, floor);
                    return floor - 1;
                }
            }
        }

        if (furthest_down_call != FLOOR_NOT_FOUND)
        {
            qInfo("[Лифт %lu] Едет к %d для смены направления", id, furthest_down_call);
            return furthest_down_call - 1;
        }
    }
    else if (direction == DOWN)
    {
        int furthest_up_call = FLOOR_NOT_FOUND;
        for (int floor = 1; floor <= current_floor - 1; ++floor)
        {
            if (_task_manager.has_floor_call(id, floor))
            {
                furthest_up_call = floor;
                break;
            }
        }

        for (int floor = current_floor - 1; floor >= 1; --floor)
        {
            if (_task_manager.has_cabin_call(id, floor) || _task_manager.has_floor_call(id, floor))
            {
                if (furthest_up_call != FLOOR_NOT_FOUND && floor > furthest_up_call)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по пути к конечному этажу %d", id, floor, furthest_up_call);
                    return floor - 1;
                }
                else if (furthest_up_call == FLOOR_NOT_FOUND)
                {
                    qInfo("[Лифт %lu] Найден этаж %d по ходу вниз", id, floor);
                    return floor - 1;
                }
            }
        }

        if (furthest_up_call != FLOOR_NOT_FOUND)
        {
            qInfo("[Лифт %lu] Едет к %d для смены направления", id, furthest_up_call);
            return furthest_up_call - 1;
        }
    }

    return FLOOR_NOT_FOUND;
}
