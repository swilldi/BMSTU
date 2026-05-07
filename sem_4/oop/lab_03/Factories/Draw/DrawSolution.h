//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DRAWSOLUTION_H
#define LAB_03_DRAWSOLUTION_H
#include "Products/BaseDrawer.h"

#include <memory>

class DrawSolution
{
public:
    template <typename Creator, typename ... Args>
    static std::shared_ptr<BaseDrawer> create_drawer(Args && ... args);
};

#endif //LAB_03_DRAWSOLUTION_H
