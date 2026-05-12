//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_FLOORBUTTON_H
#define LAB_04_FLOORBUTTON_H

#include "defines.h"
#include "Button/BaseButton.h"

class FloorButton : public BaseButton
{
    Q_OBJECT

public:
    FloorButton(floor_t floor, QWidget *parent = nullptr);
    ~FloorButton() override = default;

signals:
    // ============================================================
    // ВНУТРЕННИЕ СИГНАЛЫ — фронты изменения состояния кнопки.
    // Public, чтобы Controller мог слушать (UI-фидбэк и снятие задачи).
    // ============================================================
    void activated_signal();
    void deactivated_signal();

public slots:
    // ============================================================
    // ВНЕШНИЕ СЛОТЫ — точки входа от Controller.
    // Слот делает ровно одно: меняет состояние и эмит'ит фронт.
    // ============================================================
    void activate_slot();
    void deactivate_slot();

private:
    floor_t _floor;
};


#endif //LAB_04_FLOORBUTTON_H
