//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BASEMODELBUILDER_H
#define LAB_03_BASEMODELBUILDER_H

#include "Builders/BaseBuilder.h"
#include "Reader/ModelReader.h"

class BaseModelBuilder : public BaseBuilder
{
public:
    enum Part : size_t
    {
        POINTS = 0,
        EDGES = 1,
        CENTER = 2
    };

    BaseModelBuilder() = delete;
    explicit BaseModelBuilder(std::shared_ptr<ModelReader> reader);
    virtual ~BaseModelBuilder() override = default;

    virtual bool build_points() = 0;
    virtual bool build_edges() = 0;
    virtual bool build_center() = 0;

private:
    std::shared_ptr<ModelReader> _reader;
};

#endif //LAB_03_BASEMODELBUILDER_H