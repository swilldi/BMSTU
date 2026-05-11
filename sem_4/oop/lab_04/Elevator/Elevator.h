//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_ELEVATOR_H
#define LAB_04_ELEVATOR_H
#include <QObject>

#include "defines.h"
#include "Controller/Controller.h"


class Elevator : public QObject
{
    Q_OBJECT

public:
    explicit Elevator(QObject *parent = nullptr);

signals:
    void floor_button_change_color_signal(floor_t floor, bool is_active);
    void cabin_button_change_color_signal(floor_t floor, CabinID id, bool is_active);
    void change_cabin_position_signal(CabinID id, floor_t floor);

    void floor_button_call_signal(floor_t floor);
    void cabin_button_call_signal(floor_t floor, CabinID id);

public slots:
    void manage_floor_call_slot(floor_t floor);
    void manage_cabin_call_slot(floor_t floor, CabinID id);

    void change_floor_button_color_slot(floor_t floor, bool is_active);
    void change_cabin_button_color_slot(floor_t floor, CabinID id, bool is_active);
    void change_cabin_position_slot(CabinID id, floor_t floor);

private:
    Controller _controller;
};


#endif //LAB_04_ELEVATOR_H