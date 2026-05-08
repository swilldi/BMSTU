//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#include "BaseException.h"
#include <cstdio>

BaseException::BaseException(const char *info, const location &loc) noexcept {
    snprintf(msg, MSG_LEN, "File: %s (%d:%d) `%s`: %s\n", loc.file_name(), loc.line(), loc.column(),
             loc.function_name(), info);
}

const char *BaseException::what() const noexcept {
    return msg;
}
