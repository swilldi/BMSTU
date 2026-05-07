//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DRAWSOLUTION_HPP
#define LAB_03_DRAWSOLUTION_HPP
#include "DrawSolution.h"

#include <utility>

template <typename Creator, typename ... Args>
std::shared_ptr<BaseDrawer> DrawSolution::create_drawer(Args && ... args)
{
    return Creator::create(std::forward<Args>(args)...);
}

#endif //LAB_03_DRAWSOLUTION_HPP
