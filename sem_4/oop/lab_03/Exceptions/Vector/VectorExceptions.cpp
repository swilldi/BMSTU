//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#include "VectorExceptions.h"

VectorException::VectorException(const char *info, const location &loc) noexcept :
    BaseException(info, loc) { }

VectorDivisionByZero::VectorDivisionByZero(const location &loc) noexcept :
    VectorException("Division by zero", loc) { }

