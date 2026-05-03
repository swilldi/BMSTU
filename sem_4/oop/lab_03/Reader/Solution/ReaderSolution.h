//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_READERSOLUTION_H
#define LAB_03_READERSOLUTION_H
#include "Reader/ModelReader.h"
#include "Reader/Impl/BaseModelReaderImpl.h"
#include "Reader/Impl/Creator/ModelReaderImplCreator.h"

#include <map>


class ReaderSolution
{
public:
    ReaderSolution() = default;
    ~ReaderSolution() = default;

    std::shared_ptr<ModelReader> create(const std::string &filename);

private:
    using ImplMap = std::map<std::string, std::function<std::shared_ptr<BaseModelReaderImpl>(
                                 const std::string &filename)> >;

    const ImplMap _map = {
        { ".txt", [](const std::string &filename) {
            return TxtModelReaderImplCreator::create(filename);
        } },
        { ".csv", [](const std::string &filename) {
            return CsvModelReaderImplCreator::create(filename);
        } },
    };
};


#endif //LAB_03_READERSOLUTION_H
