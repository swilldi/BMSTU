//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEVISITOR_H
#define LAB_03_BASEVISITOR_H
#include <memory>

class BaseCameraImpl;
class BaseModelImpl;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual  ~BaseVisitor() = default;

    virtual void visit(std::shared_ptr<BaseCameraImpl> impl) = 0;
    virtual void visit(std::shared_ptr<BaseModelImpl> impl) = 0;

};

#endif //LAB_03_BASEVISITOR_H
