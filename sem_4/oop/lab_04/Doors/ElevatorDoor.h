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
    // === Внутренние события сущности «дверь» =================================
    // Эти сигналы могут слушаться как ВНУТРИ сущности (для декомпозиции
    // монолитного обработчика на цепочку коротких слотов), так и СНАРУЖИ
    // (например, UI может слушать их, чтобы анимировать двери).
    void opening_signal();   // запрос на открытие принят → следующий шаг
    void opened_signal();    // двери полностью открыты
    void closing_signal();   // запрос на закрытие принят → следующий шаг
    void is_closed();        // двери полностью закрыты (используется Cabin'ом)

public slots:
    // === Внешние события (точки входа от других сущностей) ===================
    void start_opening_slot();
    void start_closing_slot();

private slots:
    // === Внутренние обработчики ==============================================
    // Каждый делает РОВНО одну вещь: либо запустить таймер, либо
    // зафиксировать переход состояния. Декомпозиция обработчика start_opening
    // достигается тем, что вместо одного «толстого» метода теперь цепочка:
    //   start_opening_slot   → emit opening_signal
    //   on_opening           → запуск таймера открытия
    //   on_open_timer_done   → переход OPENING→OPENED + emit opened_signal
    //   on_opened            → запуск таймера удержания
    //   start_closing_slot   → emit closing_signal
    //   on_closing           → запуск таймера закрытия
    //   on_close_timer_done  → переход CLOSING→CLOSED + emit is_closed
    void on_opening();
    void on_open_timer_done();
    void on_opened();
    void on_closing();
    void on_close_timer_done();

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

    QTimer _open_timer;          // таймер длительности открытия
    QTimer _close_timer;         // таймер длительности закрытия
    QTimer _open_state_timer;    // таймер удержания дверей открытыми

};


#endif //LAB_04_ELEVATORDOOR_H
