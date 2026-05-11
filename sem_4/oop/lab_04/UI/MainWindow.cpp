//
// Created by Dmitriy Dudurev on 11.05.2026.
//

#include "MainWindow.h"
#include "ButtonStyleSheets.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace
{
    inline QString floor_button_name(floor_t floor)
    {
        return QString("floor_%1").arg(floor);
    }

    inline QString cabin_button_name(CabinID id, floor_t floor)
    {
        return QString("el_%1_floor_%2").arg(id).arg(floor);
    }

    inline bool is_button_active(QPushButton* button)
    {
        // ACTIVE_NOT_CURRENT использует #4a3a6e, ACTIVE_CURRENT — #8d6cd1.
        // Общий признак — белый цвет текста, в неактивных стилях его нет.
        return button->styleSheet().contains("color: white");
    }
} // namespace


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    build_ui();
    connect_elevator();

    for (size_t i = 0; i < CABINS_COUNT; ++i)
        update_cabin_position_slot(static_cast<CabinID>(i), START_FLOOR);
}


void MainWindow::build_ui()
{
    setWindowTitle("Система управления лифтами");
    setStyleSheet(WINDOW_STYLE);

    auto* central = new QWidget(this);
    auto* root = new QVBoxLayout(central);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(10);

    auto* title = new QLabel("Система управления лифтами");
    title->setStyleSheet(TITLE_LABEL_STYLE);
    title->setAlignment(Qt::AlignCenter);
    root->addWidget(title);

    auto* main_row = new QHBoxLayout();
    main_row->setSpacing(12);

    // ===== Секция вызова с этажей =====
    auto* call_box = new QGroupBox("Вызов");
    call_box->setStyleSheet(GROUP_BOX_STYLE);
    auto* call_grid = new QGridLayout(call_box);
    call_grid->setSpacing(6);

    for (floor_t floor = FLOOR_COUNT; floor >= 1; --floor)
    {
        const int row = FLOOR_COUNT - floor;

        auto* label = new QLabel(QString("Этаж %1").arg(floor));
        call_grid->addWidget(label, row, 0);

        auto* btn = new QPushButton("Вызов");
        btn->setObjectName(floor_button_name(floor));
        btn->setStyleSheet(INACTIVE_FLOOR_BUTTON);
        call_grid->addWidget(btn, row, 1);

        connect(btn, &QPushButton::clicked, this, [this, floor]
        {
            _elevator_system.manage_floor_call_slot(floor);
        });
    }

    main_row->addWidget(call_box);

    // ===== Секция кабин =====
    for (size_t c = 0; c < CABINS_COUNT; ++c)
    {
        const CabinID id = static_cast<CabinID>(c);

        auto* cabin_box = new QGroupBox(QString("Лифт %1").arg(c + 1));
        cabin_box->setStyleSheet(GROUP_BOX_STYLE);
        auto* cabin_grid = new QGridLayout(cabin_box);
        cabin_grid->setSpacing(4);

        for (floor_t floor = FLOOR_COUNT; floor >= 1; --floor)
        {
            const int row = FLOOR_COUNT - floor;
            auto* btn = new QPushButton(QString::number(floor));
            btn->setObjectName(cabin_button_name(id, floor));
            btn->setStyleSheet(INACTIVE_NOT_CURRENT_CABIN_BUTTON);
            cabin_grid->addWidget(btn, row, 0);

            connect(btn, &QPushButton::clicked, this, [this, id, floor]
            {
                _elevator_system.manage_cabin_call_slot(floor, id);
            });
        }

        main_row->addWidget(cabin_box);
    }

    root->addLayout(main_row);
    setCentralWidget(central);
}


void MainWindow::connect_elevator()
{
    connect(&_elevator_system, &Elevator::floor_button_change_color_signal,
            this, &MainWindow::change_floor_button_style_slot);
    connect(&_elevator_system, &Elevator::cabin_button_change_color_signal,
            this, &MainWindow::change_cabin_button_style_slot);
    connect(&_elevator_system, &Elevator::change_cabin_position_signal,
            this, &MainWindow::update_cabin_position_slot);
}


void MainWindow::change_floor_button_style_slot(floor_t floor, bool is_active)
{
    auto* button = findChild<QPushButton*>(floor_button_name(floor));
    if (!button)
        return;

    button->setStyleSheet(is_active ? ACTIVE_FLOOR_BUTTON : INACTIVE_FLOOR_BUTTON);
}


void MainWindow::change_cabin_button_style_slot(floor_t floor, CabinID id, bool is_active)
{
    auto* button = findChild<QPushButton*>(cabin_button_name(id, floor));
    if (!button)
        return;

    const bool is_current = (_cabins_floor[id] == floor);

    const char* style;
    if (is_active)
        style = is_current ? ACTIVE_CURRENT_CABIN_BUTTON : ACTIVE_NOT_CURRENT_CABIN_BUTTON;
    else
        style = is_current ? INACTIVE_CURRENT_CABIN_BUTTON : INACTIVE_NOT_CURRENT_CABIN_BUTTON;

    button->setStyleSheet(style);
}


void MainWindow::update_cabin_position_slot(CabinID id, floor_t floor)
{
    const floor_t prev_floor = _cabins_floor[id];

    if (prev_floor >= 1 && prev_floor <= FLOOR_COUNT && prev_floor != floor)
    {
        auto* prev_button = findChild<QPushButton*>(cabin_button_name(id, prev_floor));
        if (prev_button && !is_button_active(prev_button))
            prev_button->setStyleSheet(INACTIVE_NOT_CURRENT_CABIN_BUTTON);
    }

    _cabins_floor[id] = floor;

    if (floor >= 1 && floor <= FLOOR_COUNT)
    {
        auto* button = findChild<QPushButton*>(cabin_button_name(id, floor));
        if (button)
        {
            button->setStyleSheet(is_button_active(button)
                                  ? ACTIVE_CURRENT_CABIN_BUTTON
                                  : INACTIVE_CURRENT_CABIN_BUTTON);
        }
    }
}
