//
// Created by Dmitriy Dudurev on 13.04.2026.
//

#ifndef LAB_02_EXCEPTION_HPP
#define LAB_02_EXCEPTION_HPP

#include <source_location>
#include "Exceptions.h"

IteratorException::IteratorException(const char *info_msg, const std::source_location &location) noexcept :
    BaseException(info_msg, location)
{ };

SetException::SetException(const char *info_msg, const std::source_location &location) noexcept :
    BaseException(info_msg, location)
{ };

MemoryAllocException::MemoryException(const char *info_msg, const std::source_location &location) noexcept:
    BaseException(info_msg, location)
{ };

#endif //LAB_02_EXCEPTION_HPP
