//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_VECTOREXCEPTIONS_H
#define LAB_03_VECTOREXCEPTIONS_H
#include "Exceptions/BaseException.h"

class VectorException : public BaseException {
public:
    VectorException(const char *info, const location &loc = location::current()) noexcept;
};

class VectorDivisionByZero : public VectorException {
public:
    VectorDivisionByZero(const location &loc = location::current()) noexcept;
};

#endif //LAB_03_VECTOREXCEPTIONS_H
