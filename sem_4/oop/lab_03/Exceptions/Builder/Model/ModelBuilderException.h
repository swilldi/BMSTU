//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_MODELBUILDEREXCEPTION_H
#define LAB_03_MODELBUILDEREXCEPTION_H
#include "Exceptions/Builder/BaseBuilderException.h"


class ModelBuilderException : public BaseBuilderException
{
public:
    ModelBuilderException(const char *info,
                          const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelBuilderPointsException : public ModelBuilderException
{
public:
    ModelBuilderPointsException(const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelBuilderEdgesException : public ModelBuilderException
{
public:
    ModelBuilderEdgesException(const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelBuilderCenterException : public ModelBuilderException
{
public:
    ModelBuilderCenterException(const std::source_location &loc = std::source_location::current()) noexcept;
};

#endif //LAB_03_MODELBUILDEREXCEPTION_H
