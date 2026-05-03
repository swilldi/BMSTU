//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "BuilderSolutionException.h"
BuilderSolutionException::BuilderSolutionException(const char *info, const location &loc) noexcept :
    BaseSolutionException(info, loc) { }

BuilderSolutionUnknowRepresentation::BuilderSolutionUnknowRepresentation(const location &loc) noexcept :
    BuilderSolutionException("", loc) { }
