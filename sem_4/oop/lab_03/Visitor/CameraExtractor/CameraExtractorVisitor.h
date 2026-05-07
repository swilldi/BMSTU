//
// Created by Dmitriy Dudurev on 06.05.2026.
//

#ifndef LAB_03_CAMERAEXTRACTORVISITOR_H
#define LAB_03_CAMERAEXTRACTORVISITOR_H

#include "Visitor/BaseVisitor.h"

class CameraExtractorVisitor : public BaseVisitor
{
public:
    CameraExtractorVisitor() = default;
    virtual ~CameraExtractorVisitor() override = default;

    void visit(std::shared_ptr<BaseCameraImpl> impl) const override
    {
        _impl = impl;
    }

    void visit(std::shared_ptr<BaseModelImpl>) const override {}

    std::shared_ptr<BaseCameraImpl> get_impl() const noexcept { return _impl; }

private:
    mutable  std::shared_ptr<BaseCameraImpl> _impl;
};

#endif //LAB_03_CAMERAEXTRACTORVISITOR_H
