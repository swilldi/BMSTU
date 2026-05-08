//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_READERCREATOR_H
#define LAB_03_READERCREATOR_H

#include "Concepts/Concepts.h"
#include "Reader/ModelReader.h"

#include <memory>

template <typename Reader, typename ... Args> requires ConstructableWith<Reader, Args ...>
class ReaderCreator
{
public:
    ReaderCreator() = default;
    ~ReaderCreator() = default;

    template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
    static std::shared_ptr<Reader> create(CallArgs && ... args);
};

#include "ReaderCreator.hpp"

using ModelReaderCreator = ReaderCreator<ModelReader, std::shared_ptr<BaseModelReaderImpl>>;

#endif //LAB_03_READERCREATOR_H