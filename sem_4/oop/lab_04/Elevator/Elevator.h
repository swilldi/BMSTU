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
    void floor_button_change_color_signal(size_t floor, bool is_active);
    void cabin_button_change_color_signal(size_t floor, bool is_active);
    void change_cabin_position_signal(CabinID id, size_t floor);

    void floor_button_call_signal(size_t floor);
    void cabin_button_call_signal(size_t floor, CabinID id);

public slots:
    void manage_floor_call_slot(size_t floor);
    void manage_cabin_call_slot(size_t floor, CabinID id);

    void change_floor_button_color_slot(size_t floor, bool is_active);
    void change_cabin_button_color_slot(size_t floor, bool is_active);
    void change_cabin_position_slot(CabinID id, size_t floor); // почему CabinID первый???

private:
    Controller _controller;
};


#endif //LAB_04_ELEVATOR_H