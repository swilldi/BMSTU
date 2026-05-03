//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "ModelException.h"

ModelException::ModelException(const char *info, const location &loc) noexcept : BaseException(info, loc) {}

ModelInvalidPointCountException::ModelInvalidPointCountException(const location &loc) noexcept :
    ModelException("Model invalid point count", loc) { }

ModelInvalidPointException::ModelInvalidPointException(const location &loc) noexcept :
    ModelException("Model invalid point", loc) { }

ModelInvalidStructureException::ModelInvalidStructureException(const location &loc) noexcept :
    ModelException("Model invalid structure", loc) { }

ModelInvalidEdgeCountException::ModelInvalidEdgeCountException(const location &loc) noexcept :
    ModelException("Model invalid edge count", loc) { }

ModelInvalidEdgeException::ModelInvalidEdgeException(const location &loc) noexcept :
    ModelException("Model invalid edge", loc) { }

ModelInvalidEdgeIDException::ModelInvalidEdgeIDException(const location &loc) noexcept :
    ModelException("Model invalid ID of edge", loc) { }

ModelInvalidRepresentation::ModelInvalidRepresentation(const location &loc) noexcept :
    ModelException("Model invalid representation", loc) { }

ModelInvalidFileFormat::ModelInvalidFileFormat(const location &loc) noexcept :
    ModelException("Model invalid file format", loc) { }
