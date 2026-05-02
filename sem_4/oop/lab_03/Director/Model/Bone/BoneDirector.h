//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BONEDIRECTOR_H
#define LAB_03_BONEDIRECTOR_H
#include "Director/Model/ModelDirector.h"


class BoneDirector : public ModelDirector
{
public:
    BoneDirector() = delete;
    BoneDirector(std::shared_ptr<BaseBuilder> builder);
    virtual ~BoneDirector() = default;

    std::shared_ptr<BaseObject> create() const override;
};


#endif //LAB_03_BONEDIRECTOR_H
