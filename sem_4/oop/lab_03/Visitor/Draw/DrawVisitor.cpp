//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "DrawVisitor.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjection> projection,
                         std::shared_ptr<BaseRemoveInvisibleEdge> invisible_edge,
                         std::shared_ptr<BaseCoordinateConvert> coordinate_convert,
                         std::shared_ptr<BaseDrawer> painter,
                         std::shared_ptr<BaseCamera> camera) : _projection(projection),
                                                               _invisible_edge(invisible_edge),
                                                               _coordinate_convert(coordinate_convert),
                                                               _painter(painter), _camera(camera) {}

void DrawVisitor::visit(BaseCamera &/*camera*/) const { }
