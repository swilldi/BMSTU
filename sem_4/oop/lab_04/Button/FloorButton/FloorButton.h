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
    FloorButton(size_t floor, QWidget *parent = nullptr);
    ~FloorButton() override = default;

    void activate();
    void deactivate();

signals:
    void activate_signal();
    void deactivate_signal();

    void activated_signal();
    void deactivated_signal();

public slots:
    void activate_slot();
    void deactivate_slot();

private:
    size_t _floor;
};


#endif //LAB_04_FLOORBUTTON_H
