//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "DrawVisitor.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjection> projection,
                         std::shared_ptr<BaseRemoveInvisibleEdge> invisible_edge,
                         std::shared_ptr<BaseCoordinateConvert> coordinate_convert,
                         std::shared_ptr<BaseDrawer> drawer,
                         std::shared_ptr<BaseCamera> camera) : _projection(projection),
                                                               _invisible_edge(invisible_edge),
                                                               _coordinate_convert(coordinate_convert),
                                                               _drawer(drawer), _camera(camera) {}

void DrawVisitor::visit(BaseCamera &/*camera*/) const { }

void DrawVisitor::visit(std::shared_ptr<BaseStructure> structure) const
{
    std::vector<Point> projection;
    _projection->project(structure, _camera, projection);

    _coordinate_convert->convert_points(projection, _drawer->get_width(), _drawer->get_height());

    std::vector<BaseRemoveInvisibleEdge::Edge2D> visible_edge;
    _invisible_edge->prepare(projection, structure->get_edges(), _camera, visible_edge);

    for (const auto &edge : visible_edge)
        _drawer->draw_line(edge.first, edge.second);
}
