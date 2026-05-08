//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEREMOVEINVISIABLEEDGE_H
#define LAB_03_BASEREMOVEINVISIABLEEDGE_H

#include "Component/SceneObject/Camera/Implementor/BaseCameraImpl.h"
#include "Component/SceneObject/Model/Edge/Edge.h"
#include "Component/SceneObject/Model/Point/Point.h"

class BaseRemoveInvisibleEdge
{
public:
    using Edge2D = std::pair<Point, Point>;

    BaseRemoveInvisibleEdge() = default;
    virtual ~BaseRemoveInvisibleEdge() = default;

    virtual void prepare(const std::vector<Point> &points, const std::vector<Edge> &edges,
        std::shared_ptr<const BaseCameraImpl> camera, std::vector<Edge2D> &visible_edges) = 0;

protected:
    struct Face
    {
        std::vector<Point> points;
    };

    struct Plane
    {
        Vector3D<double> normal;
        double d_coef;

        Plane(const Point &a, const Point &b, const Point &c)
        {
            Vector3D<double> v1 = a - b;
            Vector3D<double> v2 = a - c;
            normal = v1.cross(v2).normalized();
            d_coef = -normal.dot(a);
        }
    };
};

#endif //LAB_03_BASEREMOVEINVISIABLEEDGE_H