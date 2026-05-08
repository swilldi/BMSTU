//
// Created by Dmitriy Dudurev on 07.05.2026.
//

#include "CameraExtractorVisitor.h"

void CameraExtractorVisitor::visit(std::shared_ptr<BaseCameraImpl> impl)
{
    _impl = impl;
}

std::shared_ptr<BaseCameraImpl> CameraExtractorVisitor::get_impl() const noexcept
{
    return _impl;
}

void CameraExtractorVisitor::visit(std::shared_ptr<BaseModelImpl>) { }
