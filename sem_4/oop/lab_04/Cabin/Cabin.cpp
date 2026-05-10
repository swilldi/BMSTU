//
// Created by Dmitriy Dudurev on 09.05.2026.
//
#include <QDebug>

#include "Cabin.h"

#define ELEVATOR_MOVE_TO_MESSAGE "[Лифт %lu] Переход %lu -> %lu"
#define ELEVATOR_IDLE_MESSAGE "[Лифт %lu] Остановился на %lu"
#define ELEVATOR_END_BOARDING_MESSAGE "[Лифт %lu] Завершил высадку/посадку"

Cabin::Cabin(CabinID id, QObject* parent) : QObject(parent), _id(id), _state(FREE), _door(id)
{
    move_timer.setSingleShot(true);
    connect(this, &Cabin::open_door_signal, &_door, &ElevatorDoor::start_opening_slot);
    connect(&_door, &ElevatorDoor::is_closed, this, &Cabin::cabin_end_boarding_slot);
}

void Cabin::cabin_free_slot()
{
    if (_state != BOARDING_ENDED)
        return;

    _state = FREE;
}

void Cabin::cabin_moving_slot(size_t floor, Direction direction)
{
    if (_state == BOARDING_STARTED)
        return;

    ++floor;
    size_t next_floor = direction == UP ? floor + 1 : floor - 1;
    _state = MOVE;
    move_timer.start(MOVE_TIME);
    qInfo(ELEVATOR_MOVE_TO_MESSAGE, _id, floor, next_floor);
}

void Cabin::cabin_start_boarding_slot(size_t floor)
{
    if (_state == BOARDING_STARTED | _state == BOARDING_ENDED)
        return;

    _state = BOARDING_STARTED;
    emit open_door_signal();
    qInfo(ELEVATOR_IDLE_MESSAGE, _id + 1, floor + 1);
}

void Cabin::cabin_end_boarding_slot()
{
    if (_state == BOARDING_ENDED)
        return;

    _state = BOARDING_ENDED;
    emit cabin_end_boarding_signal(_id);
    qInfo(ELEVATOR_END_BOARDING_MESSAGE, _id + 1);
}
