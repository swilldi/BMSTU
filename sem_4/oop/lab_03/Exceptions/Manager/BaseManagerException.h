//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BASEMANAGEREXCEPTION_H
#define LAB_03_BASEMANAGEREXCEPTION_H
#include "Exceptions/BaseException.h"


class BaseManagerException : public BaseException
{
public:
    BaseManagerException(const char *info,
                   const std::source_location &loc = std::source_location::current()) noexcept;
};


#endif //LAB_03_BASEMANAGEREXCEPTION_H