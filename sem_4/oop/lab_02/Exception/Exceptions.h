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
    IteratorException(const char *info_msg, const std::source_location &location) noexcept;
};

class SetException : public BaseException
{
public:
    SetException(const char *info_msg, const std::source_location &location) noexcept;
};

class MemoryAllocException : public SetException
{
public:
    MemoryException(const char *info_msg, const std::source_location &location) noexcept;
};

#endif //LAB_02_EXCEPTION_H
