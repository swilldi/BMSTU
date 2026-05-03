//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_COMPOSITEEXCEPTION_H
#define LAB_03_COMPOSITEEXCEPTION_H
#include "Exceptions/BaseException.h"


class CompositeException : public BaseException
{
public:
    CompositeException(const char *info,
                       const std::source_location &loc = std::source_location::current()) noexcept;
};

class CompositeIndexOutOfRange final : public CompositeException
{
public:
    CompositeIndexOutOfRange(const std::source_location &loc = std::source_location::current()) noexcept;
};

#endif //LAB_03_COMPOSITEEXCEPTION_H
