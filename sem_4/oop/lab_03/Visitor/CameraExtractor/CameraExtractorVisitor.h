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

    void visit(std::shared_ptr<BaseCameraImpl> impl) override;
    void visit(std::shared_ptr<BaseModelImpl>) override;

    std::shared_ptr<BaseCameraImpl> get_impl() const noexcept;

private:
    std::shared_ptr<BaseCameraImpl> _impl;
};

#endif //LAB_03_CAMERAEXTRACTORVISITOR_H
