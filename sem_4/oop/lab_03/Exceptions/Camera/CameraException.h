//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_CAMERAEXCEPTION_H
#define LAB_03_CAMERAEXCEPTION_H
#include "Exceptions/BaseException.h"

class CameraException : public BaseException
{
public:
    CameraException(const char *info, const location &loc = location::current()) noexcept;
};

class CameraInvalidID : public CameraException
{
public:
    CameraInvalidID(const location &loc = location::current()) noexcept;
};


#endif //LAB_03_CAMERAEXCEPTION_H