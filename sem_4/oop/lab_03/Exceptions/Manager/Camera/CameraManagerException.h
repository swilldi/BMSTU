//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_CAMERAMANAGEREXCEPTION_H
#define LAB_03_CAMERAMANAGEREXCEPTION_H
#include "Exceptions/Manager/BaseManagerException.h"


class CameraManagerException : public BaseManagerException
{
public:
    CameraManagerException(const char *info, const location &loc = location::current()) noexcept;
};

class CameraManagerInvalidID : public CameraManagerException {
public:
    CameraManagerInvalidID(const location &loc = location::current()) noexcept;
};

#endif //LAB_03_CAMERAMANAGEREXCEPTION_H