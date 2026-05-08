//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "CameraManagerException.h"

CameraManagerException::CameraManagerException(const char *info, const location &loc) noexcept :
    BaseManagerException(info, loc) {}

CameraManagerInvalidID::CameraManagerInvalidID(const location &loc) noexcept :
    CameraManagerException("Invalid camera ID", loc) { }
