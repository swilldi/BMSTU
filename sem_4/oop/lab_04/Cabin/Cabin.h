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
    // ============================================================
    // ВНЕШНИЕ СИГНАЛЫ — фронты состояний кабины, их слушает Controller.
    // ============================================================
    void cabin_end_boarding_signal(CabinID id);

    // ============================================================
    // ВНУТРЕННИЕ СИГНАЛЫ — триггеры этапов state-machine кабины.
    // Объявлены public, чтобы могли быть прослушаны и снаружи
    // (например, для логирования или UI), но в первую очередь они
    // соединяются со внутренними слотами этого же класса.
    // Декомпозиция «толстых» обработчиков достигается через них:
    //   cabin_moving_slot          → emit moving_signal       → on_moving
    //   cabin_start_boarding_slot  → emit boarding_signal     → on_boarding
    //   cabin_end_boarding_slot    → emit end_boarding_signal → on_end_boarding
    // ============================================================
    void moving_signal(floor_t floor, Direction direction);
    void boarding_signal(floor_t floor);
    void end_boarding_signal();

    // Запрос дверям открыться. Cabin владеет ElevatorDoor, но общается
    // с ним через сигнал/слот — чтобы не было прямой связи методов.
    void open_door_signal();

public slots:
    // ============================================================
    // ВНЕШНИЕ СЛОТЫ — точки входа от Controller.
    // ============================================================
    void cabin_free_slot();
    void cabin_moving_slot(floor_t floor, Direction direction);
    void cabin_start_boarding_slot(floor_t floor);

private slots:
    // ============================================================
    // ВНУТРЕННИЕ СЛОТЫ — обработчики этапов state-machine.
    // Каждый слот делает ровно одну вещь.
    // ============================================================
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
