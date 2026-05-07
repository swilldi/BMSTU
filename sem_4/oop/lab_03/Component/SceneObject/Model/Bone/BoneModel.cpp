//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "BoneModel.h"

BoneModel::BoneModel(std::shared_ptr<BaseModelImpl> impl) : BaseModel(impl) { }

Point BoneModel::get_center() const noexcept
{
    return _impl->get_center();
}

void BoneModel::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(_impl);
}
