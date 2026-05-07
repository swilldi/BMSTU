//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "DrawManager.h"

#include "Managers/ManagerSolution.h"
#include "Strategies/CoordinateConvert/Creator/CoordinateConvertCreator.h"
#include "Strategies/Projection/Creator/ProjectionCreator.h"
#include "Strategies/RemoveInvisibleEdge/Creator/RemoveInvisibleEdgeCreator.h"
#include "Visitor/CameraExtractor/CameraExtractorVisitor.h"
#include "Visitor/Draw/DrawVisitor.h"

void DrawManager::set_drawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

void DrawManager::draw()
{
    _drawer->clear();

    auto camera_manager = ManagerSolution::get_camera_manager();
    auto active_camera = camera_manager->get_active_camera();

    auto extractor = std::make_shared<CameraExtractorVisitor>();
    active_camera->accept(extractor);
    auto camera_impl = extractor->get_impl();

    auto projection = DefaultProjectionCreator::create();
    auto remove_invisible = RayCastingRemoveInvisibleEdgeCreator::create();
    auto coordinate_convert = DefaultCoordinateConvertCreator::create();

    auto draw_visitor = std::make_shared<DrawVisitor>(std::move(projection), std::move(remove_invisible),
                                                      std::move(coordinate_convert), _drawer, camera_impl);

    auto scene_manager = ManagerSolution::get_scene_manager();
    scene_manager->accept(draw_visitor);
}
