//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "DefaultProjection.h"

void DefaultProjection::project(std::shared_ptr<const BaseStructure> structure,
                                std::shared_ptr<BaseCamera> camera, std::vector<Point> &projected)
{
    projected.clear();

    const auto &points = structure->get_points();
    const auto &edges = structure->get_edges();

    const auto &look_matrix = camera->get_look_matrix();
    const auto &projection_matrix = camera->get_projection_matrix(1.0);
    const auto &transform_matrix = projection_matrix * look_matrix;

    for (const Point &point : points)
    {
        Point proj(point);
        proj.transform(transform_matrix);

        double w = proj.get_w();
        if (w != 0.0)
        {
            proj.set_x(proj.get_x() / w);
            proj.set_y(proj.get_y() / w);
            proj.set_z(proj.get_z() / w);
        }

        projected.push_back(proj);
    }

}
