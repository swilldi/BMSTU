//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_MANAGERCREATOR_H
#define LAB_03_MANAGERCREATOR_H

#include "Concepts/Concepts.h"
#include "Managers/BaseManager.h"
#include "Managers/Camera/CameraManager.h"
#include "Managers/Draw/DrawManager.h"
#include "Managers/Load/LoadManager.h"
#include "Managers/Scene/SceneManager.h"
#include "Managers/Transform/TransformManager.h"

#include <memory>

template <typename BaseManager, Derivative<BaseManager> DeriveManager, typename ... Args>
    requires ConstructableWith<DeriveManager, Args ...>
class ManagerCreator
{
public:
    ManagerCreator() = default;
    ~ManagerCreator() = default;

    template<typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
    std::shared_ptr<DeriveManager> create(CallArgs && ... args);
};

#include "ManagerCreator.hpp"

using CameraManagerCreator = ManagerCreator<BaseManager, CameraManager>;
using DrawManagerCreator = ManagerCreator<BaseManager, DrawManager>;
using LoadManagerCreator = ManagerCreator<BaseManager, LoadManager>;
using SceneManagerCreator = ManagerCreator<BaseManager, SceneManager>;
using TransformManagerCreator = ManagerCreator<BaseManager, TransformManager>;

#endif //LAB_03_MANAGERCREATOR_H