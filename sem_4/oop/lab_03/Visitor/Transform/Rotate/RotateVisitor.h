//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_ROTATEVISITOR_H
#define LAB_03_ROTATEVISITOR_H
#include "Transform/Data/Rotate/RotateData.h"
#include "Visitor/Transform/TransformVisitor.h"


class RotateVisitor : public TransformVisitor
{
public:
    RotateVisitor() = delete;
    RotateVisitor(const RotateData &data);

    virtual ~RotateVisitor() override = default;
};


#endif //LAB_03_ROTATEVISITOR_H