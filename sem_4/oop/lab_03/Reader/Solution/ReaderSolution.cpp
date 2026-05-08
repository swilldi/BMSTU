//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "ReaderSolution.h"

#include "Exceptions/Solution/Reader/ReaderSolutionException.h"
#include "Reader/Creator/ReaderCreator.h"

std::shared_ptr<ModelReader> ReaderSolution::create(const std::string &filename)
{
    std::string extension = std::filesystem::path(filename).extension().string();

    if (auto it = _map.find(extension); it != _map.end())
    {
        auto impl = it->second(filename);
        return ModelReaderCreator::create(impl);
    }

    throw ReaderSolutionUnknowExtension();
}
