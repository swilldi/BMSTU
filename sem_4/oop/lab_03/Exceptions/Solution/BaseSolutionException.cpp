//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "BaseSolutionException.h"

BaseSolutionException::BaseSolutionException(const char *info, const location &loc) noexcept :
    BaseException(info, loc) { }
