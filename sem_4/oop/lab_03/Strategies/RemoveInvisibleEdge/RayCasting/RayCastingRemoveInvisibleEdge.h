//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_RAYCASTINGREMOVEINVISIBLEEDGE_H
#define LAB_03_RAYCASTINGREMOVEINVISIBLEEDGE_H

#include "Strategies/RemoveInvisibleEdge/BaseRemoveInvisibleEdge.h"

class RayCastingRemoveInvisibleEdge : public BaseRemoveInvisibleEdge
{
public:
    RayCastingRemoveInvisibleEdge() = default;
    virtual ~RayCastingRemoveInvisibleEdge() override = default;

    void prepare(const std::vector<Point> &points, const std::vector<Edge> &edges,
        std::shared_ptr<const BaseCamera> camera, std::vector<Edge2D> &visible_edges) override;

private:
    std::vector<Face> _faces;
    void create_face(const Point &a, const Point &b, const Point &c, const Point &d);
    void calc_face(const std::vector<Point> &points);
    bool points_coplanar(const Point &a, const Point &b, const Point &c, const Point &d);

    std::optional<Point> intersect_line_plane(const Point &a, const Point &b, const Plane &plane, double &out_t);
    std::optional<Point> intersect_line_plane(const Point &a, const Point &b, const Face &face, double &out_t);
    bool point_in_polygon(const Point &point, const Face &face);

    void find_faces(const std::vector<Point> &points, const std::vector<Edge> &edges);
};

#endif //LAB_03_RAYCASTINGREMOVEINVISIBLEEDGE_H