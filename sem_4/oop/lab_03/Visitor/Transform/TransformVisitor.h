//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_TRANSFORMVISITOR_H
#define LAB_03_TRANSFORMVISITOR_H
#include "Transform/Action/TransformAction.h"
#include "Visitor/BaseVisitor.h"

class TransformVisitor : public BaseVisitor
{
public:
    TransformVisitor() = delete;
    TransformVisitor(std::shared_ptr<TransformAction> action);
    virtual ~TransformVisitor() = 0;

    void visit(BaseCamera &camera) const override;
    void visit(std::shared_ptr<BaseStructure> &structure) const override;

protected:
    std::shared_ptr<TransformAction> _action;
};

#endif //LAB_03_TRANSFORMVISITOR_H