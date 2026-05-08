//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "SceneCommand.h"

#include "Managers/ManagerSolution.h"

DrawSceneCommand::DrawSceneCommand() :
    _action(&DrawManager::draw), _draw_manager(ManagerSolution::get_draw_manager()) { }

void DrawSceneCommand::execute()
{
    (*_draw_manager.*_action)();
}
