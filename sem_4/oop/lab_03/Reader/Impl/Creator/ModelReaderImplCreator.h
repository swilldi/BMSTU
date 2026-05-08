//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_MODELREADERIMPLCREATOR_H
#define LAB_03_MODELREADERIMPLCREATOR_H

#include "Concepts/Concepts.h"
#include "Reader/Impl/BaseModelReaderImpl.h"
#include "Reader/Impl/txt/TxtModelReaderImpl.h"
#include "Reader/Impl/csv/CsvModelReaderImpl.h"

#include <string>
#include <memory>

template <typename BaseModelReaderImpl, Derivative<BaseModelReaderImpl> DerivedModelReaderImlp, typename ... Args>
    requires ConstructableWith<DerivedModelReaderImlp, Args ...>
class ModelReaderImplCreator
{
public:
    ModelReaderImplCreator() = default;
    ~ModelReaderImplCreator() = default;

    template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
    static std::shared_ptr<BaseModelReaderImpl> create(CallArgs && ... args);
};

#include "ModelReaderImplCreator.hpp"

using TxtModelReaderImplCreator = ModelReaderImplCreator<BaseModelReaderImpl, TxtModelReaderImpl, const std::string &>;
using CsvModelReaderImplCreator = ModelReaderImplCreator<BaseModelReaderImpl, CsvModelReaderImpl, const std::string &>;

#endif //LAB_03_MODELREADERIMPLCREATOR_H