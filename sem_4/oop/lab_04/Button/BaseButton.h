//
// Created by Dmitriy Dudurev on 09.05.2026.
//

#ifndef LAB_04_BASEBUTTON_H
#define LAB_04_BASEBUTTON_H
#include <QPushButton>

class BaseButton : public QObject
{
    Q_OBJECT

public:
    explicit BaseButton(QWidget *parent = nullptr);
    ~BaseButton() override = default;

protected:
    enum ButtonState
    {
        ACTIVE,
        INACTIVE
    };

    ButtonState _state;
};


#endif //LAB_04_BASEBUTTON_H
