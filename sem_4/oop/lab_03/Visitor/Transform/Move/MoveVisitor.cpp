//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "MoveVisitor.h"

#include "Transform/Action/Move/MoveAction.h"

MoveVisitor::MoveVisitor(const MoveData &data) : TransformVisitor(std::make_shared<MoveAction>(data)) {}
