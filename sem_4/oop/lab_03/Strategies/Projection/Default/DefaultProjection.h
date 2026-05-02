//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DEFAULTPROJECTION_H
#define LAB_03_DEFAULTPROJECTION_H
#include "Strategies/Projection/BaseProjection.h"

class DefaultProjection : public BaseProjection
{
public:
    DefaultProjection() = default;
    virtual ~DefaultProjection() override = default;

    void project(std::shared_ptr<const BaseStructure> structure, std::shared_ptr<BaseCamera> camera,
                 std::vector<Point> &projected) override;
};

#endif //LAB_03_DEFAULTPROJECTION_H
