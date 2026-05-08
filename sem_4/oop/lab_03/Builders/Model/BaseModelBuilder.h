//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BASEMODELBUILDER_H
#define LAB_03_BASEMODELBUILDER_H

#include "Builders/BaseBuilder.h"
#include "../../Component/SceneObject/Model/Implementor/BaseModelImpl.h"
#include "Reader/ModelReader.h"

class BaseModelBuilder : public BaseBuilder<BaseModelImpl>
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

    bool build_points();
    bool build_edges();
    bool build_center();

    std::shared_ptr<BaseModelImpl> create_product() override;

protected:
    virtual std::shared_ptr<BaseModelImpl> create_impl() = 0;

    std::shared_ptr<ModelReader> _reader;
    std::shared_ptr<BaseModelImpl> _impl;
};

#endif //LAB_03_BASEMODELBUILDER_H
