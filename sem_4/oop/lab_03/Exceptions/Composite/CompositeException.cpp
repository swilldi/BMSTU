//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "CompositeException.h"
CompositeException::CompositeException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { }


CompositeIndexOutOfRange::CompositeIndexOutOfRange(const std::source_location &loc) noexcept :
    CompositeException("Composite index out of range", loc) { }