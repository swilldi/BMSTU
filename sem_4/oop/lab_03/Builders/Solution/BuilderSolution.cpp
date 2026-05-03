//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BuilderSolution.h"

#include "Builders/Creator/BuilderCreator.h"
#include "Exceptions/Solution/Builder/BuilderSolutionException.h"

std::shared_ptr<BaseBuilder> BuilderSolution::create(
    std::shared_ptr<ModelReader> reader, ModelRepresentationID representation_id)
{
    auto it = _map.find(representation_id);
    if (it != _map.end())
        return BoneBuilderCreator::create(reader, it->second());

    throw BuilderSolutionUnknowRepresentation();
}
