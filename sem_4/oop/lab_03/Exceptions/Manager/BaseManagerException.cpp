//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "BaseManagerException.h"
BaseManagerException::BaseManagerException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };
