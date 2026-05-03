//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_SCENEEXCEPTION_H
#define LAB_03_SCENEEXCEPTION_H
#include "Exceptions/BaseException.h"


class SceneException : public BaseException
{
public:
    SceneException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class SceneInvalidObjectID : public SceneException
{
public:
    SceneInvalidObjectID(const std::source_location &loc = std::source_location::current()) noexcept;
};


#endif //LAB_03_SCENEEXCEPTION_H