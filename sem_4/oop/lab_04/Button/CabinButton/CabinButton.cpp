//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "CabinButton.h"
#include <QDebug>

CabinButton::CabinButton(floor_t floor, CabinID id, QWidget *parent) : BaseButton(parent), _floor(floor), _id(id)
{
    _state = INACTIVE;
}

void CabinButton::activate_slot()
{
    if (_state == ACTIVE)
        return;

    _state = ACTIVE;
    qInfo("[Кабина %d][Этаж %d] Кнопка активирована", _id + 1, _floor);
    emit activated_signal();
}

void CabinButton::deactivate_slot()
{
    if (_state == INACTIVE)
        return;

    _state = INACTIVE;
    qInfo("[Кабина %d][Этаж %d] Кнопка деактивирована", _id + 1, _floor);
    emit deactivated_signal();
}
