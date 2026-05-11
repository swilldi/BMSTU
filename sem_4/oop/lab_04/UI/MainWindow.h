//
// Created by Dmitriy Dudurev on 11.05.2026.
//

#ifndef LAB_04_MAINWINDOW_H
#define LAB_04_MAINWINDOW_H

#include <QMainWindow>

#include "defines.h"
#include "Elevator/Elevator.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

public slots:
    void change_floor_button_style_slot(floor_t floor, bool is_active);
    void change_cabin_button_style_slot(floor_t floor, CabinID id, bool is_active);
    void update_cabin_position_slot(CabinID id, floor_t floor);

private:
    void build_ui();
    void connect_elevator();

    Elevator _elevator_system;

    // Текущий этаж каждой кабины — для подсветки кнопок внутри кабины
    floor_t _cabins_floor[CABINS_COUNT] = {0, 0};
};


#endif //LAB_04_MAINWINDOW_H
