//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "ElevatorDoor.h"

ElevatorDoor::ElevatorDoor(CabinID id, QObject *parent) : QObject(parent), _id(id), _state(CLOSED)
{
    _open_timer.setSingleShot(true);
    _close_timer.setSingleShot(true);
    _open_state_timer.setSingleShot(true);

    connect(&_open_timer, &QTimer::timeout, this, &ElevatorDoor::open_slot);
    connect(&_open_state_timer, &QTimer::timeout, this, &ElevatorDoor::start_closing_slot);
    connect(&_close_timer, &QTimer::timeout, this, &ElevatorDoor::close_slot);
}

void ElevatorDoor::start_opening_slot()
{
    if (_state != CLOSED && _state != CLOSING)
        return;

    int time_to_open = WAIT_TIME;
    if (_state == CLOSING)
    {
        int remining_time = _close_timer.remainingTime();
        time_to_open = remining_time > 0 ? (WAIT_TIME * remining_time / WAIT_TIME) : WAIT_TIME;
    }

    _open_timer.start(time_to_open);
    _state = OPENING;
    qInfo("[Двери %lu] Открываются", _id + 1);
}

void ElevatorDoor::start_closing_slot()
{
    if (_state != OPENED)
        return;

    _state = CLOSING;
    _close_timer.start(WAIT_TIME);
    qInfo("[Двери %lu] Закрываются", _id + 1);
}

void ElevatorDoor::open_slot()
{
    if (_state != OPENING)
        return;

    _state = OPENED;
    _open_state_timer.start(WAIT_TIME);
    qInfo("[Двери %lu] Открылись", _id + 1);
}

void ElevatorDoor::close_slot()
{
    if (_state != CLOSING)
        return;

    _state = CLOSED;
    qInfo("[Двери %lu] Закрылись", _id + 1);
    emit is_closed();
}
