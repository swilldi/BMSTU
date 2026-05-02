//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_LOADMANAGER_H
#define LAB_03_LOADMANAGER_H
#include "Director/DirectorSolution.h"
#include "Managers/BaseManager.h"
#include "ID/ID.h"
#include <string>

class LoadManager : public BaseManager
{
public:
    LoadManager();
    virtual ~LoadManager() override = default;

    void load(ModelRepresentationID representation_id, const std::string &filename);

private:
    std::shared_ptr<BaseDirectorSolution> _director_solution;
};

#endif //LAB_03_LOADMANAGER_H