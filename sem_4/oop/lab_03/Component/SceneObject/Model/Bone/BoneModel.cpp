//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "BoneModel.h"

BoneModel::BoneModel(std::shared_ptr<BaseStructure> structure) : BaseModel(structure) { }

Point BoneModel::get_center() const noexcept
{
    return _structure->get_center();
}

std::shared_ptr<BaseStructure> BoneModel::get_structure() const
{
    return _structure;
}

void BoneModel::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(get_structure());
}
