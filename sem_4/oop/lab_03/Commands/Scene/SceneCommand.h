//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_SCENECOMMAND_H
#define LAB_03_SCENECOMMAND_H
#include "Commands/BaseCommand.h"
#include "Managers/Draw/DrawManager.h"

class SceneCommand : public BaseCommand
{
public:
    SceneCommand() = default;
    virtual ~SceneCommand() = default;
};


class DrawSceneCommand : public SceneCommand
{
public:
    DrawSceneCommand();
    virtual ~DrawSceneCommand() = default;

    void execute() override;

private:
    using Action = void (DrawManager::*)();

    Action _action;
    std::shared_ptr<DrawManager> _draw_manager;
};

#endif //LAB_03_SCENECOMMAND_H