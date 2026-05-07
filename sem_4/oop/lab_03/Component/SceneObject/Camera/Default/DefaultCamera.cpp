//
// Created by Dmitriy Dudurev on 06.05.2026.
//

#include "DefaultCamera.h"

DefaultCamera::DefaultCamera(std::shared_ptr<BaseCameraImpl> impl) : _impl(impl) { }

Point DefaultCamera::get_center() const noexcept
{
    return _impl->get_center();
}

void DefaultCamera::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(_impl);
}
