//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "ScaleVisitor.h"

#include "Transform/Action/Scale/ScaleAction.h"

ScaleVisitor::ScaleVisitor(const ScaleData &data) : TransformVisitor(std::make_shared<ScaleAction>(data)) {}
