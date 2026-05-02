//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "LoadManager.h"

#include "Builders/Solution/BuilderSolution.h"
#include "Director/Model/Bone/BoneDirector.h"
#include "Managers/ManagerSolution.h"
#include "Reader/Solution/ReaderSolution.h"

LoadManager::LoadManager()
{
    _director_solution = std::make_shared<BaseDirectorSolution>();
    _director_solution->registrate<BoneDirector, std::shared_ptr<BaseBuilder>>(DirectorID::BoneDirectorID);
}

void LoadManager::load(ModelRepresentationID representation_id, const std::string &filename)
{
    ReaderSolution reader_solution;
    auto reader = reader_solution.create(filename);

    BuilderSolution builder_solution;
    auto builder = builder_solution.create(reader, representation_id);

    auto director = _director_solution->create(DirectorID::BoneDirectorID, builder);

    auto object = director->create();

    auto scene_manager = ManagerSolution::get_scene_manager();
    scene_manager->add_object(object);
}
