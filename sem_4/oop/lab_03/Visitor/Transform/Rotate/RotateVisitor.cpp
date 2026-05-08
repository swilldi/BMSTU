//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "RotateVisitor.h"

#include "Transform/Action/Rotate/RotateAcion.h"

RotateVisitor::RotateVisitor(const RotateData &data) : TransformVisitor(
    std::make_shared<RotateAction>(data)) {}
