//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#include "Elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    connect(this, &Elevator::floor_button_call_signal, &_controller, &Controller::floor_destination_slot);
    connect(this, &Elevator::cabin_button_call_signal, &_controller, &Controller::cabin_destination_slot);

    connect(&_controller, &Controller::floor_button_change_color_signal, this, &Elevator::change_floor_button_color_slot);
    connect(&_controller, &Controller::cabin_button_change_color_signal, this, &Elevator::change_cabin_button_color_slot);
    connect(&_controller, &Controller::cabin_position_change_signal, this, &Elevator::change_cabin_position_slot);
}


void Elevator::manage_floor_call_slot(floor_t floor)
{
    emit floor_button_call_signal(floor);
}
void Elevator::manage_cabin_call_slot(floor_t floor, CabinID id)
{
    emit cabin_button_call_signal(floor, id);
}

void Elevator::change_floor_button_color_slot(floor_t floor, bool is_active)
{
    emit floor_button_change_color_signal(floor, is_active);
}
void Elevator::change_cabin_button_color_slot(floor_t floor, CabinID id, bool is_active)
{
    emit cabin_button_change_color_signal(floor, id, is_active);
}
void Elevator::change_cabin_position_slot(CabinID id, floor_t floor)
{
    emit change_cabin_position_signal(id, floor);
}

