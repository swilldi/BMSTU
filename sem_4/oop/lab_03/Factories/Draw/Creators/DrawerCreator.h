//
// Created by Dmitriy Dudurev on 06.05.2026.
//

#ifndef LAB_03_DRAWERCREATOR_H
#define LAB_03_DRAWERCREATOR_H


#include "Concepts/Concepts.h"
#include "Factories/Draw/Products/BaseDrawer.h"
#include "Factories/Draw/QtDraw/Products/QtDrawer.h"

#include <memory>

template <typename BaseDrawer, Derivative<BaseDrawer> DeriveDrawer, typename ... Args>
    requires ConstructableWith<DeriveDrawer, Args ...>
class DrawerCreator
{
public:
    DrawerCreator() = default;
    ~DrawerCreator() = default;

    template<typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
    static std::shared_ptr<BaseDrawer> create(CallArgs && ... args);
};

#include "DrawerCreator.hpp"

using QtDrawerCreator = DrawerCreator<BaseDrawer, QtDrawer, std::shared_ptr<QGraphicsScene>>;

#endif //LAB_03_DRAWERCREATOR_H
