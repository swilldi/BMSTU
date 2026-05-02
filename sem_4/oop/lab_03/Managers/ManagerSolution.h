//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_MANAGERSOLUTION_H
#define LAB_03_MANAGERSOLUTION_H
#include "Camera/CameraManager.h"
#include "Draw/DrawManager.h"
#include "Load/LoadManager.h"
#include "Scene/SceneManager.h"
#include "Transform/TransformManager.h"

#include <memory>

class ManagerSolution
{
public:
    ManagerSolution() = delete;
    ~ManagerSolution() = delete;
    ManagerSolution(ManagerSolution &) = delete;

    static std::shared_ptr<CameraManager> get_camera_manager();
    static std::shared_ptr<DrawManager> get_draw_manager();
    static std::shared_ptr<LoadManager> get_load_manager();
    static std::shared_ptr<SceneManager> get_scene_manager();
    static std::shared_ptr<TransformManager> get_transform_manager();

};

#endif //LAB_03_MANAGERSOLUTION_H