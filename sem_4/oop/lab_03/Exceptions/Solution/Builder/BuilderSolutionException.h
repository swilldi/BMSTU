//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BUILDERSOLUTIONEXCEPTION_H
#define LAB_03_BUILDERSOLUTIONEXCEPTION_H
#include "Exceptions/Solution/BaseSolutionException.h"


class BuilderSolutionException : public BaseSolutionException
{
public:
    BuilderSolutionException(const char *info, const location &loc = location::current()) noexcept;
};

class BuilderSolutionUnknowRepresentation : public BuilderSolutionException
{
public:
    BuilderSolutionUnknowRepresentation(const location &loc = location::current()) noexcept;
};


#endif //LAB_03_BUILDERSOLUTIONEXCEPTION_H