//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "RayCastingRemoveInvisibleEdge.h"

void RayCastingRemoveInvisibleEdge::prepare(const std::vector<Point> &points, const std::vector<Edge> &edges,
                                            std::shared_ptr<const BaseCamera> camera,
                                            std::vector<Edge2D> &visible_edges)
{
    find_faces(points, edges);

    double t1, t2;
    bool from_visible = true, to_visible = true;
    auto viewpoint = camera->get_center();

    viewpoint.set_x(viewpoint.get_x() + 430);
    viewpoint.set_y(-viewpoint.get_y() + 415);
    viewpoint.set_z(-(viewpoint.get_y() * 20));

    for (const auto &edge: edges)
    {
        auto from = points[edge.get_from()];
        auto to = points[edge.get_to()];

        from.set_z(from.get_z() * from.get_w());
        to.set_z(to.get_z() * to.get_w());

        from_visible = true;
        to_visible = true;

        for (const auto &face : _faces)
        {
            if (std::ranges::find(face.points, from) == face.points.end())
            {
                auto i1 = intersect_line_plane(viewpoint, from, face, t1);
                if (i1 && t1 > -1 && t1 < 0 && point_in_polygon(i1.value(), face))
                    from_visible = false;
            }

            if (std::ranges::find(face.points, to) == face.points.end())
            {
                auto i2 = intersect_line_plane(viewpoint, to, face, t2);
                if (i2 && t2 > -1 && t2 < 0 && point_in_polygon(i2.value(), face))
                    to_visible = false;
            }
        }

        if (from_visible && to_visible)
            visible_edges.push_back({from, to });
    }
}

void RayCastingRemoveInvisibleEdge::find_faces(const std::vector<Point> &points, const std::vector<Edge> &edges)
{
    _faces.clear();

    std::map<int, std::vector<int>> adj;
    for (const auto &edge: edges)
    {
        adj[edge.get_from()].push_back(edge.get_to());
        adj[edge.get_to()].push_back(edge.get_from());
    }

    for (auto &pair : adj)
        std::sort(pair.second.begin(), pair.second.end());

    std::vector<std::vector<int>> processed_faces;

    for (const auto &edge : edges)
    {
        int p1_id = edge.get_from();
        int p2_id = edge.get_to();

        for (int p3_id : adj[p2_id])
        {
            if (p3_id == p1_id)
                continue;

            for (int p4_id : adj[p3_id])
            {
                if (p4_id == p2_id || p4_id == p1_id)
                    continue;

                if (std::binary_search(adj[p4_id].begin(), adj[p4_id].end(), p1_id))
                {
                    std::vector<int> face_ids = { p1_id, p2_id, p3_id, p4_id };
                    std::sort(face_ids.begin(), face_ids.end());

                    bool is_new = true;
                    for (const auto &processed : processed_faces)
                    {
                        if (processed == face_ids)
                        {
                            is_new = false;
                            break;
                        }
                    }

                    if (is_new)
                    {
                        processed_faces.push_back(face_ids);

                        Face face;
                        face.points = { points[p1_id], points[p2_id], points[p3_id], points[p4_id] };
                        _faces.push_back(face);
                    }
                }
            }
        }
    }

    for (auto &face : _faces)
        for (auto &point : face.points)
            point.set_z(point.get_z() * point.get_w());
}

std::optional<Point> RayCastingRemoveInvisibleEdge::intersect_line_plane(const Point &a, const Point &b, const Plane &plane, double &out_t)
{
    const double eps = 1e-9;
    Vector3D<double> line_dir = a - b;
    double dot_n_dir = plane.normal.dot(line_dir);

    if (std::abs(dot_n_dir) < eps)
    {
        double val_p1_in_plane = plane.normal.dot(a) + plane.d_coef;
        if (std::abs(val_p1_in_plane) < eps)
        {
            out_t = 0.0;
            return std::nullopt;
        }
        else
        {
            return std::nullopt;
        }
    }

    double val_p1_in_plane = plane.normal.dot(a) + plane.d_coef;
    out_t = -val_p1_in_plane / dot_n_dir;

    Point intersection_point(a.get_x() + out_t * line_dir.get_x(),
                             a.get_y() + out_t * line_dir.get_y(),
                             a.get_z() + out_t * line_dir.get_z());

    return intersection_point;
}

std::optional<Point> RayCastingRemoveInvisibleEdge::intersect_line_plane(const Point &a, const Point &b, const Face &face, double &out_t)
{
    Plane plane(face.points[0], face.points[1], face.points[2]);
    return intersect_line_plane(a, b, plane, out_t);
}

bool RayCastingRemoveInvisibleEdge::point_in_polygon(const Point &point, const Face &face)
{
    int cross = 0;
    double px = point.get_x();
    double py = point.get_y();

    for (size_t i = 0, j = face.points.size() - 1; i < face.points.size(); j = i++)
    {
        const Point &pi = face.points[i];
        const Point &pj = face.points[j];

        double pi_x = pi.get_x(), pi_y = pi.get_y();
        double pj_x = pj.get_x(), pj_y = pj.get_y();

        if ((pi_y <= py && py < pj_y) || (pj_y <= py && py < pi_y))
        {
            double x_inter = (pj_x - pi_x) * (py - pi_y) / (pj_y - pi_y) + pi_x;
            if (px < x_inter)
                cross++;
        }
    }

    return cross % 2 == 1;
}
