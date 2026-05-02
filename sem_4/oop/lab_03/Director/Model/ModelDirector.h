//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_MODELDIRECTOR_H
#define LAB_03_MODELDIRECTOR_H
#include "Director/BaseDirector.h"

class ModelDirector : public BaseDirector
{
public:
    ModelDirector() = default;
    virtual ~ModelDirector() = default;

    std::shared_ptr<BaseObject> create() const override = 0;
};

#endif //LAB_03_MODELDIRECTOR_H