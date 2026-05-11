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
    void cabin_end_boarding_signal(CabinID id);

    void cabin_stop_signal();
    void passing_floor_signal();
    void open_door_signal();

public slots:
    void cabin_free_slot();
    void cabin_moving_slot(floor_t floor, Direction direction);
    void cabin_end_boarding_slot();
    void cabin_start_boarding_slot(floor_t floor);

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