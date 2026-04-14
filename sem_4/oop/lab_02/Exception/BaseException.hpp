//
// Created by Dmitriy Dudurev on 13.04.2026.
//

#ifndef LAB_02_BASEEXCEPTION_HPP
#define LAB_02_BASEEXCEPTION_HPP

#include <source_location>
#include "BaseException.h"
#include <cstdio>

BaseException::BaseException(const char *info_msg, const std::source_location &location) noexcept
{
    snprintf(msg, msg_size, "%s (%d:%d): '%s' -> %s\n",
        location.file_name(), location.line(), location.column(), location.function_name(), info_msg);
};

const char *BaseException::what() const noexcept
{
    return msg;
}

#endif //LAB_02_BASEEXCEPTION_HPP