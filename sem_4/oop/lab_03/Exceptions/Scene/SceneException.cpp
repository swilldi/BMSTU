//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "SceneException.h"
SceneException::SceneException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { }

SceneInvalidObjectID::SceneInvalidObjectID(const std::source_location &loc) noexcept :
    SceneException("Invalid ID of object", loc) { }