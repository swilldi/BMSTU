//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_CABIN_H
#define LAB_04_CABIN_H
#include <QObject>
#include <QTimer>

#include "defines.h"
#include "Doors/ElevatorDoor.h"


class Cabin : public QObject
{
    Q_OBJECT

public:
    Cabin(CabinID id, QObject *parent = nullptr);
    ~Cabin() = default;

    QTimer move_timer;

signals:
    // Внешние сигналы
    void cabin_end_boarding_signal(CabinID id);

    // Внутренние сигналы
    void moving_signal(floor_t floor, Direction direction);
    void boarding_signal(floor_t floor);
    void end_boarding_signal();

    void open_door_signal();

public slots:
    void cabin_free_slot();
    void cabin_moving_slot(floor_t floor, Direction direction);
    void cabin_start_boarding_slot(floor_t floor);

private slots:
    void cabin_end_boarding_slot();   // подписан на ElevatorDoor::is_closed
    void on_moving(floor_t floor, Direction direction);
    void on_boarding(floor_t floor);
    void on_end_boarding();

private:
    enum CabinState
    {
        FREE,
        MOVE,
        BOARDING_STARTED,
        BOARDING_ENDED
    };

    CabinID _id;
    CabinState _state;
    ElevatorDoor _door;
};


#endif //LAB_04_CABIN_H
