//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "ReaderSolutionException.h"
ReaderSolutionException::ReaderSolutionException(const char *info, const location &loc) noexcept :
    BaseSolutionException(info, loc) { }

ReaderSolutionUnknowExtension::ReaderSolutionUnknowExtension(const location &loc) noexcept :
    ReaderSolutionException("Unknow file extension", loc) { }