//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "FloorButton.h"
#include <QDebug>


#define ACTIVATE_FLOOR_BUTTON_MESSAGE "[Этаж %lu]: кнопка активирована"
#define INACTIVATE_FLOOR_BUTTON_MESSAGE "[Этаж %lu]: кнопка деактивирована"

FloorButton::FloorButton(size_t floor, QWidget *parent) : BaseButton(parent), _floor(floor)
{
    connect(this, &FloorButton::activate_signal, this, &FloorButton::activate_slot);
    connect(this, &FloorButton::deactivate_signal, this, &FloorButton::deactivate_slot);
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
