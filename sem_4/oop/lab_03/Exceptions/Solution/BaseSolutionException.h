//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BASESOLUTIONEXCEPTION_H
#define LAB_03_BASESOLUTIONEXCEPTION_H
#include "Exceptions/BaseException.h"


class BaseSolutionException : public BaseException
{
public:
    BaseSolutionException(const char *info, const location &loc = location::current()) noexcept;
};


#endif //LAB_03_BASESOLUTIONEXCEPTION_H