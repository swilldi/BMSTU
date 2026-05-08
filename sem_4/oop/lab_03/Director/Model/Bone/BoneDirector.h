//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BONEDIRECTOR_H
#define LAB_03_BONEDIRECTOR_H
#include "Builders/Model/BaseModelBuilder.h"
#include "Director/Model/ModelDirector.h"


class BoneDirector : public ModelDirector
{
public:
    BoneDirector() = delete;
    explicit BoneDirector(std::shared_ptr<BaseModelBuilder> builder);
    virtual ~BoneDirector() = default;

    std::shared_ptr<BaseObject> create() const override;

private:
    std::shared_ptr<BaseModelBuilder> _builder;
};


#endif //LAB_03_BONEDIRECTOR_H
