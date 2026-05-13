//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "ElevatorDoor.h"

#include <QDebug>

#define START_OPENING_DOOR_MESSAGE "[Двери %d] Открываются"
#define END_OPEN_DOOR_MESSAGE      "[Двери %d] Открылись"
#define START_CLOSING_DOOR_MESSAGE "[Двери %d] Закрываются"
#define END_CLOSING_DOOR_MESSAGE   "[Двери %d] Закрылись"

ElevatorDoor::ElevatorDoor(CabinID id, QObject* parent) : QObject(parent), _id(id), _state(CLOSED)
{
    _open_timer.setSingleShot(true);
    _close_timer.setSingleShot(true);
    _open_state_timer.setSingleShot(true);

    connect(this, &ElevatorDoor::opening_signal, this, &ElevatorDoor::on_opening);  // запуск таймера открытия
    connect(&_open_timer, &QTimer::timeout, this, &ElevatorDoor::on_open_timer_done);  // запуск таймера удержания
    connect(this, &ElevatorDoor::opened_signal, this, &ElevatorDoor::on_opened); // запуск таймера открытого состояния
    connect(&_open_state_timer, &QTimer::timeout, this, &ElevatorDoor::start_closing_slot);
    connect(this, &ElevatorDoor::closing_signal, this, &ElevatorDoor::on_closing);  // запуск таймера закрытия
    connect(&_close_timer, &QTimer::timeout, this, &ElevatorDoor::on_close_timer_done);
}


void ElevatorDoor::start_opening_slot()
{
    if (_state != CLOSED && _state != CLOSING)
        return;

    _state = OPENING;
    emit opening_signal();
}

void ElevatorDoor::start_closing_slot()
{
    if (_state != OPENED)
        return;

    _state = CLOSING;
    emit closing_signal();
}

// Внутренние слоты
void ElevatorDoor::on_opening()
{
    _open_timer.start(WAIT_TIME);
    qInfo(START_OPENING_DOOR_MESSAGE, _id + 1);
}

void ElevatorDoor::on_open_timer_done()
{
    if (_state != OPENING)
        return;

    _state = OPENED;
    qInfo(END_OPEN_DOOR_MESSAGE, _id + 1);
    emit opened_signal();
}

void ElevatorDoor::on_opened()
{
    _open_state_timer.start(WAIT_TIME);
}

void ElevatorDoor::on_closing()
{
    _close_timer.start(WAIT_TIME);
    qInfo(START_CLOSING_DOOR_MESSAGE, _id + 1);
}

void ElevatorDoor::on_close_timer_done()
{
    if (_state != CLOSING)
        return;

    _state = CLOSED;
    qInfo(END_CLOSING_DOOR_MESSAGE, _id + 1);
    emit is_closed();
}
