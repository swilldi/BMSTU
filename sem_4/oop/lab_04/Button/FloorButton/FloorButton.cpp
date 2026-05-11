//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "FloorButton.h"
#include <QDebug>


#define ACTIVATE_FLOOR_BUTTON_MESSAGE "[Этаж %d]: кнопка активирована"
#define INACTIVATE_FLOOR_BUTTON_MESSAGE "[Этаж %d]: кнопка деактивирована"

FloorButton::FloorButton(floor_t floor, QWidget *parent) : BaseButton(parent), _floor(floor)
{
    _state = INACTIVE;
}

void FloorButton::activate_slot()
{
    if (_state == ACTIVE)
        return;

    _state = ACTIVE;
    qInfo(ACTIVATE_FLOOR_BUTTON_MESSAGE, _floor);
    emit activated_signal();
}

void FloorButton::deactivate_slot()
{
    if (_state == INACTIVE)
        return;

    _state = INACTIVE;
    qInfo(INACTIVATE_FLOOR_BUTTON_MESSAGE, _floor);
    emit deactivated_signal();
}

void FloorButton::activate()
{
    // Меняем состояние и оповещаем подписчиков (Controller, UI).
    // Самоконнекта на собственный сигнал нет — переход состояния явный.
    activate_slot();
    emit activate_signal();
}

void FloorButton::deactivate()
{
    deactivate_slot();
    emit deactivate_signal();
}