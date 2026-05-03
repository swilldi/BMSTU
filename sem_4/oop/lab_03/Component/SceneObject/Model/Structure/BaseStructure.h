//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_BASESTRUCTURE_H
#define LAB_03_BASESTRUCTURE_H

#include "Component/SceneObject/Model/Point/Point.h"
#include "Component/SceneObject/Model/Edge/Edge.h"
#include "Transform/Action/TransformAction.h"

class BaseStructure
{
public:
    BaseStructure() = default;
    virtual ~BaseStructure() = default;

    virtual void add_point(const Point& point) = 0;
    virtual void add_edge(const Edge& edge) = 0;

    virtual void set_center(const Point& point) noexcept = 0;

    virtual std::vector<Point> get_points() noexcept = 0;
    virtual std::vector<Edge> get_edges() const noexcept = 0;
    virtual Point get_center() noexcept = 0;

    virtual const std::vector<Point> &get_points() const noexcept = 0;
    virtual const Point &get_center() const noexcept = 0;

    virtual void transform(std::shared_ptr<TransformAction> action) = 0;

protected:
    Point _center;
};

#endif //LAB_03_BASESTRUCTURE_H