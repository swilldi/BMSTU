//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BuilderSolution.h"

#include "Builders/Creator/BuilderCreator.h"
#include "Exceptions/Solution/Builder/BuilderSolutionException.h"

std::shared_ptr<BaseBuilder<BaseModelImpl>> BuilderSolution::create(
    std::shared_ptr<ModelReader> reader, ModelRepresentationID representation_id)
{
    if (representation_id == ListRepresentationID)
        return BoneBuilderCreator::create(reader);
    if (representation_id == MatrixRepresentationID)
        return MatrixBuilderCreator::create(reader);

    throw BuilderSolutionUnknowRepresentation();
}
