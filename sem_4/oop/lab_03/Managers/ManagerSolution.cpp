//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "ManagerSolution.h"

#include "Creators/ManagerCreator.h"

std::shared_ptr<CameraManager> ManagerSolution::get_camera_manager()
{
    return CameraManagerCreator().create();
}

std::shared_ptr<DrawManager> ManagerSolution::get_draw_manager()
{
    return DrawManagerCreator().create();
}

std::shared_ptr<LoadManager> ManagerSolution::get_load_manager()
{
    return LoadManagerCreator().create();
}

std::shared_ptr<SceneManager> ManagerSolution::get_scene_manager()
{
    return SceneManagerCreator().create();
}

std::shared_ptr<TransformManager> ManagerSolution::get_transform_manager()
{
    return TransformManagerCreator().create();
}


