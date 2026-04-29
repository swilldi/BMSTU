//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#include "MatrixExceptions.h"
MatrixException::MatrixException(const char *info, const location &loc) noexcept:
    BaseException(info, loc) { }


MatrixMemoryAllocateError::MatrixMemoryAllocateError(const location &loc) noexcept:
    MatrixException("Matrix memory allocate error", loc) { }

MatrixInitListInvalidSize::MatrixInitListInvalidSize(const location &loc) noexcept:
    MatrixException("Matrix initialize list invalid size", loc) { }

MatrixIncompatibleDimensions::MatrixIncompatibleDimensions(const location &loc) noexcept:
    MatrixException("Incompatible dimensions of matrix", loc) { }

MatrixOutOfRange::MatrixOutOfRange(const location &loc) noexcept:
    MatrixException("Out of range matrix size", loc) { }