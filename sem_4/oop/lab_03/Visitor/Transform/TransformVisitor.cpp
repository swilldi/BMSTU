//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "TransformVisitor.h"

#include "Component/SceneObject/Camera/Implementor/BaseCameraImpl.h"
#include "../../Component/SceneObject/Model/Implementor/BaseModelImpl.h"

TransformVisitor::TransformVisitor(std::shared_ptr<TransformAction> action) : _action(action) {}

TransformVisitor::~TransformVisitor() {}

void TransformVisitor::visit(std::shared_ptr<BaseCameraImpl> impl)
{
    if (_action)
        impl->transform(_action);
}

void TransformVisitor::visit(std::shared_ptr<BaseModelImpl> impl)
{
    if (_action)
        impl->transform(_action);
}
