//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DRAWSOLUTION_HPP
#define LAB_03_DRAWSOLUTION_HPP
#include "DrawSolution.h"
#include "BaseDrawFactory.h"

template <typename Factory, typename Scene>
std::unique_ptr<BaseDrawer> DrawSolution::create_drawer(std::shared_ptr<Scene> scene)
{
    std::shared_ptr<BaseDrawFactory> factory = std::make_shared<Factory>(scene);
    return factory->create_drawer();
}

#endif //LAB_03_DRAWSOLUTION_HPP
