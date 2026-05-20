//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_ELEVATORDOOR_H
#define LAB_04_ELEVATORDOOR_H
#include <QObject>
#include <QTimer>

#include "defines.h"


class ElevatorDoor : public QObject
{
    Q_OBJECT

public:
    explicit ElevatorDoor(CabinID id, QObject *parent = nullptr);

signals:
    void is_closed();        // двери полностью закрыты

public slots:
    void start_opening_slot();
    void start_closing_slot();

private slots:
    void open_slot();
    void close_slot();

private:
    enum ElevatorDoorState
    {
        OPENED,
        OPENING,
        CLOSED,
        CLOSING
    };

    CabinID _id;
    ElevatorDoorState _state;

    QTimer _open_timer;          // таймер открытия
    QTimer _close_timer;         // таймер закрытия
    QTimer _open_state_timer;    // таймер удержания дверей открытыми

};


#endif //LAB_04_ELEVATORDOOR_H
