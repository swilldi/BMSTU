//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_MODELEXCEPTION_H
#define LAB_03_MODELEXCEPTION_H
#include "Exceptions/BaseException.h"


class ModelException : public BaseException
{
public:
    ModelException(const char *info, const location &loc = location::current()) noexcept;
};

class ModelInvalidPointCountException : public ModelException
{
public:
    ModelInvalidPointCountException(const location &loc = location::current()) noexcept;
};

class ModelInvalidPointException : public ModelException
{
public:
    ModelInvalidPointException(const location &loc = location::current()) noexcept;
};

class ModelInvalidStructureException : public ModelException
{
public:
    ModelInvalidStructureException(const location &loc = location::current()) noexcept;
};

class ModelInvalidEdgeCountException : public ModelException
{
public:
    ModelInvalidEdgeCountException(const location &loc = location::current()) noexcept;
};

class ModelInvalidEdgeException : public ModelException
{
public:
    ModelInvalidEdgeException(const location &loc = location::current()) noexcept;
};

class ModelInvalidEdgeIDException : public ModelException
{
public:
    ModelInvalidEdgeIDException(const location &loc = location::current()) noexcept;
};

class ModelInvalidRepresentation : public ModelException
{
public:
    ModelInvalidRepresentation(const location &loc = location::current()) noexcept;
};

class ModelInvalidFileFormat : public ModelException
{
public:
    ModelInvalidFileFormat(const location &loc = location::current()) noexcept;
};


#endif //LAB_03_MODELEXCEPTION_H