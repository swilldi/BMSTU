//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEMODELREADERIMPL_H
#define LAB_03_BASEMODELREADERIMPL_H
#include "Component/SceneObject/Model/Edge/Edge.h"
#include "Component/SceneObject/Model/Point/Point.h"
#include <string>

#include <memory>
#include <fstream>

class BaseModelReaderImpl {
public:
    BaseModelReaderImpl() = delete;
    BaseModelReaderImpl(const std::string &filename);
    virtual ~BaseModelReaderImpl() = default;

    virtual std::shared_ptr<std::vector<Point>> read_points() = 0;
    virtual std::shared_ptr<std::vector<Edge>> read_edges() = 0;

protected:
    std::ifstream _file;
};


#endif //LAB_03_BASEMODELREADERIMPL_H