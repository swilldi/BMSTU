//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "LoadCommand.h"

#include "Managers/ManagerSolution.h"

BoneLoadCommand::BoneLoadCommand(ModelRepresentationID representation_id,const std::pmr::string &filename) :
    _action(&LoadManager::load), _representation_id(representation_id), _filename(filename),
    _load_manager(ManagerSolution::get_load_manager()) { }

void BoneLoadCommand::execute()
{
    (*_load_manager.*_action)(_representation_id, _filename);
}
