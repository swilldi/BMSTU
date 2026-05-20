//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_CABINBUTTON_H
#define LAB_04_CABINBUTTON_H
#include "defines.h"
#include "Button/BaseButton.h"


class CabinButton : public BaseButton
{
    Q_OBJECT

public:
    CabinButton(floor_t floor, CabinID id, QWidget *parent = nullptr);
    ~CabinButton() override = default;

signals:
    // Внутренние сигналы
    void activated_signal();
    void deactivated_signal();

public slots:
    void activate_slot();
    void deactivate_slot();

private:
    CabinID _id;
    floor_t _floor;
};


#endif //LAB_04_CABINBUTTON_H
