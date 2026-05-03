//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_READERSOLUTIONEXCEPTION_H
#define LAB_03_READERSOLUTIONEXCEPTION_H
#include "Exceptions/Solution/BaseSolutionException.h"


class ReaderSolutionException : public BaseSolutionException
{
public:
    ReaderSolutionException(const char *info, const location &loc = location::current()) noexcept;
};

class ReaderSolutionUnknowExtension : public ReaderSolutionException
{
public:
    ReaderSolutionUnknowExtension(const location &loc = location::current()) noexcept;
};


#endif //LAB_03_READERSOLUTIONEXCEPTION_H