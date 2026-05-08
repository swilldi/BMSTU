//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_MOVEVISITOR_H
#define LAB_03_MOVEVISITOR_H
#include "Transform/Data/Move/MoveData.h"
#include "Visitor/Transform/TransformVisitor.h"


class MoveVisitor : public TransformVisitor
{
public:
    MoveVisitor() = delete;
    MoveVisitor(const MoveData &data);

    virtual ~MoveVisitor() override = default;
};


#endif //LAB_03_MOVEVISITOR_H
