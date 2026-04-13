//
// Created by Dmitriy Dudurev on 13.04.2026.
//

#ifndef LAB_02_EXCEPTION_H
#define LAB_02_EXCEPTION_H

#include <source_location>
#include "BaseException.h"

class IteratorException : public BaseException
{
public:
    IteratorException(const char *info_msg, const std::source_location &location) noexcept : BaseException(
        info_msg, location) {}
};

class SetException : public BaseException
{
public:
    SetException(const char *info_msg, const std::source_location &location) noexcept : BaseException(
        info_msg, location) {}
};

class MemoryAllocException : public SetException
{
public:
    MemoryAllocException(const char *info_msg, const std::source_location &location) noexcept : SetException(
        info_msg, location) {}
};

#endif //LAB_02_EXCEPTION_H
