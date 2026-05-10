//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "Controller.h"

Controller::Controller(QObject* parent) : QObject(parent)
{
    setup_cabins();
    setup_cabin_buttons();
    setup_floor_buttons();
    setup_internal_connection();
}

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
    connect(this, &Controller::button_deactivate_signal, this, &Controller::manage_cabin_slot);
    connect(this, &Controller::free_controller_signal, this, &Controller::free_controller_slot);

    // Начальная позиция лифтов
    for (size_t i = 0; i < CABINS_COUNT; ++i)
        emit cabin_position_change_signal(static_cast<CabinID>(i), START_FLOOR);
}

