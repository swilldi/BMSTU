//
// Created by Dmitriy Dudurev on 09.05.2026.
//
#include <QDebug>

#include "Cabin.h"

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
    qInfo("[Лифт %lu] Свободен", _id + 1);
}

void Cabin::cabin_moving_slot(floor_t floor, Direction direction)
{
    if (_state == BOARDING_STARTED)
        return;

    // floor приходит 0-based; для лога переводим в 1-based
    const floor_t cur_floor = floor + 1;
    const floor_t next_floor = direction == UP ? cur_floor + 1 : cur_floor - 1;
    _state = MOVE;
    move_timer.start(MOVE_TIME);
    qInfo("[Лифт %lu] Едет %d → %d", _id + 1, cur_floor, next_floor);
}

void Cabin::cabin_start_boarding_slot(floor_t floor)
{
    if (_state == BOARDING_STARTED || _state == BOARDING_ENDED)
        return;

    // Если кабина была в MOVE — гасим висящий move_timer.
    // Иначе он сработает уже во время посадки и manage_move_slot
    // сдвинет _current_floor, хотя кабина физически стоит.
    move_timer.stop();

    _state = BOARDING_STARTED;
    emit open_door_signal();
    qInfo("[Лифт %lu] Остановился на этаже %d → посадка/высадка", _id + 1, floor + 1);
}

void Cabin::cabin_end_boarding_slot()
{
    if (_state == BOARDING_ENDED)
        return;

    _state = BOARDING_ENDED;
    qInfo("[Лифт %lu] Посадка/высадка завершена", _id + 1);
    emit cabin_end_boarding_signal(_id);
}
