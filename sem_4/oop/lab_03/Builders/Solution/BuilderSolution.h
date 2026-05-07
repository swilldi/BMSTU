//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BUILDERSOLUTION_H
#define LAB_03_BUILDERSOLUTION_H
#include "Builders/BaseBuilder.h"
#include "../../Component/SceneObject/Model/Implementor/BaseModelImpl.h"
#include "ID/ID.h"
#include "Reader/ModelReader.h"

#include <memory>


class BuilderSolution {
public:
    BuilderSolution() = default;
    ~BuilderSolution() = default;

    std::shared_ptr<BaseBuilder<BaseModelImpl>> create(std::shared_ptr<ModelReader> reader, ModelRepresentationID representation_id);
};


#endif //LAB_03_BUILDERSOLUTION_H
