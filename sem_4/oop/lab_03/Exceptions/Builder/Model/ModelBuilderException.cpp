//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "ModelBuilderException.h"
ModelBuilderException::ModelBuilderException(const char *info, const std::source_location &loc) noexcept :
    BaseBuilderException(info, loc) { }

ModelBuilderPointsException::ModelBuilderPointsException(const std::source_location &loc) noexcept :
    ModelBuilderException("Model build points error", loc) { }

ModelBuilderEdgesException::ModelBuilderEdgesException(const std::source_location &loc) noexcept :
    ModelBuilderException("Model build edges error", loc) { }

ModelBuilderCenterException::ModelBuilderCenterException(const std::source_location &loc) noexcept :
    ModelBuilderException("Model builder center error", loc) { }