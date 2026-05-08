//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_TRANSFORMMANAGER_H
#define LAB_03_TRANSFORMMANAGER_H
#include "Managers/BaseManager.h"
#include "Transform/Data/Move/MoveData.h"
#include "Transform/Data/Rotate/RotateData.h"
#include "Transform/Data/Scale/ScaleData.h"

class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    virtual ~TransformManager() = default;

    void move_object(size_t id, const MoveData &data);
    void rotate_object(size_t id, const RotateData &data);
    void scale_object(size_t id, const ScaleData &data);
};

#endif //LAB_03_TRANSFORMMANAGER_H