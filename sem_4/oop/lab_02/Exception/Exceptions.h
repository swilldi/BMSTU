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

class IteratorPointerExpiredException : public IteratorException
{
public:
    IteratorPointerExpiredException(const std::source_location &location) noexcept : IteratorException(
        "wear_ptr expired", location) {}
};

class SetException : public BaseException
{
public:
    SetException(const char *info_msg, const std::source_location &location) noexcept : BaseException(
        info_msg, location) {}
};

class SetMemoryAllocException : public SetException
{
public:
    SetMemoryAllocException(const std::source_location &location) noexcept : SetException(
        "Memory alloc error", location) {}
};

class SetArrayNullptrException : public SetException
{
public:
    SetArrayNullptrException(const std::source_location &location) noexcept : SetException(
        "Nullptr for array", location) {}
};

class SetArrayZeroSizeException : public SetException
{
public:
    SetArrayZeroSizeException(const std::source_location &location) noexcept : SetException(
        "Zero size of array", location) {}
};

#endif //LAB_02_EXCEPTION_H
