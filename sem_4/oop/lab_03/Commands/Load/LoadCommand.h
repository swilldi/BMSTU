//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_LOADCOMMAND_H
#define LAB_03_LOADCOMMAND_H
#include "Commands/BaseCommand.h"
#include "ID/ID.h"
#include "Managers/Load/LoadManager.h"
#include <string>

class LoadCommand : public BaseCommand
{
public:
    LoadCommand() = default;

    virtual ~LoadCommand() = default;
};

class BoneLoadCommand : public LoadCommand
{
public:
    BoneLoadCommand(ModelRepresentationID representation_id, const std::string &filename);
    virtual ~BoneLoadCommand() override = default;

    void execute() override;

private:
    using Action = void (LoadManager::*)(ModelRepresentationID, const std::string &);

    Action _action;
    ModelRepresentationID _representation_id;
    std::string _filename;
    std::shared_ptr<LoadManager> _load_manager;
};

#endif //LAB_03_LOADCOMMAND_H
