//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_MATRIXSTRUCTURE_H
#define LAB_03_MATRIXSTRUCTURE_H
#include "Component/SceneObject/Model/Structure/BaseStructure.h"

class MatrixModelImpl : public BaseModelImpl
{
public:
    MatrixModelImpl();
    virtual ~MatrixModelImpl() override = default;

    void add_point(const Point &point) override;
    void add_edge(const Edge &edge) override;

    void set_center(const Point &point) noexcept override;

    std::vector<Point> get_points() noexcept override;
    const std::vector<Point> &get_points() const noexcept override;
    std::vector<Edge> get_edges() const noexcept override;

    Point get_center() noexcept override;
    const Point &get_center() const noexcept override;

    void transform(std::shared_ptr<TransformAction> action) override;

private:
    std::vector<Point> _points;
    std::vector<std::vector<bool>> _adjacency_matrix;
    size_t _point_count;

    void resize_matrix(size_t size);
};

#endif //LAB_03_MATRIXSTRUCTURE_H