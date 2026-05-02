//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_SCALEVISITOR_H
#define LAB_03_SCALEVISITOR_H
#include "Transform/Data/Scale/ScaleData.h"
#include "Visitor/Transform/TransformVisitor.h"


class ScaleVisitor : public TransformVisitor
{
public:
    ScaleVisitor() = delete;
    ScaleVisitor(const ScaleData &data);

    virtual ~ScaleVisitor() override = default;
};


#endif //LAB_03_SCALEVISITOR_H
