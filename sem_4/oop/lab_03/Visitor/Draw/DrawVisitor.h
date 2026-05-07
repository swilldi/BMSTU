//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DRAWVISITOR_H
#define LAB_03_DRAWVISITOR_H
#include "Factories/Draw/Products/BaseDrawer.h"
#include "Strategies/CoordinateConvert/BaseCoordinateConvert.h"
#include "Strategies/Projection/BaseProjection.h"
#include "Strategies/RemoveInvisibleEdge/BaseRemoveInvisibleEdge.h"
#include "Visitor/BaseVisitor.h"

class DrawVisitor : public BaseVisitor
{
public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseProjection> projection, std::shared_ptr<BaseRemoveInvisibleEdge> invisible_edge,
              std::shared_ptr<BaseCoordinateConvert> coordinate_convert, std::shared_ptr<BaseDrawer> drawer,
              std::shared_ptr<BaseCameraImpl> camera);

    virtual ~DrawVisitor() override = default;

    void visit(std::shared_ptr<BaseCameraImpl> impl) const override;
    void visit(std::shared_ptr<BaseModelImpl> impl) const override;

private:
    std::shared_ptr<BaseDrawer> _drawer;
    std::shared_ptr<BaseCameraImpl> _camera;

    std::shared_ptr<BaseProjection> _projection;
    std::shared_ptr<BaseRemoveInvisibleEdge> _invisible_edge;
    std::shared_ptr<BaseCoordinateConvert> _coordinate_convert;

};

#endif //LAB_03_DRAWVISITOR_H
