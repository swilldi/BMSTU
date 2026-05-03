//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "BoneModelBuilder.h"

#include "Component/SceneObject/Model/Bone/BoneModel.h"
#include "Component/SceneObject/Model/Structure/BaseStructure.h"
#include "Exceptions/Builder/Model/ModelBuilderException.h"

BoneModelBuilder::BoneModelBuilder(std::shared_ptr<ModelReader> reader,
                                   std::shared_ptr<BaseStructure> structure) : BaseModelBuilder(reader), _structure(structure)
{
    _part = 0;
}

bool BoneModelBuilder::build_points()
{
    if (_part != POINTS)
        return false;

    auto points = _reader->read_points();
    for (const auto &point : *points)
        _structure->add_point(point);

    ++_part;
    return true;
}

bool BoneModelBuilder::build_edges()
{
    if (_part != EDGES)
        return false;

    auto edges = _reader->read_edges();
    for (const auto &edge : *edges)
        _structure->add_edge(edge);

    ++_part;
    return true;
}

bool BoneModelBuilder::build_center()
{
    if (_part != CENTER)
        return false;

    const auto &points = _structure->get_points();
    double x_min = points[0].get_x(), x_max = points[0].get_x(),
           y_min = points[0].get_y(), y_max = points[0].get_y(),
           z_min = points[0].get_z(), z_max = points[0].get_z();

    for (const auto &point : points)
    {
        x_min = std::min(x_min, point.get_x());
        x_max = std::max(x_max, point.get_x());

        y_min = std::min(y_min, point.get_y());
        y_max = std::max(y_max, point.get_y());

        z_min = std::min(z_min, point.get_z());
        z_max = std::max(z_max, point.get_z());
    }

    double cx = (x_min + x_max) / 2,
           cy = (y_min + y_max) / 2,
           cz = (z_min + z_max) / 2;

    _structure->set_center({ cx, cy, cz });

    _part = POINTS;
    return true;
}

std::shared_ptr<BaseObject> BoneModelBuilder::create_product()
{
    if (!build_points())
        throw ModelBuilderPointsException();
    if (!build_edges())
        throw ModelBuilderEdgesException();
    if (!build_center())
        throw ModelBuilderCenterException();

    return std::make_shared<BoneModel>(_structure);
}
