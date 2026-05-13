//
// Created by Dmitriy Dudurev on 09.05.2026.
//
#include <QDebug>

#include "Cabin.h"

Cabin::Cabin(CabinID id, QObject* parent) : QObject(parent), _id(id), _state(FREE), _door(id)
{
    move_timer.setSingleShot(true);

    // === Связь с дверьми ===
    connect(this, &Cabin::open_door_signal, &_door, &ElevatorDoor::start_opening_slot);
    connect(&_door, &ElevatorDoor::is_closed, this, &Cabin::cabin_end_boarding_slot);

    // === Внутренние подписки ===
    connect(this, &Cabin::moving_signal,       this, &Cabin::on_moving);
    connect(this, &Cabin::boarding_signal,     this, &Cabin::on_boarding);
    connect(this, &Cabin::end_boarding_signal, this, &Cabin::on_end_boarding);
}

void Cabin::cabin_free_slot()
{
    if (_state != BOARDING_ENDED)
        return;

    _state = FREE;
    qInfo("[Лифт %d] Свободен", _id + 1);
}

void Cabin::cabin_moving_slot(floor_t floor, Direction direction)
{
    if (_state == BOARDING_STARTED)
        return;

    _state = MOVE;
    emit moving_signal(floor, direction);
}

void Cabin::cabin_start_boarding_slot(floor_t floor)
{
    if (_state == BOARDING_STARTED || _state == BOARDING_ENDED)
        return;

    move_timer.stop();

    _state = BOARDING_STARTED;
    emit boarding_signal(floor);
}

void Cabin::cabin_end_boarding_slot()
{
    if (_state == BOARDING_ENDED)
        return;

    _state = BOARDING_ENDED;
    emit end_boarding_signal();
}

// Внутренние сигналы
void Cabin::on_moving(floor_t floor, Direction direction)
{
    const floor_t cur_floor = floor + 1;
    const floor_t next_floor = direction == UP ? cur_floor + 1 : cur_floor - 1;
    move_timer.start(MOVE_TIME);
    qInfo("[Лифт %d] Едет %d → %d", _id + 1, cur_floor, next_floor);
}

void Cabin::on_boarding(floor_t floor)
{
    emit open_door_signal();
    qInfo("[Лифт %d] Остановился на этаже %d → посадка/высадка", _id + 1, floor + 1);
}

void Cabin::on_end_boarding()
{
    qInfo("[Лифт %d] Посадка/высадка завершена", _id + 1);
    emit cabin_end_boarding_signal(_id);
}
