//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "ElevatorDoor.h"

#include <QDebug>

#define START_OPENING_DOOR_MESSAGE "[Двери %lu] Открываются"
#define END_OPEN_DOOR_MESSAGE      "[Двери %lu] Открылись"
#define START_CLOSING_DOOR_MESSAGE "[Двери %lu] Закрываются"
#define END_CLOSING_DOOR_MESSAGE   "[Двери %lu] Закрылись"

ElevatorDoor::ElevatorDoor(CabinID id, QObject* parent) : QObject(parent), _id(id), _state(CLOSED)
{
    _open_timer.setSingleShot(true);
    _close_timer.setSingleShot(true);
    _open_state_timer.setSingleShot(true);

    // --- Цепочка декомпозированных внутренних подписок ---
    // start_opening_slot → opening_signal → on_opening (запуск таймера)
    connect(this, &ElevatorDoor::opening_signal, this, &ElevatorDoor::on_opening);
    // _open_timer ➜ on_open_timer_done (фиксирует OPENED + opened_signal)
    connect(&_open_timer, &QTimer::timeout, this, &ElevatorDoor::on_open_timer_done);
    // opened_signal → on_opened (запуск таймера удержания)
    connect(this, &ElevatorDoor::opened_signal, this, &ElevatorDoor::on_opened);
    // _open_state_timer ➜ start_closing_slot (как только удержание истекло —
    // эмулируем «внешний» запрос на закрытие)
    connect(&_open_state_timer, &QTimer::timeout, this, &ElevatorDoor::start_closing_slot);
    // start_closing_slot → closing_signal → on_closing (запуск таймера)
    connect(this, &ElevatorDoor::closing_signal, this, &ElevatorDoor::on_closing);
    // _close_timer ➜ on_close_timer_done (фиксирует CLOSED + is_closed)
    connect(&_close_timer, &QTimer::timeout, this, &ElevatorDoor::on_close_timer_done);
}

// =============================================================================
// Внешние точки входа (start_opening_slot, start_closing_slot).
// Делают РОВНО три вещи: проверка ТПС, смена состояния, эмит внутреннего сигнала.
// Вся остальная работа — в обработчиках внутренних событий.
// =============================================================================

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

// =============================================================================
// Внутренние обработчики — каждая функция выполняет ровно одну операцию.
// =============================================================================

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
