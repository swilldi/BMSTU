//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_CONTROLLER_H
#define LAB_04_CONTROLLER_H
#include <QObject>

#include "defines.h"
#include "Button/CabinButton/CabinButton.h"
#include "Button/FloorButton/FloorButton.h"
#include "Cabin/Cabin.h"
#include "Task/TaskManager/TaskManager.h"


class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

signals:
    // Внешние сигналы
    void floor_button_change_color_signal(floor_t floor, bool is_active);               // подсветка кнопки этажа
    void cabin_button_change_color_signal(floor_t floor, CabinID id, bool is_active);   // подсветка кнопки в кабине
    void cabin_position_change_signal(CabinID id, floor_t floor);                       // позиция лифта изменилась

    // Внутренние сигналы
    void button_deactivated_signal(CabinID id);                             // задача на этаже выполнена
    void free_cabin_signal(CabinID id);                                     // команда кабине – освободиться
    void move_cabin_signal(CabinID id, floor_t floor, Direction direction); // команда кабине – двигаться
    void stop_cabin_signal(CabinID id, floor_t floor);                      // команда кабине – остановиться
    void free_controller_signal();                                          // задач больше нет

public slots:
    void floor_destination_slot(floor_t floor);                             // Elevator: кнопка вызова на этаже
    void cabin_destination_slot(floor_t floor, CabinID id);                 // Elevator: кнопка внутри кабины

    void free_controller_slot();                                            // подписан на free_controller_signal
    void manage_cabin_slot(CabinID id);                                     // подписан на button_deactivate_signal
    void manage_move_slot(CabinID id);                                      // вход от Cabin::move_timer
    void reach_dst_floor_slot(CabinID id);                                  // вход от Cabin::cabin_end_boarding

private:
    enum ControllerState
    {
        FLOOR_REQUEST,
        CABIN_REQUEST,
        FREE,
        MANAGING_CABIN,
        MANAGING_MOVE,
        REACH_DST_FLOOR
    };

    void setup_cabins();
    void setup_floor_buttons();
    void setup_cabin_buttons();
    void setup_internal_connection();


    Direction get_direction(int diff);
    Direction get_next_direction(CabinID id);

    double cabin_weight(CabinID id, floor_t target_floor, Direction direction);                 // Вес кабины
    floor_t get_next_visit_floor(CabinID id);                                                   // Следующих этаж который посетит кабина
    floor_t next_floor_in_direction(CabinID id, Direction direction, floor_t current_floor);    // Следующих этаж кабины по направлению

    ControllerState _state = FREE;
    std::unique_ptr<Cabin> _cabins[CABINS_COUNT] {};                            // текущие кабины
    floor_t _current_floor[CABINS_COUNT] {};                                    // этажи на которых располагаются кабины
    Direction _current_directions[CABINS_COUNT] {};                             // текущие направления движений кабин
    Direction _preferred_directions[CABINS_COUNT] {};                           // приоритетные направления движений кабин

    std::shared_ptr<FloorButton> _floor_buttons[FLOOR_COUNT] {};                // кнопки на этажах
    std::shared_ptr<CabinButton> _cabin_buttons[CABINS_COUNT][FLOOR_COUNT] {};  // кнопки в кабинах

    TaskManager _task_manager;

};


#endif //LAB_04_CONTROLLER_H