//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BONEDIRECTOR_H
#define LAB_03_BONEDIRECTOR_H
#include "Builders/BaseBuilder.h"
#include "Director/Model/ModelDirector.h"


class BoneDirector : public ModelDirector
{
public:
    BoneDirector() = delete;
    explicit BoneDirector(std::shared_ptr<BaseBuilder<BaseModelImpl>> builder);
    virtual ~BoneDirector() = default;

    std::shared_ptr<BaseObject> create() const override;
};


#endif //LAB_03_BONEDIRECTOR_H
