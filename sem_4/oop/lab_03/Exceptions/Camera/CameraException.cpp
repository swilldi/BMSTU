//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "CameraException.h"
CameraException::CameraException(const char *info, const location &loc) noexcept :
    BaseException(info, loc) { }

CameraInvalidID::CameraInvalidID(const location &loc) noexcept :
    CameraException("Invalid camera ID", loc) { }