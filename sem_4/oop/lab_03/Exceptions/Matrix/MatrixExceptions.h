//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_MATRIXEXCEPTIONS_H
#define LAB_03_MATRIXEXCEPTIONS_H
#include "Exceptions/BaseException.h"

class MatrixException : public BaseException {
public:
    MatrixException(const char *info, const location &loc = location::current()) noexcept;
};


class MatrixMemoryAllocateError : public  MatrixException {
public:
    MatrixMemoryAllocateError(const location &loc = location::current()) noexcept;
};

class MatrixInitListInvalidSize : public MatrixException {
public:
    MatrixInitListInvalidSize(const location &loc = location::current()) noexcept;
};

class MatrixIncompatibleDimensions : public MatrixException {
    MatrixIncompatibleDimensions(const location &loc = location::current()) noexcept;
};

class MatrixOutOfRange : public MatrixException {
    MatrixOutOfRange(const location &loc = location::current()) noexcept;
};

#endif //LAB_03_MATRIXEXCEPTIONS_H