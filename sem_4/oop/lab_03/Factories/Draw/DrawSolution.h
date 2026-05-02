//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DRAWSOLUTION_H
#define LAB_03_DRAWSOLUTION_H
#include "Products/BaseDrawer.h"

class DrawSolution
{
public:
    template <typename Factory, typename Scene>
    static std::unique_ptr<BaseDrawer> create_drawer(std::shared_ptr<Scene> scene);
};

#endif //LAB_03_DRAWSOLUTION_H