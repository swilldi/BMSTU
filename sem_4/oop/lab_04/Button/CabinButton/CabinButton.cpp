//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "CabinButton.h"
#include <QDebug>

#define ACTIVATE_CABIN_BUTTON_MESSAGE "[Лифт %lu]: кнопка N-%d активирована"
#define INACTIVATE_CABIN_BUTTON_MESSAGE "[Лифт %lu]: кнопка N-%d деактивирована"

CabinButton::CabinButton(floor_t floor, CabinID id, QWidget *parent) : BaseButton(parent), _floor(floor), _id(id)
{
    _state = INACTIVE;
}

void CabinButton::activate_slot()
{
    if (_state == ACTIVE)
        return;

    _state = ACTIVE;
    qInfo(ACTIVATE_CABIN_BUTTON_MESSAGE, _id + 1, _floor);
    emit activated_signal();
}

void CabinButton::deactivate_slot()
{
    if (_state == INACTIVE)
        return;

    _state = INACTIVE;
    qInfo(INACTIVATE_CABIN_BUTTON_MESSAGE, _id + 1, _floor);
    emit deactivated_signal();
}

void CabinButton::activate()
{
    activate_slot();
    emit activate_signal();
}

void CabinButton::deactivate()
{
    deactivate_slot();
    emit deactivate_signal();
}