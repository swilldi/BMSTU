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
    // Внутренние сигналы
    void opening_signal();   // запрос на открытие принят
    void opened_signal();    // двери полностью открыты
    void closing_signal();   // запрос на закрытие принят
    void is_closed();        // двери полностью закрыты

public slots:
    void start_opening_slot();  // emit opening_signal
    void start_closing_slot();  // emit closing_signal

private slots:
    void on_opening();          // запуск таймера открытия
    void on_open_timer_done();  // таймер открытия завершился
    void on_opened();           // запуск таймера ожидания на этаже
    void on_closing();          // запуск таймера закрытия
    void on_close_timer_done(); // таймер закрытия завершился

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
