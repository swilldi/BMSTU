//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_MODELREADER_H
#define LAB_03_MODELREADER_H
#include "Component/SceneObject/Model/Edge/Edge.h"
#include "Component/SceneObject/Model/Point/Point.h"
#include "Impl/BaseModelReaderImpl.h"

#include <memory>


class ModelReader
{
public:
    ModelReader() = delete;
    ModelReader(std::shared_ptr<BaseModelReaderImpl> impl);
    ~ModelReader() = default;

    std::shared_ptr<std::vector<Point>> read_points();
    std::shared_ptr<std::vector<Edge>> read_edges();

private:
    std::shared_ptr<BaseModelReaderImpl> _impl;
    std::vector<Point> _points;
    std::vector<Edge> _edges;
};


#endif //LAB_03_MODELREADER_H