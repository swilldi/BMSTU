//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_DRAWMANAGER_H
#define LAB_03_DRAWMANAGER_H
#include "Factories/Draw/Products/BaseDrawer.h"
#include "Managers/BaseManager.h"

#include <memory>

class DrawManager : public BaseManager
{
public:
    DrawManager() = default;
    virtual ~DrawManager() override = default;

    void set_drawer(std::shared_ptr<BaseDrawer> drawer);
    void draw();

private:
    std::shared_ptr<BaseDrawer> _drawer;
};

#endif //LAB_03_DRAWMANAGER_H