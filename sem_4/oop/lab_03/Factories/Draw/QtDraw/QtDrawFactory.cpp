//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "QtDrawFactory.h"

#include "Products/QtDrawer.h"

QtDrawFactory::QtDrawFactory(std::shared_ptr<QGraphicsScene> scene) : _scene(scene) {}

std::unique_ptr<BaseDrawer> QtDrawFactory::create_drawer()
{
    return std::make_unique<QtDrawer>(_scene.lock());
}
