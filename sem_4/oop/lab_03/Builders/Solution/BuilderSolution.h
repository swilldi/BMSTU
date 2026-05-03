//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BUILDERSOLUTION_H
#define LAB_03_BUILDERSOLUTION_H
#include "Builders/BaseBuilder.h"
#include "Component/SceneObject/Model/Structure/List/ListStructure.h"
#include "Component/SceneObject/Model/Structure/Matrix/MatrixStructure.h"
#include "ID/ID.h"
#include "Reader/ModelReader.h"

#include <memory>


class BuilderSolution {
public:
    BuilderSolution() = default;
    ~BuilderSolution() = default;

    std::shared_ptr<BaseBuilder> create(std::shared_ptr<ModelReader> reader, ModelRepresentationID representation_id);

private:
    using ModelRepresentationMap = std::map<ModelRepresentationID, std::function<std::shared_ptr<BaseStructure>()>>;
    const ModelRepresentationMap _map = {
        { ListRepresentationID, []() { return std::make_shared<ListStructure>(); }},
        { MatrixRepresentationID, []() { return std::make_shared<MatrixStructure>(); }}
    };
};


#endif //LAB_03_BUILDERSOLUTION_H