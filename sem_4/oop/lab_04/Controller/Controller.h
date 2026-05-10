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
    void floor_button_change_color_signal(size_t floor, bool is_active);
    void cabin_button_change_color_signal(size_t floor, CabinID id, bool is_active);
    void cabin_position_change_signal(CabinID id, size_t floor);

    void button_deactivate_signal(CabinID id);
    void free_cabin_signal(CabinID id);
    void move_cabin_signal(CabinID id, size_t floor, Direction direction);
    void stop_cabin_signal(CabinID id, size_t floor);
    void free_controller_signal();

public slots:
    void floor_destanation_slot(size_t floor);
    void floor_destanation_slot(size_t floor, CabinID id);

    void manage_move_slot(CabinID id);
    void manage_cabin_slot(CabinID id);
    void reach_dst_floor_slot(CabinID id);
    void free_controller_slot();

private:
    enum ControllerState
    {
        FREE,
        CABIN_REQUEST,
        FLOOR_REQUEST,
        MANAGING_CABIN,
        MANAGING_MOVE,
        REACH_DST_FLOOR
    };

    void setup_cabins();
    void setup_floor_buttons();
    void setup_cabin_buttons();
    void setup_internal_connection();


    Direction get_direction(size_t diff);
    Direction get_next_direction(CabinID id);
    CabinID get_deside_cabin_id(size_t floor);

    double cabin_weight(CabinID id, size_t target_floor, Direction direction);
    size_t get_next_visit_floor(CabinID id);
    size_t next_floor_in_direction(CabinID id, Direction direction, size_t current_floor);
    bool all_cabins_free();

    ControllerState _state = FREE;
    std::unique_ptr<Cabin> _cabins[CABINS_COUNT] {};
    size_t _current_floor[CABINS_COUNT] {};
    Direction _current_directions[CABINS_COUNT] {};
    Direction _preferred_directions[CABINS_COUNT] {};

    std::shared_ptr<FloorButton> _floor_buttons[FLOOR_COUNT] {};
    std::shared_ptr<CabinButton> _cabin_buttons[CABINS_COUNT][FLOOR_COUNT] {};

    TaskManager _task_manager;

};


#endif //LAB_04_CONTROLLER_H